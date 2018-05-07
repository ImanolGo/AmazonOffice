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
    ~Sensor();

    void update();
    
    void setThreshold(int value){m_threshold = value;}
    
    void setStandbyTime(double value){m_standbyTime = value;}
    
    void updateValue(int value);
    
    int getId() const {return m_id;}
    
private:
    
    void setup();
    
    void checkOnset(int value);
    
    void sendOscOnset();
    
private:
    
    int                 m_threshold;
    int                 m_value;
    int                 m_previousValue;
    int                 m_id;
    bool                m_activeSensor;
    double              m_standbyTime;
    double              m_ellapsedTime;
   
};

