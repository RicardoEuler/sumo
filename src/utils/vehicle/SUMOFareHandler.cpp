/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    SUMOFareHandler.h
/// @author  Michael Behrisch
/// @date    19 Jan 2020
///
// Parser for the tariff system description
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <utils/router/FareModule.h>
#include "SUMOFareHandler.h"


// ===========================================================================
// method definitions
// ===========================================================================

SUMOFareHandler::SUMOFareHandler(const std::string& file, FareModule* fareModule)
 : SUMOSAXHandler(file), myFareModule(fareModule) {
}


SUMOFareHandler::~SUMOFareHandler() {
}


void
SUMOFareHandler::myStartElement(int element, const SUMOSAXAttributes& attrs) {
/* preliminary structure of the input file
<fares>
    <ticket id="" name="" type="" cost=""/>
    name is the long name, type is the name, cost is the price

    <condition id="" comparator="" key="" value=""/> 
    comparator is one of "eq", "ne", "lt", "le", "gt", "ge"
    key is the attribute name and is one of "distance", "numStops", "numZones", "transfer", "symbol"

    <change from="" to="" conditions=""/> 
</fares>
*/

    switch (element) {
        case SUMO_TAG_TICKET:
            myFareModule->addTicket(attrs.getString(SUMO_ATTR_ID), attrs.getFloat(SUMO_ATTR_COST));
            break;
        case SUMO_TAG_CONDITION:
            myConditions[attrs.getString(SUMO_ATTR_ID)] = std::make_shared<FareCondition>(attrs.getString(SUMO_ATTR_COMPARATOR), attrs.getString(SUMO_ATTR_KEY), attrs.getFloat(SUMO_ATTR_VALUE));
            break;
        case SUMO_TAG_CHANGE: {
            std::vector<std::shared_ptr<FareCondition> > conditions;
            for (const std::string& condID : attrs.getStringVector(SUMO_ATTR_CONDITIONS)) {
                conditions.push_back(myConditions[condID]);
            }
            myFareModule->addChange(attrs.getString(SUMO_ATTR_FROM), attrs.getString(SUMO_ATTR_TO), conditions);
            break;
        }
    }
}


/****************************************************************************/
