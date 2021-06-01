cmake_minimum_required(VERSION 3.0.2)
project(detect_obstacle)

find_package(catkin REQUIRED COMPONENTS
  laser_geometry
  message_filters
  nodelet
  roscpp
  sensor_msgs
  tf2
  tf2_ros
  tf2_sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES pointcloud_to_laserscan
  CATKIN_DEPENDS laser_geometry message_filters nodelet roscpp sensor_msgs tf2 tf2_ros tf2_sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} src/pointcloud_to_laserscan_nodelet.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

add_executable(pointcloud_to_laserscan src/pointcloud_to_laserscan.cpp)
target_link_libraries(pointcloud_to_laserscan ${catkin_LIBRARIES})
#add_executable(analyticPointCloud src/analyticPointCloud.cpp)
#target_link_libraries(analyticPointCloud ${catkin_LIBRARIES})
