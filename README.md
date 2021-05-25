# Operator 4.0 - ROS

**Devices**: Microsoft HoloLens 2, Universal Robots UR5

## ROS terminals
- Open bridge to HoloLens 2 communication:

    *roslaunch rosbridge_server rosbridge_websocket.launch*

- Read topic info

    *rostopic echo /HLposition*

- Record & play bags

    *rosbag record -O <file_name> /HLposition*
    
    *rosbag play <file_name>*

- Run scripts
    
    *rosrun operator4_0 ur5_sender* -> subscribes to HL2 topic, builds and sends program to UR5
    
    *rosrun operator4_0 tester_ur5* -> subscribes to HL2 topic, builds and prints the program for UR5
    
    *rosrun operator4_0 tester_abb* -> subscribes to HL2 topic, builds and prints the program for ABB
    
    *rosrun operator4_0 record2csv* -> subscribes to HL2 topic and prints the coordinates to a csv file
    
    *rosrun operator4_0 robot_control_test* -> program to test the UR5 movements
