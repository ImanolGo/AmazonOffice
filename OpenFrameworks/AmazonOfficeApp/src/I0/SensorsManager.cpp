/*
 *  SensorsManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */


#include "SensorsManager.h"
#include "AppManager.h"

const int SensorsManager::NUM_SENSORS = 3;

SensorsManager::SensorsManager(): Manager(), m_pirCounter(0.0), m_previousPirValue(-1)
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
    for(int i=0; i<NUM_SENSORS; i++){
        ofPtr<Sensor> sensor =  ofPtr<Sensor>( new Sensor(i));
        m_sensors[sensor->getId()] = sensor;
        //m_sensors.insert ( std::pair<int,Sensor>(sensor.getId(),sensor) );
        
//        Sensor sensor(i+1);
//        m_sensors.insert ( std::pair<int,Sensor>(sensor.getId(),sensor) );
        ofLogNotice() <<"SensorsManager::setupSensors -> ID: " << sensor->getId();
    }
}


void SensorsManager::update()
{
    this->updateSensors();
}

void SensorsManager::updateSensors()
{
    for(auto sensor: m_sensors){
        sensor.second->update();
    }
}

void SensorsManager::updatePir(int& value)
{
    if(m_previousPirValue!=value){
        m_previousPirValue = value;
        if(value > 0){
            this->addPirOnset();
        }
    }
}

void SensorsManager::updateValue(int value, int _id)
{
    if(m_sensors.find(_id) == m_sensors.end()){
        return;
    }
    
    m_sensors[_id]->updateValue(value);
}


void SensorsManager::setThreshold(int value, int _id)
{
    if(m_sensors.find(_id) == m_sensors.end()){
        return;
    }
    
    m_sensors[_id]->setThreshold(value);
}

void SensorsManager::setStandbyTime(double value, int _id)
{
    if(m_sensors.find(_id) == m_sensors.end()){
        return;
    }
    
    m_sensors[_id]->setStandbyTime(value);
}

void SensorsManager::addPirOnset()
{
    m_pirCounter++;
    this->sendOscPirCounter();
}

void SensorsManager::sendOscPirCounter()
{
    string address = "amazon/arduino/amazon/arduino/count/sentrada";
    
    ofLogNotice() <<"SensorsManager::sendOscPirCounter << count : " << m_pirCounter;
    
    AppManager::getInstance().getOscManager().sendIntMessage(m_pirCounter, address);
    AppManager::getInstance().getGuiManager().onPirCountChange(m_pirCounter);
}



void SensorsManager::setWaitingTime(float& value)
{
    for(auto sensor: m_sensors){
        sensor.second->setStandbyTime(value);
    }
}

