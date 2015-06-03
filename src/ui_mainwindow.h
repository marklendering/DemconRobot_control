/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTextBrowser>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

	class Ui_MainWindow
	{
	public:
		QWidget *centralWidget;
		QWidget *verticalLayoutWidget;
		QVBoxLayout *verticalLayout;
		QPushButton *lineButton;
		QPushButton *squareButton;
		QPushButton *triangleButton;
		QPushButton *pentagonButton;
		QTextBrowser *textBrowser;
		QPushButton *reset_button;
		QPushButton *stopButton;
		QMenuBar *menuBar;
		QToolBar *mainToolBar;
		QStatusBar *statusBar;

		void setupUi(QMainWindow *MainWindow)
		{
			if (MainWindow->objectName().isEmpty())
				MainWindow->setObjectName("MainWindow");
			MainWindow->resize(549, 375);
			centralWidget = new QWidget(MainWindow);
			centralWidget->setObjectName("centralWidget");
			verticalLayoutWidget = new QWidget(centralWidget);
			verticalLayoutWidget->setObjectName("verticalLayoutWidget");
			verticalLayoutWidget->setGeometry(QRect(20, 10, 160, 251));
			verticalLayout = new QVBoxLayout(verticalLayoutWidget);
			verticalLayout->setSpacing(6);
			verticalLayout->setContentsMargins(11, 11, 11, 11);
			verticalLayout->setObjectName("verticalLayout");
			verticalLayout->setContentsMargins(0, 0, 0, 0);
			lineButton = new QPushButton(verticalLayoutWidget);
			lineButton->setObjectName("lineButton");

			verticalLayout->addWidget(lineButton);

			squareButton = new QPushButton(verticalLayoutWidget);
			squareButton->setObjectName("squareButton");

			verticalLayout->addWidget(squareButton);

			triangleButton = new QPushButton(verticalLayoutWidget);
			triangleButton->setObjectName("triangleButton");

			verticalLayout->addWidget(triangleButton);

			pentagonButton = new QPushButton(verticalLayoutWidget);
			pentagonButton->setObjectName("pentagonButton");

			verticalLayout->addWidget(pentagonButton);

			textBrowser = new QTextBrowser(centralWidget);
			textBrowser->setObjectName("textBrowser");
			textBrowser->setGeometry(QRect(200, 10, 331, 251));
			reset_button = new QPushButton(centralWidget);
			reset_button->setObjectName("reset_button");
			reset_button->setGeometry(QRect(430, 280, 99, 27));
			stopButton = new QPushButton(centralWidget);
			stopButton->setObjectName("stopButton");
			stopButton->setGeometry(QRect(320, 280, 99, 27));
			MainWindow->setCentralWidget(centralWidget);
			menuBar = new QMenuBar(MainWindow);
			menuBar->setObjectName("menuBar");
			menuBar->setGeometry(QRect(0, 0, 549, 25));
			MainWindow->setMenuBar(menuBar);
			mainToolBar = new QToolBar(MainWindow);
			mainToolBar->setObjectName("mainToolBar");
			MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
			statusBar = new QStatusBar(MainWindow);
			statusBar->setObjectName("statusBar");
			MainWindow->setStatusBar(statusBar);

			retranslateUi(MainWindow);

			QMetaObject::connectSlotsByName(MainWindow);
		} // setupUi

		void retranslateUi(QMainWindow *MainWindow)
		{
			MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
			lineButton->setText(QApplication::translate("MainWindow", "Line", 0));
			squareButton->setText(QApplication::translate("MainWindow", "Square", 0));
			triangleButton->setText(QApplication::translate("MainWindow", "Triangle", 0));
			pentagonButton->setText(QApplication::translate("MainWindow", "Pentagon", 0));
			reset_button->setText(QApplication::translate("MainWindow", "Reset text", 0));
			stopButton->setText(QApplication::translate("MainWindow", "Stop Robot", 0));
		} // retranslateUi

	};

	namespace Ui {
		class MainWindow: public Ui_MainWindow {};
	} // namespace Ui


QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
