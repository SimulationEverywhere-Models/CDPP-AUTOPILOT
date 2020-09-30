[top]
components : AutoPilotController AircraftController 
out : actualPitch_out 
in : desiredPitch_in 
Link : desiredPitch_in desiredPitch_in@AutoPilotController
Link : actualPitch_out@AircraftController actualPitch_in@AutoPilotController
Link : cmdPitch_out@AutoPilotController  cmdPitch_in@AircraftController
Link : actualPitch_out@AircraftController actualPitch_out

[AutoPilotController]
components : AutoPilotController@AutoPilotController 
out : cmdPitch_out 
in : desiredPitch_in actualPitch_in 

[AutoPilotController]
time : 00:00:00:100 


[AircraftController]
components : AircraftController@AircraftController
out : actualPitch_out 
in : cmdPitch_in 

[AircraftController]
time : 00:00:00:100  



