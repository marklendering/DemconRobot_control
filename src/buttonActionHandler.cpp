
#include "buttonActionHandler.h"

using namespace std;

namespace DemconRobot
{
	buttonActionHandler::buttonActionHandler()
	{
		MoveBaseClient ac("move_base", true);
	}
	
	buttonActionHandler::~buttonActionHandler()
	{
	}

	bool rideLine()
	{
		return false;
	}
	
	bool rideSquare()
	{
		return false;
	}
	
	bool rideTriangle()
	{
		return false;
	}
	
	bool ridePentagon()
	{
		return false;
	}



}