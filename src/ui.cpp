#include <ros/ros.h>

#include <QApplication>
#include <QWidget>
#include "mainwindow.h"

using namespace std;
using namespace DemconRobot;

int main(int argc, char** argv){
	ros::init(argc, argv, "RosGui");
	ros::NodeHandle n;
	
	n.ok();
	
	QApplication app(argc, argv);
	
	MainWindow w;
	w.setWindowTitle("ROS gui");
	w.show();
	
	return app.exec();
}