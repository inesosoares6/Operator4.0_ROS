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

using namespace std;

int client_sockfd;  // server socket (global for sig capture)

#define PORT 30003 // The same port as used by the server
#define HOST "192.168.11.76" // The remote host

char STOP= 'n';
char option =' ';

int main() {


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
              cout << "Connected" << endl;
              return 1;
          }



          double x=-0.431075;
          double y=0.632364;
          double z=0.0915;
          double rx=1.57;
          double ry=0.0;
          double rz=0.0;

          vector<string> vec;
          ostringstream ss;
          vec.push_back("def myProg():\n");
          ss << "movel(p[" << x << "," << y << "," << z+0.06 << ", " << rx << "," << ry << "," << rz << "], a=0.01, v=0.1, r=0)\n";
          vec.push_back(ss.str());
          ss.str( std::string() );
          ss.clear();
          ss << "movel(p[" << x << "," << y << "," << z << ", " << rx << "," << ry << "," << rz << "], a=0.01, v=0.1, r=0)\n";
          vec.push_back(ss.str());
          ss.str( std::string() );
          ss.clear();
          ss << "movel(p[" << x << "," << y << "," << 0.267641 << ", " << rx << "," << ry << "," << rz << "], a=0.01, v=0.1, r=0)\n";
          vec.push_back(ss.str());
          ss.str( std::string() );
          ss.clear();
          vec.push_back("end\n");


            for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                write (client_sockfd, it->c_str(), it->length());
                sleep(1);

            }
           

          //Close Socket
      close(client_sockfd);

      return 0;
 }