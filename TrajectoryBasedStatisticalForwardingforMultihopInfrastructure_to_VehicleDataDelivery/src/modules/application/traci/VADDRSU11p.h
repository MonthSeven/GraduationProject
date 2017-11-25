//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef TraCIDemoRSU11p_H
#define TraCIDemoRSU11p_H

#include "VADDBaseWaveApplLayer.h"
#include "modules/world/annotations/AnnotationManager.h"
#include "modules/mobility/traci/TraCIMobility.h"

using Veins::AnnotationManager;

/**
 * Small RSU Demo using 11p
 */
class VADDRSU11p : public VADDBaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
    protected:
        AnnotationManager* annotations;
        BaseMobility* mobi;
        bool sentMessage;
    protected:
        virtual void onBeacon(multipleRSUsRTpkt* pkts);
        virtual void onData(multipleRSUsRTpkt* pkts);
        void sendMessage(std::string blockedRoadId);
        virtual void sendpkts(multipleRSUsRTpkt* pkts);
};
#endif
