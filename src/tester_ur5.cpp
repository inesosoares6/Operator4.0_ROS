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
    myfile << "movel(p[" << - hololens->x << "," << hololens->z << "," << hololens->y << ", 1.57, 0.00, 0.00], a=0.01, v=0.1, r=0.01)\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");

  ros::NodeHandle n_HL;

  ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);

  myfile.open("UR5_tester");
  myfile << "def myProg():\n";

  ros::spin();

  myfile << "end\n";
  myfile.close();

  return 0;
}