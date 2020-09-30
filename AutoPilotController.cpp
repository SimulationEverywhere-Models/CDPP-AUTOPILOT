/*******************************************************************
 *
 *  DESCRIPTION: Atomic Model AutoPilotController
 *
 *  AUTHOR: Diane Hould
 *
 *  EMAIL: mailto://dhould@connect.carleton.ca
 *        *
 *  DATE: 20/12/2012
 *
 *******************************************************************/

/** include files **/
#include "AutoPilotController.h"     // class AutoPilotController
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
 * Function Name: AutoPilotController
 * Description: Constructor
 ********************************************************************/
AutoPilotController::AutoPilotController( const string &name )
: Atomic( name )
, desiredPitch_in( addInputPort( "desiredPitch_in" ) )
, actualPitch_in( addInputPort( "actualPitch_in" ) )
, cmdPitch_out( addOutputPort( "cmdPitch_out" ) )

{
}

/*******************************************************************
 * Function Name: initFunction
 * Description: Initialize pitches
 ********************************************************************/
Model &AutoPilotController::initFunction()
{
	lastDeltaPitch = 0 ;
	lastIC = 0 ;
	cmdPitch = 0 ;
	actualPitch = 0 ;
	desiredPitch = 0 ;
	time = (0, 0, 0, 1) ;
	return *this ;
}

/*******************************************************************
 * Function Name: externalFunction
 * Description: When external input occurs calculate the delta pitch, otherwise do nothing
 ********************************************************************/
Model &AutoPilotController::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == desiredPitch_in )

		desiredPitch == msg.value() ;

		if((desiredPitch < -50) && (desiredPitch > 40))		//ensure pitch is within elevator position range

		if(msg.port() == actualPitch_in )
		{
			actualPitch == msg.value() ;
		}
		deltaPitch = desiredPitch - actualPitch ;
		holdIn(active, time) ;

		//else
		//{
			//deltaPitch = desiredPitch - actualPitch ;
			//holdIn(passive, time) ;
		//}

	return *this ;
}

/*******************************************************************
 * Function Name: internalFunction
 * Description: Change the state to active when no_correction_factor
 ********************************************************************/
Model &AutoPilotController::internalFunction( const InternalMessage & )
{
	if( deltaPitch >= 1 )									//zero band to prevent oscillation
		{
			dt = 0.1 ;
			ku = 0.5 ;
			pu = 20	;										//ku and pu are the values that need to be tuned
			pg = 0.60*ku ;     								//where pg is the proportional gain
			ig = 1.20*(ku/pu) ;   							//where ig is the integral gain
			dg = 0.075*(ku*pu) ;     						//where dg is the derivative gain
			pc = pg*deltaPitch ;  							//where pc is the proportional component
			dc = dg*((deltaPitch - lastDeltaPitch)/dt) ;    //where dc is the derivative component
			ic = ((1-dt)*lastIC) + (ig*deltaPitch*dt) ; 	//where ic is the integral component
			cmdPitch = pc + ic + dc ;
			lastIC = ic ;
			lastDeltaPitch = deltaPitch ;
			passivate() ;
		}
	if( deltaPitch <= -1)									//zero band to prevent oscillation
		{
			dt = 0.1 ;
			ku = 0.5 ;
			pu = 20	;										//ku and pu are the values that need to be tuned
			pg = 0.60*ku ;     								//where pg is the proportional gain
			ig = 1.20*(ku/pu) ;   							//where ig is the integral gain
			dg = 0.075*(ku*pu) ;     						//where dg is the derivative gain
			pc = pg*deltaPitch ;  							//where pc is the proportional component
			dc = dg*((deltaPitch - lastDeltaPitch)/dt) ;    //where dc is the derivative component
			ic = ((1-dt)*lastIC) + (ig*deltaPitch*dt) ; 	//where ic is the integral component
			cmdPitch = pc + ic + dc ;
			lastIC = ic ;
			lastDeltaPitch = deltaPitch ;
			passivate() ;
		}
		else
		{
			cmdPitch = actualPitch ;
			passivate() ;
		}
		return *this;
}
/*******************************************************************
 * Function Name: outputFunction
 * Description:  Send correction_factor when in display
 ********************************************************************/
Model &AutoPilotController::outputFunction( const InternalMessage &msg )
{
		sendOutput( msg.time(), cmdPitch_out, cmdPitch ) ;

		return *this ;
}
