/*******************************************************************
 *
 *  DESCRIPTION: AutoPilot Controller
 *
 *  AUTHOR: Diane Hould
 *
 *  EMAIL: dhould@connect.carleton.ca
 *
 *
 *  DATE: 20/12/2012
 *
 *******************************************************************/
#ifndef __AUTOPILOTCONTROLLER_H
#define __AUTOPILOTCONTROLLER_H

#include "atomic.h"     // class Atomic

class AutoPilotController : public Atomic
{
public:
	AutoPilotController( const string &name = "AutoPilotController" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );


private:

	Port &cmdPitch_out ;
	Port &desiredPitch_in ;
	Port &actualPitch_in ;
	Time time;

	double dt ;
	double ku ;
	double pu ;
	double pg ;
	double ig ;
	double dg ;
	double pc ;
	double dc ;
	double ic ;
	double lastIC;
	double cmdPitch ;
	double deltaPitch ;
	double lastDeltaPitch ;
	double actualPitch ;
	double desiredPitch ;

};	// class AutoPilotController

// ** inline ** //
inline
string AutoPilotController::className() const
{
	return "AutoPilotController" ;
}

#endif   //__AUTOPILOTCONTROLLER_H
