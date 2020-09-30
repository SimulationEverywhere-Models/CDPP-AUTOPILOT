/*******************************************************************
 *
 *  DESCRIPTION: Atomic Model AircraftController
 *
 *  AUTHOR: Diane Hould
 *
 *  EMAIL: mailto://dhould@connect.carleton.ca
 *        *
 *  DATE: 20/12/2012
 *
 *******************************************************************/

/** include files **/
#include "AircraftController.h"     // class AircraftController
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
 * Function Name: AircraftController
 * Description: Constructor
 ********************************************************************/
AircraftController::AircraftController( const string &name )
: Atomic( name )
, cmdPitch_in( addInputPort( "cmdPitch_in" ) )
, actualPitch_out( addOutputPort( "actualPitch_out" ) )

{
}

/*******************************************************************
 * Function Name: initFunction
 * Description: Initialize variables
 ********************************************************************/
Model &AircraftController::initFunction()
{
	actualPitch = 0 ;
	cmdPitch = 0 ;
	time = (0, 0, 0, 1) ;
	return *this ;
}

/*******************************************************************
 * Function Name: externalFunction
 * Description: When external input occurs, reacts.
 ********************************************************************/
Model &AircraftController::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == cmdPitch_in )
			{
				cmdPitch = msg.value() ;
				holdIn(active, time)  ;
			}
				else
				{
					cmdPitch = actualPitch ;
					holdIn(passive, time);
				}

		return *this ;
}

	/*******************************************************************
	 * Function Name: internalFunction
	 * Description: Move aircraft controls by calculating the actualPitch
	 ********************************************************************/
	Model &AircraftController::internalFunction( const InternalMessage & )
	{
		deltaPitch = cmdPitch - actualPitch ;

		if (deltaPitch > 0.5)
			{
			actPitchRate = 0.01 ;
			}
		if (deltaPitch  > -0.5)
			{
			actPitchRate = 0.01 ;
			}
		if (deltaPitch  < 0.5)
			{
			if (deltaPitch < -0.5)
				{
					actPitchRate = 0.0 ;
				}
			}
		actualPitch = actualPitch + actPitchRate ;

		return *this;
	}
	/*******************************************************************
	 * Function Name: outputFunction
	 * Description:  Send actualPitch out
	 ********************************************************************/
	Model &AircraftController::outputFunction( const InternalMessage &msg )
	{
		sendOutput( msg.time(), actualPitch_out , actualPitch );

		return *this ;
	}

