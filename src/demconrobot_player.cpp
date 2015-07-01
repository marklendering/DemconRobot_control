#include <ros/ros.h>
#include <player_node.h>
#include <math.h>

using namespace std;
using namespace DemconRobot;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "Driver");

	PlayerNode demconRobotPlayer;
	ros::NodeHandle n;

	if(demconRobotPlayer.start()!= 0){
		exit(-1);
	}


	ros::Rate loop_rate(120); 

	while(n.ok()){
		ros::spinOnce();	
		demconRobotPlayer.doUpdate();
		loop_rate.sleep();
	}

	demconRobotPlayer.stop();

	return(0);


}
