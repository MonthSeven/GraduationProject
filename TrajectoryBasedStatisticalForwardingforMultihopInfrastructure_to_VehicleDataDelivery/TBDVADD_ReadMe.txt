############# VADD (Vehicular Assisted Data Delivery ) ##############
############# TBD (Trajectory Based Data Forwarding in Light-Traffic Ad Hoc Networks)



Introduction on TBD & VADD
___________________________

This project is an implementation of both TBD and VADD. Like VADD, TBD is also based on the EDD (Expected Delivery Delay) as packet forwarding metrics.
VADD is based on best Angle while TBD is base on geographical shortest path to decide the best packet route to destination.




Simulation Environnement
_________________________

To run TBDVADD simulation requires:
- Install OMNeT++ 4.6 in lunix environment
- Install Sumo 0.22.0



Necessary Modifications
_______________________

After importing your TBDVADD project in your OMNeT++ workspace or extracting it to run it in command line environment,
You need to changee a location path of Netlane.net.xml, in ReadFile.cc function readFile(), according to your directory path toNetlane.net.xml.



Running TBD or VADD
___________________

To run TBD : Set forwardingChoice = 1 (you will using edge length based forwarding) or 2 (you will be using edge delay based forwarding)
To run VADD: Set forwardingChoice = 0 (you will using Angle based forwarding)




Enjoy the TBD and VADD Simulation in OMNeT++ environment