<<<<<<< HEAD

Open bridge to HoloLens 2 communication
roslaunch rosbridge_server rosbridge_websocket.launch

Launch VRPN
roslaunch vrpn_client_ros sample.launch

Read topic info
rostopic echo /HLposition
rostopic echo /HTCposition
rostopic echo /vrpn_client_node/IndexFinger/pose

Record bags
rosbag record -O <file_name> /HLposition /vrpn_client_node/IndexFinger/pose
rosbag record -O <file_name> /HTCposition /vrpn_client_node/IndexFinger/pose
rosbag record -O <file_name> /HLposition

Run scripts
rosrun repeatability_tests sync_HL_OT _testNumber:=_#
rosrun repeatability_tests sync_HTC_OT _testNumber:=_#
rosrun operator4_0 robot_control_test
rosrun operator4_0 subscriber
rosrun operator4_0 robot_sender
=======
# Operator 4.0 - ROS

**Devices**: Microsoft HoloLens 2, Universal Robots UR5

## ROS terminals
- Open bridge to HoloLens 2 communication:

    *roslaunch rosbridge_server rosbridge_websocket.launch*

- Read topic info

    *rostopic echo /HLposition*

- Record bags

    *rosbag record -O <file_name> /HLposition*

- Run scripts

    *rosrun operator4_0 robot_control_test*
    
    *rosrun operator4_0 subscriber*
    
    *rosrun operator4_0 robot_sender*
>>>>>>> 39d731bf7419760fb7a0dc3d6ce52bfe6886bce1
