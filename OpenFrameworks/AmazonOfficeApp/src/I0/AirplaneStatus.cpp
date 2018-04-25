/*
 *  AirplaneStatus.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 25/04/18.
 *
 */

#include "AirplaneStatus.h"


AirplaneStatus::AirplaneStatus()
{
    this->setupPatameters();
}

AirplaneStatus::~AirplaneStatus()
{
    //Intentionally left empty
}


//--------------------------------------------------------------

void AirplaneStatus::setupPatameters()
{
    m_latitude.set("Latitude", 0.0, 0.0, 180.0);
    m_longitude.set("Longitude", 0.0, 0.0, 180.0);
    m_altitude.set("Altitude", 0.0, 0, 50000.0);
    m_velocity.set("Velocity", 0.0, 0, 1000);
    m_heading.set("Heading", 0.0, 0, 360);
    m_verticalRate.set("VerticalRate", 0, -1000.0, 1000);
}


