/*
 *  AirplaneStatus.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 25/04/18.
 *
 */



#pragma once

#include "ofMain.h"

//===================+==== class AirplaneStatus =============================
//==============================================================================
/** \class AirplaneStatus AirplaneStatus.h
 *	\brief class holding the current status of an airplane
 *	\details It reads and organizes all the data of a current airplane on flight
 */


class AirplaneStatus
{

public:
    //! Constructor
    AirplaneStatus();

    //! Destructor
    virtual ~AirplaneStatus();

    string getLatitude() const { return ofToString(m_latitude) + "°";}
    string getLongitude() const { return ofToString(m_longitude) + "°";}
    string getAltitude() const { return ofToString(m_altitude) + "m";}
    string getVelocity() const { return ofToString(m_velocity) + "m/s";}
    string getHeading() const { return ofToString(m_velocity) + "°";}
    string getVerticalRate() const { return ofToString(m_verticalRate) + "m/s";}
    
 
private:
    
    void setupPatameters();
    
public:
    
    string              m_callsign;
    ofParameter<float>  m_latitude;
    ofParameter<float>  m_longitude;
    ofParameter<float>  m_altitude;
    ofParameter<float>  m_velocity;
    ofParameter<float>  m_heading;
    ofParameter<float>  m_verticalRate;

};

