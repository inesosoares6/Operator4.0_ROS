#include <ros/ros.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>          /* stderr, stdout */
#include <netdb.h>          /* hostent struct, gethostbyname() */
#include <arpa/inet.h>      /* inet_ntoa() to format IP address */
#include <netinet/in.h>     /* in_addr structure */
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>			//cout
#include <stdlib.h>			//exit
#include <string.h>			//bzero
#include <signal.h>			//catch ctrl+c
#include <pthread.h>
#include <vector>
#include <cctype>
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include <iostream>
#include <fstream>

using namespace std;

int client_sockfd;  // server socket (global for sig capture)

#define PORT 30002 // The same port as used by the server
#define HOST "192.168.1.66" // The remote host

char STOP= 'n';
char option =' ';

vector<string> vec;
ostringstream ss;

bool sent2robot;
bool start_doc;

std_msgs::String msg2;
std::stringstream initiate_doc;
std_msgs::String msg1;
std::stringstream finalize_doc;

void statusCallback(const std_msgs::String::ConstPtr& status)
{
    if(strcmp(status->data.c_str(), msg1.data.c_str())==0){
        if(!sent2robot){
            // SEND TO ROBOT
            vec.push_back("end\n");
            for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                write (client_sockfd, it->c_str(), it->length());
                //sleep(1); // CHECK IF THIS IS NECESSARY
            }
            vec.clear();
            ROS_INFO("File sent to UR5");
            sent2robot = true;
            start_doc = false;
        }
    } else if(strcmp(status->data.c_str(), msg2.data.c_str())==0){
        if(!start_doc){
            // START DOC
            vec.push_back("def myProg():\n");
            ROS_INFO("File opened");
            start_doc = true;
            sent2robot = false;
        }
    }
}

void hololensCallback(const geometry_msgs::Vector3::ConstPtr& hololens)
{
    ss << "movel(p[" << hololens->y << "," << hololens->z << "," << hololens->x << ", 2.2, 2.2, -0.3], a=0.01, v=0.5, r=0.1)\n";
    vec.push_back(ss.str());
    ss.str(std::string());
    ss.clear();
}

int main(int argc, char **argv) {

    struct sockaddr_in serv_addr; // , cli_addr;
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_sockfd < 0)
    {
        //client_sockfd - id do socket principal do servidor
        cout << "Error creating socket" << endl;
        exit(-1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); //bzero - apaga todos os dados da estrutura (coloca a 0's)
    serv_addr.sin_family = AF_INET;	//AF_INET - endereço IP
    serv_addr.sin_addr.s_addr = inet_addr(HOST);;//INADDR_ANY - aceitar pedidos para qualquer IP
    serv_addr.sin_port = htons(PORT);

    //Connect to remote server
    if (connect(client_sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
        return 1;
    }

    start_doc = false;
    sent2robot = false;
    initiate_doc << "start_doc";
    msg2.data = initiate_doc.str();
    finalize_doc << "send_doc";
    msg1.data = finalize_doc.str();

    ros::init(argc, argv, "ur5_sender");
    ros::NodeHandle n_HL;
    ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);
    ros::Subscriber sub_status = n_HL.subscribe("HLstatus", 1000, statusCallback);
           
    ros::spin();

    //Close Socket
    close(client_sockfd);

    return 0;
 }