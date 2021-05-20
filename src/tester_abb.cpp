#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include <iostream>
#include <fstream>

using namespace geometry_msgs;

std::ofstream myfile;

void hololensCallback(const geometry_msgs::Vector3::ConstPtr& hololens)
{
    ROS_INFO("Recording");
    myfile << "MOVEL [[" << - hololens->x << "," << hololens->z << "," << hololens->y << "],[0.7071,0,0.7071,0],[0,0,0,0][0,0,0,9E+09,9E+09,9E+09]], v1000, fine, tool0;\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");

  ros::NodeHandle n_HL;

  ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);

  myfile.open("ABB_tester");
  myfile << "MODULE MainModule\n";
  myfile << "PROC main()\n";

  ros::spin();

  myfile << "END\n";
  myfile << "PROCENDMODULE\n";
  myfile.close();

  return 0;
}