# IPv6 Neighbor Discovery for Prefix and Service Discovery in Vehicular Networks
##### GraduationProject

>I will proposes an extension of IPv6 neighbor discovery (ND) for rapid network prefix and service discovery in
vehicular networks. It is assumed that a vehicle as a moving network (MN) or a road-side unit (RSU) as a fixed network (FN) has
an external network interface, and hosts in an MN periodically announce their services to their local DNS Server called recursive
DNS server (RDNSS) of the MN. We define new options for prefix and service discovery in IPv6 ND through which an MN or an
FN can fast exchange prefix and service information by sending the neighbor solicitation (NS) and neighbor advertisement (NA)
messages containing a sender’s prefix and service information. 
Through theoretical analysis comparing our proposed method with conventional methods separating prefix discovery and service
discovery, our approach can reduce the delay of the prefix and service discovery to provide better intelligent transportation
services (e.g., cooperative adaptive cruise control for collision avoidance) in vehicular environment.

### For setting developing environments...
1. **Install SUMO(Simulation of Urban MObility)**.

If you run debian or ubuntu, SUMO is part of the regular distribution and can be installed like this:
>sudo apt-get install sumo sumo-tools sumo-doc.

If you need a more up-to-date ubuntu version, it may be found in a separate ppa, which is added like this:
>sudo add-apt-repository ppa:sumo/stable >sudo apt-get update.

and then again
>sudo apt-get install sumo sumo-tools sumo-doc.


2. **Install OMNET++**.
