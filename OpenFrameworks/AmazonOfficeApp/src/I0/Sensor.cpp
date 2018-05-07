/*
 *  Sensor.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */

#include "Sensor.h"
#include "AppManager.h"

Sensor::Sensor(int _id): m_threshold(50), m_value(-1), m_id(_id), m_previousValue(0), m_standbyTime(0.3), m_ellapsedTime(0.0), m_activeSensor(false)
{
    this->setup();
}

Sensor::~Sensor()
{
    //Intentionally left empty
}

void Sensor::setup()
{
    ofLogNotice() <<"Sensor::setup << ID: " << m_id;
}

void Sensor::update()
{
    // m_ellapsedTime = m_ellapsedTime + ofGetLastFrameTime();
    if(m_activeSensor){
        m_ellapsedTime +=ofGetLastFrameTime();
        
        if(m_ellapsedTime>m_standbyTime){
            m_activeSensor = false;
        }
    }
}


void Sensor::updateValue(int value)
{
    m_value = value;
    int diff = m_value - m_previousValue;
    m_previousValue = value;
    
    this->checkOnset(diff);
    
}

void Sensor::checkOnset(int value)
{
    if(m_activeSensor){
        return;
    }
    
    //ofLogNotice() <<"Sensor::update << m_ellapsedTime: " << m_ellapsedTime;
    
    if(value > m_threshold){
        m_ellapsedTime = 0;
        m_activeSensor = true;
        this->sendOscOnset();
    }
    
}

void Sensor::sendOscOnset()
{
    string address = "amazon/arduino/norm/baldosa" + ofToString(m_id);
    
    ofLogNotice() <<"Sensor::sendOscOnset << ID: " << m_id;
    
    AppManager::getInstance().getOscManager().sendIntMessage(1, address);
}

