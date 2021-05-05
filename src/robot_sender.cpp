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

#define PORT 50002 // The same port as used by the server
#define HOST "192.168.1.74" // The remote host

char STOP= 'n';
char option =' ';

void hololensCallback(const geometry_msgs::Vector3::ConstPtr& hololens)
{
    vector<string> vec;
    ostringstream ss;
    vec.push_back("def myProg():\n");
    ss << "movel(p[" << hololens->x << "," << hololens->y << "," << hololens->z << ", 1.57, 0.00, 0.00], a=0.01, v=0.1, r=0)\n";
    vec.push_back(ss.str());
    ss.str(std::string());
    ss.clear();
    vec.push_back("end\n");

    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        write (client_sockfd, it->c_str(), it->length());
        sleep(1);
    }
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

    ros::init(argc, argv, "subscriber");
    ros::NodeHandle n_HL;
    ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);
           
    ros::spin();

    //Close Socket
    close(client_sockfd);

    return 0;
 }