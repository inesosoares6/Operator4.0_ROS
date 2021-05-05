# Operator 4.0 - ROS

**Devices**: Microsoft HoloLens 2, Universal Robots UR5

## ROS terminals
- Open bridge to HoloLens 2 communication:

    *roslaunch rosbridge_server rosbridge_websocket.launch*

- Read topic info

    *rostopic echo /HLposition*

- Record bags

    *rosbag record -O <file_name> /HLposition

- Run scripts

    *rosrun operator4_0 robot_control_test*
    
    *rosrun operator4_0 subscriber*
    
    *rosrun operator4_0 robot_sender*
