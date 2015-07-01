#include <player_node.h>

using namespace std;

namespace DemconRobot
{
	PlayerNode::PlayerNode()
	{
		//set several parameter values from config file
		ros::NodeHandle private_nh("playerNode");
		robotId = "demconRobot1";
		private_nh.getParam("demcon_config/RobotId", robotId);
		ROS_INFO("I get ROBOT_ID: [%s] ", robotId.c_str());

		robotType = "Dcon";
		private_nh.getParam("demcon_config/RobotType", robotType);
		ROS_INFO("I get ROBOT_TYPE: [%s]", robotType.c_str());

		wheelRadius = 0.083;
		private_nh.getParam("demcon_config/WheelRadius", wheelRadius);
		ROS_INFO("I get wheel radius: [%f]", wheelRadius);

		wheelDis = 0.480;
		private_nh.getParam("demcon_config/WheelDistance", wheelDis);
		ROS_INFO("I get wheel distance: [%f]", wheelDis);

		minSpeed = 0;
		private_nh.getParam("demcon_config/MinSpeed", minSpeed);
		ROS_INFO("I get minimum speed: [%f]", minSpeed);

		maxSpeed = 0;
		private_nh.getParam("demcon_config/MaxSpeed", maxSpeed);
		ROS_INFO("I get maximum speed [%f] ", maxSpeed);

		m_y = 0;
		m_x = 0;
		m_theta = 0;
		deltaDistR = 0;
		deltaDistL = 0;
		speedR = 0;
		speedL = 0;

		//advertise wheel velocity and odometry topics
		WheelVelocities_pub = node_.advertise<beaglebone::WheelVelocities>("Wheel_Set_Velocity", 100);
		odom_pub = node_.advertise<nav_msgs::Odometry>("odometry", 10);

		last_time=ros::Time::now();
	}

	PlayerNode::~PlayerNode()
	{
	}

	int PlayerNode::start()
	{
		//subscribe to robot velocity topic published by the Move_base 
		cmd_vel_sub_ = node_.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, boost::bind(&PlayerNode::cmdVelReceived, this, _1));
		//subscribe to the wheel delta distance topic published by the robot platform
		WheelDistances_sub = node_.subscribe<beaglebone::WheelDistances>("/Wheel_Delta_Distance", 10, boost::bind(&PlayerNode::deltaDistanceReceived, this, _1));
		return 0;
	}

	int PlayerNode::stop()
	{
		return 0;
	}

	void PlayerNode::doUpdate()
	{
		publishOdometry();
	}

	void PlayerNode::cmdVelReceived(const geometry_msgs::Twist::ConstPtr& cmd_vel)
	{

		double g_vel = cmd_vel -> linear.x;
		double t_vel = cmd_vel -> angular.z;

		float left = 0;
		float right = 0;
		//if andular velocity above thresshold of 0.28 rad/s then rotate robot first. else rotate while driving
		//this prevents deviations caused by wheel slip encountered while rotating and driving
		if(abs(t_vel) < 0.28)
		{
			left = (2*g_vel - t_vel*wheelDis) / (2*wheelRadius);
			right = (t_vel*wheelDis + 2*g_vel) / (2*wheelRadius);
		}
		else
		{
			left = (-t_vel*wheelDis) / (2*wheelRadius);
			right = (t_vel*wheelDis) / (2*wheelRadius);
		}

		beaglebone::WheelVelocities msg;
		msg.left = left;
		msg.right = right;
		WheelVelocities_pub.publish(msg);
	}
	
	void PlayerNode::velocityReceived(const beaglebone::WheelVelocities::ConstPtr& vel)
	{
		//not implemented		
	}

	void PlayerNode::deltaDistanceReceived(const beaglebone::WheelDistances::ConstPtr& dist)
	{
		//calculate deltadistance, value received is in cm's
		deltaDistR += ((dist -> right)/100);
		deltaDistL += ((dist -> left)/100);
	}

	void PlayerNode::publishOdometry()
	{

		ros::Time current_time = ros::Time::now();
		double dt = (current_time - last_time).toSec();
		last_time = current_time;
		double avgDistance = (deltaDistL + deltaDistR) /2.0;
		double deltaAngle = atan2((deltaDistR - deltaDistL), wheelDis);
		//set wheel delta's back to 0
		deltaDistR = 0;
		deltaDistL = 0;
		//calculate x,y delta's according to distance and angle
		double delta_x = avgDistance * cos(m_theta);
		double delta_y = avgDistance * sin(m_theta);

		//calculate x,y and theta(rotational) velocities
		double vx = avgDistance / dt;
		double vy = 0.0;
		double vth = deltaAngle / dt;

		//calculate total x,y and rotation
		m_theta += deltaAngle;
		m_x += delta_x;
		m_y += delta_y;


		geometry_msgs::Quaternion odom_quat;
		odom_quat=tf::createQuaternionMsgFromYaw(m_theta);

		//publish transform between odometry and base_footprint frames, needed to perform transformations
		//This is performed by the robot localization node and should only be performed here in case this ROS package is not used
		/*
		geometry_msgs::TransformStamped odom_trans;
		odom_trans.header.frame_id="odom";
		odom_trans.child_frame_id="base_footprint";

		current_time = ros::Time::now();
		odom_trans.header.stamp=current_time;
		odom_trans.transform.translation.x=m_x;
		odom_trans.transform.translation.y=m_y;
		odom_trans.transform.translation.z=0.0;
		odom_trans.transform.rotation=odom_quat;

		broadcaster.sendTransform(odom_trans);
		*/


		//publish robot odometry data, required for robot transformations
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time;
		odom.header.frame_id = "odom";

		odom.pose.pose.position.x = m_x;
		odom.pose.pose.position.y = m_y;
		odom.pose.pose.position.z = 0.0;
		odom.pose.pose.orientation = odom_quat;

		odom.twist.twist.linear.x = vx;
		odom.twist.twist.linear.y = vy;
		odom.twist.twist.angular.z = vth;

		odom_pub.publish(odom);
	}
}
