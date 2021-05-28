#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include <iostream>
#include <fstream>

using namespace geometry_msgs;

std::ofstream myfile;

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
            myfile << "ENDPROC\n";
            myfile << "ENDMODULE\n";
            myfile.close();
            ROS_INFO("File ready to go to ABB");
            sent2robot = true;
            start_doc = false;
        }
    } else if(strcmp(status->data.c_str(), msg2.data.c_str())==0){
        if(!start_doc){
            // START DOC
            myfile.open("MainModule.mod");
            myfile << "MODULE MainModule\n";
            myfile << "PROC main()\n";
            ROS_INFO("File opened");
            start_doc = true;
            sent2robot = false;
        }
    }
}

void hololensCallback(const geometry_msgs::Vector3::ConstPtr& hololens)
{
    myfile << "MoveL [[" << hololens->y * 1000 << "," << hololens->z * 1000 << "," << hololens->x * 1000 << "],[0.5,-0.5,0.5,0.5],[1,0,-1,1],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]], v200, z50, toolSprayGun;\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tester_abb");

  ros::NodeHandle n_HL;

  start_doc = false;
  sent2robot = false;
  initiate_doc << "start_doc";
  msg2.data = initiate_doc.str();
  finalize_doc << "send_doc";
  msg1.data = finalize_doc.str();

  ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);
  ros::Subscriber sub_status = n_HL.subscribe("HLstatus", 1000, statusCallback);

  ros::spin();

  return 0;
}