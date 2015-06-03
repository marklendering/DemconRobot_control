#ifndef HANDLER_H
#define HANDLER_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>


namespace DemconRobot
{
	class buttonActionHandler{
	
		typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
		public:
			buttonActionHandler();
			~buttonActionHandler();
			bool rideLine();
			bool rideSquare();
			bool rideTriangle();
			bool ridePentagon();
		private:
			

		
		
	};
}

#endif
