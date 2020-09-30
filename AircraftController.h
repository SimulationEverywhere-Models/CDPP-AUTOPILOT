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

#ifndef __AIRCRAFTCONTROLLER_H
#define __AIRCRAFTCONTROLLER_H

#include "atomic.h"     // class Atomic

class AircraftController : public Atomic
{
public:
	AircraftController( const string &name = "AircraftController" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &actualPitch_out ;
	Port &cmdPitch_in ;
	Time time ;
	int deltaPitch ;
	int actPitchRate ;
	int cmdPitch ;
	int actualPitch ;


};	// class AircraftController

// ** inline ** //
inline
string AircraftController::className() const
{
	return "AircraftController" ;
}

#endif   //__AIRCRAFTCONTROLLER_H
