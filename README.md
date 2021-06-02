# Operator 4.0 - ROS

**Devices**: Microsoft HoloLens 2, Universal Robots UR5, ABB IRB 2600

## Terminals for running the program
- Open bridge to communicate with HoloLens 2 application

      roslaunch rosbridge_server rosbridge_websocket.launch

- Read topic info

      rostopic echo /HLposition
      rostopic echo /HLstatus

- Run scripts
    
      rosrun operator4_0 ur5_sender
      rosrun operator4_0 abb_translator

## Scripts purpose

- *ur5_sender* -> subscribes to HL2 topic, builds and sends program to UR5 (language: *URScript*)
- *abb_translator* -> subscribes to HL2 topic and generates the program for ABB (language: *RAPID*)
- *talker_start_doc* -> writes *start_doc* in topic /HLstatus, simulating the command sent by the HoloLens 2 application
- *talker_send_doc* -> writes *send_doc* in topic /HLstatus, simulating the command sent by the HoloLens 2 application
- *tester_ur5* -> subscribes to HL2 topic and generates the program for UR5 (language: *URScript*)
- *ur5_sender_test_circle* -> program to test the UR5 movements (draws a circle)
- *record2csv* -> subscribes to HL2 topic and prints the coordinates to a csv file
