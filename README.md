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
* **Install SUMO(Simulation of Urban MObility)**
  * STEP 1: DOWNLOAD LATEST RELEASE VERSION OF SUMO FROM OFFICLE SITE OF SUMO http://sumo.dlr.de/wiki/Main_Page OR FROM GIVEN DIRECT LINK  http://sourceforge.net/projects/sumo/...
  * STEP 2: NEED TO INSTALL DEPENDENCIES FIRST REQUIRED FOR SUMO WORKING CORRECTLY; OPEN TERMINAL BY PRESSING "CTRL + ALT + T" AND TYPE :-   "$ sudo apt-get install libgdal1h libgdal-dev g++ libxerces-c3.1 libxerces-c-dev libicu-dev libproj-dev libfox-1.6-dev libgl1-mesa-dev   libglu1-mesa-dev python" PRESS ENTER
  * STEP 3: Decompress the tarball:(MY SUMO TAR FILE LOCATED IN MY DOWNLOAD FOLDER YOU MAY BE SOME OTHER PLACE) "cd /home/batth/Downloads"   PRESS ENTER "$ sudo tar -xzvf sumo-src-0.25.0.tar.gz" PRESS ENTER
  * STEP 4: MOVE DECOMPRESSED DIRECTORY TO "/usr/local/src": "$ sudo mv -v sumo-0.25.0 /usr/local/src" PRESS ENTER
  * STEP 5: ENTER INTO THE SOURCE DIRECTORY: "$ cd /usr/local/src/sumo-0.25.0" PRESS ENTER
  * STEP 6: FINAL COMMANDS FOR COMPLETE INSTALLATION: FIRST ONE: "$ sudo ./configure --with-fox-includes=/usr/include/fox-1.6 \ --with-   gdal-includes=/usr/include/gdal --with-proj-libraries=/usr \ --with-gdal-libraries=/usr --with-proj-gdal"
  * SECOND ONE: "$ sudo make"
  * THIRD ONE: "$ sudo make install"
  * STEP 7: YOUR INSTALATION COMPLETE NOW ENJOY USING IT BY TYPING THIS COMMAND IN TERMINAL: "$ sumo-gui"

* **Install OMNET++**
