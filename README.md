# realsense
Reference link: https://github.com/ros-perception/pointcloud_to_laserscan

Install realsense with ROS:
- $sudo apt-get install ros-melodic-realsense2-camera
- $sudo apt-get install ros-melodic-realsense2-description

Connect camera realsense:
- Check usb port: $ls /dev/video*

Run:
- $roslaunch detect_obstacle pointcloud_to_laserscan.launch
