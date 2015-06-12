cmake_minimum_required(VERSION 2.8.3)
project(beaglebone)

find_package(catkin REQUIRED COMPONENTS 
	roscpp rospy rostest std_msgs tf tf2
	message_generation geometry_msgs sensor_msgs
)
find_package(Boost REQUIRED)


find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
include(${QT_USE_FILE})

add_message_files(
  DIRECTORY
  msg
  FILES
  IMU.msg
  LRS.msg
  WheelVelocities.msg
  WheelDistances.msg
)

#add_service_files(
#  FILES
#)


generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime roscpp )

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${QT_LIBRARIES})



#sensor and motor drivers
add_executable(MotionSensorDriver src/demconrobot_MotionSensorDriver.cpp)
add_library(Driver src/MotionSensorDriver.cpp src/CanDriver.cpp)
target_link_libraries(MotionSensorDriver Driver)
target_link_libraries(MotionSensorDriver ${catkin_LIBRARIES})
target_link_libraries(MotionSensorDriver ${Boost_LIBRARIES})
add_dependencies(MotionSensorDriver beaglebone_gencpp)
add_dependencies(Driver beaglebone_gencpp)

#robot controller

add_executable(RobotController src/demconrobot_player.cpp) 
add_library(Player src/player_node.cpp)
target_link_libraries(RobotController Player)
target_link_libraries(RobotController ${catkin_LIBRARIES})
target_link_libraries(RobotController ${Boost_LIBRARIES})
add_dependencies(RobotController beablebone_gencpp)

####user interface####
SET(beaglebone_SRCS
	src/mainwindow.cpp
)
SET(beaglebone_HDRS
	src/mainwindow.h
	src/ui_mainwindow.h
)
qt4_wrap_cpp(cpp_MOCS ${beaglebone_HDRS})
add_executable(ui src/ui.cpp src/mainwindow.cpp)
add_library(qt ${cpp_MOCS} ${beaglebone_HDRS})
target_link_libraries(ui qt)
target_link_libraries(ui ${QT_LIBRARIES} ${catkin_LIBRARIES} ${Boost_LIBRARIES})



