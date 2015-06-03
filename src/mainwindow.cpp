
//#include <actionlib/client/simple_action_client.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tf/transform_broadcaster.h>
#include <boost/thread.hpp>


using namespace std;

	typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
	
	MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow)
	{
		ui->setupUi(this);


	}

	MainWindow::~MainWindow()
	{
		delete ui;
	}

	void MainWindow::on_lineButton_clicked()
	{
		
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header.frame_id = "base_footprint";
		goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        vector<move_base_msgs::MoveBaseGoal> goals;
        goals.push_back(goal);
		ui->textBrowser->append("started Line task");
		boost::thread spin_thread(&MainWindow::handleButton, this, goals);
        //handleButton(goals);
        
	}

	void MainWindow::on_squareButton_clicked()
	{
		vector<move_base_msgs::MoveBaseGoal> goals;
		
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header.frame_id = "base_footprint";
		goal.target_pose.header.stamp = ros::Time::now();
		
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal);
		
		move_base_msgs::MoveBaseGoal goal1;
		goal1.target_pose.header.frame_id = "base_footprint";
		goal1.target_pose.header.stamp = ros::Time::now();
		
		goal1.target_pose.pose.position.x = 0.0;
		goal1.target_pose.pose.position.y = -1.0;
        goal1.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal1);
		
		move_base_msgs::MoveBaseGoal goal2;
		goal2.target_pose.header.frame_id = "base_footprint";
		goal2.target_pose.header.stamp = ros::Time::now();
		
		goal2.target_pose.pose.position.x = -1.0;
		goal2.target_pose.pose.position.y = 0.0;
        goal2.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal2);
		
		move_base_msgs::MoveBaseGoal goal3;
		goal3.target_pose.header.frame_id = "base_footprint";
		goal3.target_pose.header.stamp = ros::Time::now();
		
		goal3.target_pose.pose.position.x = 0.0;
		goal3.target_pose.pose.position.y = 1.0;
        goal3.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal3);
		ui->textBrowser->append("started Square task");
		boost::thread spin_thread(&MainWindow::handleButton, this, goals);
        //handleButton(goals);
        
	}

	void MainWindow::on_triangleButton_clicked()
	{
		vector<move_base_msgs::MoveBaseGoal> goals;
		
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header.frame_id = "base_footprint";
		goal.target_pose.header.stamp = ros::Time::now();
		
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal);
		
		move_base_msgs::MoveBaseGoal goal1;
		goal1.target_pose.header.frame_id = "base_footprint";
		goal1.target_pose.header.stamp = ros::Time::now();
		
		goal1.target_pose.pose.position.x = -0.5;
		goal1.target_pose.pose.position.y = -1.0;
        goal1.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal1);
		
		move_base_msgs::MoveBaseGoal goal2;
		goal2.target_pose.header.frame_id = "base_footprint";
		goal2.target_pose.header.stamp = ros::Time::now();
		
		goal2.target_pose.pose.position.x = -0.5;
		goal2.target_pose.pose.position.y = 1.0;
        goal2.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(radians(0));
        goals.push_back(goal2);
		
		ui->textBrowser->append("started Triangle task");
		spin_thread = boost::thread(&MainWindow::handleButton, this, goals);
	}

	void MainWindow::on_pentagonButton_clicked()
	{

	}

	void MainWindow::on_stopButton_clicked()
	{
		stopSet = true;
		MoveBaseClient ac("move_base", true);
		ac.cancelAllGoals();
		ui->textBrowser->append("canceled goal");
	}

	void MainWindow::on_reset_button_clicked()
	{
		ui->textBrowser->clear();
	}

    void MainWindow::handleButton(vector<move_base_msgs::MoveBaseGoal> goals)
	{
        MoveBaseClient ac("move_base", true);
        while(!ac.waitForServer(ros::Duration(5.0)) && stopSet== false)
			ui->textBrowser->append("waiting for Action server to come online");

		if(stopSet)
			return;
        for(int i=0; i < goals.size(); i++)
        {
            ui->textBrowser->append("starting new goal");
            ac.sendGoal(goals[i]); //, ros::Duration(6.0), ros::Duration(4.0)
            ac.waitForResult();


            if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                ui->textBrowser->append("Goal reached succesfully");
            else
            {
                ui->textBrowser->append("Failed to reach goal:");
                QString str = QString::fromStdString(ac.getState().toString());
                ui->textBrowser->append(str);
            }
        }
	}

    double MainWindow::radians (double d) {
    return d * M_PI / 180;
    }
	

//TODO make function that is called from the button event. 
//This method receives a set of coordinates to which it has to move. It will start a thread in which it will run untill the robot reaches it location.



