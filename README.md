# Trajectory-Based Statistical Forwarding for Multihop Infrastructure-to-Vehicle Data Delivery


##### Abstract
>This project proposes _Trajectory-based Statistical Forwarding_ (TSF) scheme, tailored for the multihop data delivery from infrastructure nodes (e.g., Internet access points) to moving vehicles in vehicular ad hoc networks. To our knowledge, this project presents the first attempt to investigate how to effectively utilize the packet destination vehicle's trajectory for such an infrastructure-to-vehicle data delivery. This data delivery is performed through the computation of a target point based on the destination vehicle's trajectory that is an optimal rendezvous point of the packet and the destination vehicle. TSF forwards packets over multihop to a selected target point where the vehicle is expected to pass by. Such a target point is selected optimally to minimize the packet delivery delay while satisfying the required packet delivery probability. The optimality is achieved analytically by utilizing the packet's delivery delay distribution and the destination vehicle's travel delay distribution.


##### Introduction
>Vehicular Ad Hoc Networks (VANETs) have recently emerged as one of promising research areas for the driving safety in road networks. As a result, the IEEE standards association has been working for wireless access in vehicular environments, standardizing Dedicated Short Range Communications (DSRC), such as IEEE 802.11p. In the meantime, the GPS technology has been adopted for navigation purposes at an unprecedented rate. It seems a very timely topic to develop the vehicular networking by integrating the cutting-edge DSRC and GPS technologies. The drivers are guided by these GPS-based navigation systems to select better driving paths in terms of the physically shortest path or the vehicular low-density traffic path. Therefore, one natural research question is how to make the most of these GPS-guided driving paths to improve the performance of vehicular networks.

> Let’s consider the scenario 1) where a Traffic Control Center (TCC) collects road network condition and maintains the trajectories of vehicles to want such up-to-date condition and 2) where Access Points (APs) sparsely deployed in road networks are interconnected with
each other along with the Traffic Control Center. These APs are used to provide individual vehicles with customized driving path information, such as driving hazards (e.g., holes, bumps, and slippery spots), accidents, and congested areas. With the customized driving path information, each individual vehicle can select another roadway (or lane) to escape from the possible dangerous situations for the driving safety or compute another travel path to lead to the more efficient driving for the further congested areas.
This individually customized driving path information needs to be delivered from the Traffic Control Center to each packet destination vehicle via APs. Rather than the broadcast data delivery approach of road network condition, the unicast data delivery approach is preferred in terms of data traffic volume. This is because vehicles have different trajectories and so they do need the driving path
information only along their trajectory. Since the APs have the limited communication coverage, the infrastructure-to-vehicle data delivery can be supported using vehicular ad-hoc networks to bridge the APs and the packet destination vehicles. However, due to the dynamic mobility in the road networks, the Disruption Tolerant Networking (DTN) is required for data delivery in vehicular networks. For
vehicular DTN, state-of-the-art schemes have adopted the carry-and-forward approach and have demonstrated their effectiveness in the data forwarding from a moving source (e.g., vehicle) to a stationary destination (e.g., AP). However, these schemes are not designed for the infrastructure-to-vehicle data delivery (called reverse data forwarding). This reverse data forwarding is more challenging because the packet destination is moving during the packet delivery. For this forwarding, the packet destination position needs to be accurately
estimated considering the temporal-and-spatial rendezvous of the packet and the destination vehicle. 

> To the best of our knowledge, our Trajectory-based Statistical Forwarding (TSF) is the first work to investigate the reverse data forwarding based on the vehicle trajectory guided by GPS-based navigation systems for the efficient-and-safe driving. To ensure the rendezvous of a packet and a destination vehicle, an optimal target point is identified as a packet destination position in the road
network in order to minimize the packet delivery delay while satisfying the user-required packet delivery probability. In order to search such an optimal target point, our key idea is to use the two delay distributions: 1) the packet delivery delay distribution from the AP to the target point and 2) the vehicle travel delay distribution from the destination vehicle’s current position to the target point. Once the target point is decided, our TSF adopts the source routing technique, i.e., forwards the packet toward the target point by using the shortest delay forwarding path specified by multiple intersections in the target road network. Our intellectual contributions are as follows: 
> * An infrastructure-to-vehicle data delivery architecture
> * The delay modeling for packet and vehicle
> * An optimal target point selection algorithm


### For setting developing environments...
1. **Install SUMO(Simulation of Urban MObility)**.

2. **Install OMNET++**.

3. **Install Veins**.

4. **For futher infomation, check (Part1_Installation, and so on...)**



## Korean

##### 개요
>Vehicular Ad Hoc Networks (VANETs)는 현재 도로 네트워크에서 운전 안전을 위한 영역에서 가장 떠오르는 주제입니다. 현재 Vehicle-to-Infrastructure을 위한 scheme은 연구 되어있는 상황이지만, Infrastructure-to-Vehicle을 위한 연구는 끊임없이 움직이는 차량에 어려움을 겪고 있습니다. 이에 차량의 궤적(Trajectory)를 통해 미리 차량이 갈 곳(Rendezvous)에 data를 전송하여 Infrastructure-to-Vehicle를 구현할 수 있는 scheme을 연구하고 구현을 시도하였습니다.


##### 시스템 구성
![ss1](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/system1.jpg?raw=true)

1. **Destination Vehicle:** 
>Destination Vehicle은 자신의 Trajectory 정보를 AP(Access Point)에 전송합니다.

2. **Trajectory:** 
>Relay Node 2 -> 3 -> 4 -> 5 -> 10 -> 15 -> 20

3. **Source Vehicle:** 
>Source Vehicle은 전달할 정보를 Expected Packet-Delivery Delay를 계산하여 좀 더 빠르게 전달 가능한 AP에 전달합니다.(위 그림에서는 AP1)

4. **Expected Packet-Delivery Delay:**
![ss2](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/system2.png?raw=true)
![ss3](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/system3.png?raw=true)

5. **AP1 (Access Point):** 
>AP1은 Destination Vehicle의 trajectory를 고려하여 Target Point로 data를 전송합니다.

6. **Target Point:** 
>미리 도착한 data는 Relay Node에서 holding 되었다가 Target Point(Rendezvous)를 지나는 Destination Vehicle에게 전송됩니다.


##### 구현해야할 것
1. **Implementation of Target Point Selection**
>Based on delivery probability that the packet will arrive earlier than the destination vehicle at the target point Can be computed by (1) packet's delivery delay distribution (2) destination vehicle's travel delay distribution
![ss6](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/sys6.png?raw=true)

![sssdf](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss1.png?raw=true)
![ddd](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss2.png?raw=true)
![df](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss3.png?raw=true)
![ddds](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss4.png?raw=true)

2. **Implementation of Packet Transmission toward to Target Point**
![x](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss5.png?raw=true)
![ssxxx](https://github.com/HyunJunKwon/GraduationProject/blob/master/TrajectoryBasedStatisticalForwardingforMultihopInfrastructure_to_VehicleDataDelivery/screenshots/ss6.png?raw=true)
3. **Implementation of Packet Transmission from Target Point to Vehicle**


