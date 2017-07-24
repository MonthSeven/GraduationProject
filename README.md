# Trajectory-Based Statistical Forwarding for Multihop Infrastructure-to-Vehicle Data Delivery
##### GraduationProject

##### Abstract
>This project proposes Trajectory-based Statistical Forwarding (TSF) scheme, tailored for the multihop data delivery from infrastructure nodes (e.g., Internet access points) to moving vehicles in vehicular ad hoc networks. To our knowledge, this project presents the first attempt to investigate how to effectively utilize the packet destination vehicle's trajectory for such an infrastructure-to-vehicle data delivery. This data delivery is performed through the computation of a target point based on the destination vehicle's trajectory that is an optimal rendezvous point of the packet and the destination vehicle. TSF forwards packets over multihop to a selected target point where the vehicle is expected to pass by. Such a target point is selected optimally to minimize the packet delivery delay while satisfying the required packet delivery probability. The optimality is achieved analytically by utilizing the packet's delivery delay distribution and the destination vehicle's travel delay distribution. Through theoretical analysis and extensive simulation, it is shown that our design provides an efficient data forwarding under a variety of vehicular traffic conditions.

##### Introduction
>Vehicular Ad Hoc Networks (VANETs) have recently emerged as one of promising research areas for the driving safety in road networks. As a result, the IEEE standards association has been working for wireless access in vehicular environments, standardizing Dedicated Short Range Communications (DSRC), such as IEEE 802.11p. In the meantime, the GPS technology has been adopted for navigation purposes at an unprecedented rate. It is expected that approximately 300 million GPS devices will be shipped in 2009 alone. It seems a very timely topic to develop the vehicular networking by integrating the cutting-edge DSRC and GPS technologies. Especially, our work is inspired by this current trend that a huge number of vehicles have started to install GPS-receivers for navigation and are considering DSRC devices for driving safety. The drivers are guided by these GPS-based navigation systems to select better driving paths in terms of the physically shortest path or the vehicular low-density traffic path. Therefore, one natural research question is how to make the most of these GPS-guided driving paths to improve the performance of vehicular networks......

### For setting developing environments...
1. **Install SUMO(Simulation of Urban MObility)**.

If you run debian or ubuntu, SUMO is part of the regular distribution and can be installed like this:
>sudo apt-get install sumo sumo-tools sumo-doc.

If you need a more up-to-date ubuntu version, it may be found in a separate ppa, which is added like this:
>sudo add-apt-repository ppa:sumo/stable >sudo apt-get update.

and then again
>sudo apt-get install sumo sumo-tools sumo-doc.


2. **Install OMNET++**.
