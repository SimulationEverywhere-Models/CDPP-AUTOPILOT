/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Diane Hould
*
*  EMAIL: mailto://dhould@connect.carleton.ca
*        *
*  DATE: 20/12/2012
*
*******************************************************************/


#include "modeladm.h"
#include "mainsimu.h"
#include "AircraftController.h"             // class AircraftController
#include "AutoPilotController.h"            // class AutoPilotController
#include "queue.h"        					// class Queue
#include "generat.h"      					// class Generator
#include "cpu.h"          					// class CPU
#include "transduc.h"     					// class Transducer
#include "trafico.h"      					// class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;

	//New Atomic models//

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AircraftController>() , "AircraftController" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AutoPilotController>() , "AutoPilotController" ) ;
}
