/*
 *  TrafficStatus.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 26/04/18.
 *
 */



#pragma once

#include "ofMain.h"

//===================+==== class TrafficStatus =============================
//==============================================================================
/** \class TrafficStatus TrafficStatus.h
 *	\brief class holding the current traffic status
 *	\details It represents the traffic flow at a certain point on a street
 */


class TrafficStatus
{

public:
    //! Constructor
    TrafficStatus();

    //! Destructor
    virtual ~TrafficStatus();

    string getLatitude() const { return ofToString(m_latitude) + "°";}
    string getLongitude() const { return ofToString(m_longitude) + "°";}
    string getSpeed() const { return ofToString(m_speed) + "kmph";}
    
    float getSpeedNorm();
    
    void setSpeedMax(float value);
    
    
private:
    
    void setupPatameters();
    
public:
    
    string              m_name;
    string              m_url;
    ofParameter<float>  m_latitude;
    ofParameter<float>  m_longitude;
    ofParameter<float>  m_speed;
   

};

