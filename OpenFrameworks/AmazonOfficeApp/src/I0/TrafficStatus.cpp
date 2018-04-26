/*
 *  TrafficStatus.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 26/04/18.
 *
 */

#include "TrafficStatus.h"


TrafficStatus::TrafficStatus()
{
    this->setupPatameters();
}

TrafficStatus::~TrafficStatus()
{
    //Intentionally left empty
}


//--------------------------------------------------------------

void TrafficStatus::setupPatameters()
{
    m_latitude.set("Latitude", 0.0, 0.0, 180.0);
    m_longitude.set("Longitude", 0.0, 0.0, 180.0);
    m_speed.set("Altitude", 0.0, 0, 120);
}


void TrafficStatus::setSpeedMax(float value)
{
    m_speed.setMax(value);
}

float TrafficStatus::getSpeedNorm()
{
    return ofMap(m_speed, m_speed.getMin(), m_speed.getMax(), 0.0, 1.0,true);
}
