#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/PoseStamped.h"
#include <iostream>
#include <fstream>

using namespace geometry_msgs;

std::ofstream myfile;

void hololensCallback(const geometry_msgs::Vector3::ConstPtr& hololens)
{
    ROS_INFO("Recording");
    myfile << hololens->x << "," << hololens->y << "," << hololens->z << "\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n_HL;

  ros::Subscriber sub_HL2 = n_HL.subscribe("HLposition", 1000, hololensCallback);

  myfile.open("HoloLens2_data.csv");
  myfile << "HL_x,HL_y,HL_z\n";

  ros::spin();

  myfile.close();

  return 0;
}