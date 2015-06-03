#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <QMainWindow>
#include "buttonActionHandler.h"
#include <iostream>
#include <vector>
#include <string>


	namespace Ui {
	class MainWindow;
	}


	class MainWindow : public QMainWindow
	{
		//typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
        Q_OBJECT

	public:
        explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		//buttonActionHandler *handler; // = new buttonActionHandler;

	private slots:
		void on_lineButton_clicked();

		void on_squareButton_clicked();

		void on_triangleButton_clicked();

		void on_pentagonButton_clicked();

		void on_stopButton_clicked();

		void on_reset_button_clicked();

	private:
		Ui::MainWindow *ui;
		boost::thread spin_thread;
		bool stopSet = false;
		
		void handleButton(std::vector<move_base_msgs::MoveBaseGoal> goals);
		double radians (double d);
		
		
	};

#endif // MAINWINDOW_H
