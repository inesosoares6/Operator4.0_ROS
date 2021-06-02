# Operator 4.0 - ROS

**Devices**: Microsoft HoloLens 2, Universal Robots UR5, ABB IRB 2600

## ROS terminals
- Open bridge to HoloLens 2 communication:

    *roslaunch rosbridge_server rosbridge_websocket.launch*

- Read topic info

    *rostopic echo /HLposition*
   
    *rostopic echo /HLstatus*

- Run scripts
    
    *rosrun operator4_0 ur5_sender* -> subscribes to HL2 topic, builds and sends program to UR5 (language: *URScript*)
    
    *rosrun operator4_0 abb_translator* -> subscribes to HL2 topic, builds and generates the program for ABB (language: *RAPID*)
