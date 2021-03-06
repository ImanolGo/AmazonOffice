/*
 *  SensorsManager.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "Sensor.h"


//========================== class SensorsManager =======================================
//===================================================================================
/** \class SensorsManager SensorsManager.h
 *    \brief class for managing several APIs
 *    \details It reads from weather APIs, tide APIs, parses the informations and provides the
 *    methods to read it
 */


class SensorsManager: public Manager
{
    
    static const int NUM_SENSORS;
    
public:
    //! Constructor
    SensorsManager();
    
    //! Destructor
    virtual ~SensorsManager();
    
    //! setups the manager
    void setup();
    
    //! updates the manager
    void update();
    
    void updateValue(int value, int _id);
    
    void updatePir(int& value);
    
    void setThreshold(int value, int _id);
    
    void setStandbyTime(double value, int _id);
    
    void setWaitingTime(float& value);
    
    void setPirCount(int& value) {m_pirCounter = value;}
    
private:
    
    void setupSensors();

    void updateSensors();
    
    void sendOscPirCounter();
    
    void addPirOnset();

private:
    
    typedef    map< int, ofPtr<Sensor> >    SensorMap;    ///< Defines a map of sensors attached to its id
    
    SensorMap         m_sensors;
    int               m_pirCounter;
    int               m_previousPirValue;
    
 
    
};

