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
#ifndef SUMOFareHandler_h
#define SUMOFareHandler_h


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <utils/xml/SUMOSAXHandler.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MsgHandler;
class SUMOVTypeParameter;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class SUMOFareHandler
 * @brief Parser for the tariff system description
 */
class SUMOFareHandler : public SUMOSAXHandler {
public:
    /// @brief standard constructor
    SUMOFareHandler(const std::string& file);

    /// @brief standard destructor
    virtual ~SUMOFareHandler();

protected:
    /// @name inherited from GenericSAXHandler
    //@{

    /** @brief Called on the opening of a tag;
     *
     * @param[in] element ID of the currently opened element
     * @param[in] attrs Attributes within the currently opened element
     * @exception ProcessError If something fails
     * @see GenericSAXHandler::myStartElement
     */
    virtual void myStartElement(int element,
                                const SUMOSAXAttributes& attrs);
    //@}

private:
    std::map<std::string, double> myPrices;
    
private:
    /// @brief Invalidated copy constructor
    SUMOFareHandler(const SUMOFareHandler& s) = delete;

    /// @brief Invalidated assignment operator
    SUMOFareHandler& operator=(const SUMOFareHandler& s) = delete;
};


#endif

/****************************************************************************/
