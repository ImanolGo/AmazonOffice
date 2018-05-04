/*
 *  Sensor.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */



#pragma once

#include "ofMain.h"

//===================+==== class Sensor =============================
//==============================================================================
/** \class Sensor Sensor.h
 *	\brief class holding the current traffic status
 *	\details It represents the traffic flow at a certain point on a street
 */


class Sensor
{

public:
    //! Constructor
    Sensor(int _id);

    //! Destructor
    virtual ~Sensor();

    void update();
    
    void setThreshold(int value){m_threshold = value;}
    
    
private:
    
    void setup();
    
private:
    
    int                 m_threshold;
    int                 m_value;
    int                 m_id;
   
};

