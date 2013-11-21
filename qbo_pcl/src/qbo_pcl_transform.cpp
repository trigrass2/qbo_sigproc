#include "ros/ros.h"
#include <sensor_msgs/PointCloud2.h>
// PCL specifics:
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_types.h>
// tf specifics
#include <tf/transform_listener.h>
#include <iostream>
#include <string>

/*Transformer transforms point clouds published on the "camera/depth/points" topic into the /odom frame. 
Publishes the transformed point cloud on the "camera/depth/transformed_points" topic.
*/
class Transformer
{
public:
	Transformer(const ros::NodeHandle& nh, 
                   const ros::NodeHandle& nh_private):
	_nh(nh),
	_nh_private(nh_private)
	{
		initParams();
		ROS_INFO("Transformer initialized");
	}
	~Transformer(){
	}

	void transformAndPublishPC(const sensor_msgs::PointCloud2&);

private:
	void initParams(void);
	std::string _target_frame;
	ros::Publisher _pub; 
	tf::TransformListener _transform_listener;
	ros::Subscriber _sub;
	ros::NodeHandle _nh;                ///< the public nodehandle
    ros::NodeHandle _nh_private;        ///< the private nodehandle
};

void Transformer::initParams(void){
	std::string input_topic;
	std::string output_topic;

	if (!_nh_private.getParam ("target_frame", _target_frame)){
	    _target_frame = "/odom";
		ROS_WARN("Need to set target frame argument! Setting target frame to /odom");
	}
	if (!_nh_private.getParam ("input_topic", input_topic)){
	    input_topic = "/camera/depth/points";
	    ROS_WARN("Need to set input_topic argument! Setting input_topic to /camera/depth/points");
	}
	if (!_nh_private.getParam ("output_topic", output_topic))
	{
		output_topic = "/camera/depth/transformed_points";	
		ROS_WARN("Need to set output_topic argument! Setting input_topic to /camera/depth/transformed_points");
	}
	_sub = _nh.subscribe(input_topic, 1, &Transformer::transformAndPublishPC,this);
	_pub = _nh.advertise<sensor_msgs::PointCloud2> (output_topic,1);
}

void Transformer::transformAndPublishPC(const sensor_msgs::PointCloud2 &inputCloud){
	ROS_INFO("Transforming PC");
	sensor_msgs::PointCloud2 output;
	std::cout << inputCloud.header.frame_id << std::endl;
	output.header = inputCloud.header;
	//Get the transform matrix and do transformation here

	if(!pcl_ros::transformPointCloud(_target_frame, inputCloud, output, _transform_listener)){
		ROS_ERROR("Something went wrong when transforming PC");
		return;
	}
	//Publish transformed cloud here
	std::cout << output.header.frame_id << std::endl;
	_pub.publish(output);
}

int main(int argc, char **argv)
{
	ros::init(argc,argv, "pointcloud_transformer");

  	ros::NodeHandle nh;
  	ros::NodeHandle nh_private("~");
	Transformer myTransformer(nh,nh_private);

	ros::spin();
	return 0;
}
