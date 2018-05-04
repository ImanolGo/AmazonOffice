/*
 *  Sensor.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */

#include "Sensor.h"


Sensor::Sensor(int _id): m_threshold(255), m_value(-1), m_id(_id)
{
    this->setup();
}

Sensor::~Sensor()
{
    //Intentionally left empty
}

void Sensor::setup()
{
    
}

void Sensor::update()
{
    
}


