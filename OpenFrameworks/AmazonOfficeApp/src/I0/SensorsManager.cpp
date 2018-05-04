/*
 *  SensorsManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */


#include "SensorsManager.h"
#include "AppManager.h"


SensorsManager::SensorsManager(): Manager()
{
    //Intentionally left empty
}

SensorsManager::~SensorsManager()
{
    ofLogNotice() << "SensorsManager::destructor";
}


//--------------------------------------------------------------

void SensorsManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    this->setupSensors();
    
    ofLogNotice() <<"SensorsManager::initialized" ;
}

void SensorsManager::setupSensors()
{

}


void SensorsManager::update()
{
    this->updateSensors();
}

void SensorsManager::updateSensors()
{
   
}
