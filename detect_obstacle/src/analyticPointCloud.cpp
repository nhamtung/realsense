
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
//pcl::toROSMsg
#include <pcl/io/pcd_io.h>
#include <string>
#include <pcl/filters/voxel_grid.h>
#include "pcl_ros/point_cloud.h"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>

ros::Publisher pub, pub1, pub2; 

void analyticPointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    sensor_msgs::PointCloud2 pointCloud = *msg;
    ROS_INFO("analyticPointCloud.cpp - height: %d", pointCloud.height);
    ROS_INFO("analyticPointCloud.cpp - width: %d", pointCloud.width);
    for (int i=0; i<4; i++){
        ROS_INFO("analyticPointCloud.cpp - fields.name: %s", pointCloud.fields[i].name.c_str());
        ROS_INFO("analyticPointCloud.cpp - fields.offset: %d", pointCloud.fields[i].offset);
        ROS_INFO("analyticPointCloud.cpp - fields.datatype: %d", pointCloud.fields[i].datatype);
        ROS_INFO("analyticPointCloud.cpp - fields.count: %d", pointCloud.fields[i].count);
    }
    ROS_INFO("analyticPointCloud.cpp - is_bigendian: %d", pointCloud.is_bigendian);
    ROS_INFO("analyticPointCloud.cpp - point_step: %d", pointCloud.point_step);
    ROS_INFO("analyticPointCloud.cpp - row_step: %d", pointCloud.row_step);
    ROS_INFO(" ");

    

    pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl::PCLPointCloud2 cloud_filtered;
    pcl_conversions::toPCL(*msg, *cloud);
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloudPtr);
    sor.setLeafSize (0.1, 0.1, 0.1);
    sor.filter (cloud_filtered);
    sensor_msgs::PointCloud2 output;
    pcl_conversions::fromPCL(cloud_filtered, output);
    pub.publish (output);

    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(*msg, pcl_pc2);
    pub1.publish(pcl_pc2);
    pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);
    pub2.publish(temp_cloud);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "analyticPointCloud");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/camera/depth/color/points", 1, analyticPointCloudCallback);
    pub = n.advertise<sensor_msgs::PointCloud2> ("output", 1);
    pub1 = n.advertise<pcl::PCLPointCloud2>("output1", 10);
    pub2 = n.advertise<pcl::PointCloud<pcl::PointXYZ>>("output2", 10);

  ros::spin();

  return 0;
}