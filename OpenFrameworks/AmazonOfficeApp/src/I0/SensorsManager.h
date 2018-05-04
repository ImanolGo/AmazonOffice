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


//========================== class SensorsManager =======================================
//===================================================================================
/** \class SensorsManager SensorsManager.h
 *    \brief class for managing several APIs
 *    \details It reads from weather APIs, tide APIs, parses the informations and provides the
 *    methods to read it
 */


class SensorsManager: public Manager
{
    
public:
    //! Constructor
    SensorsManager();
    
    //! Destructor
    virtual ~SensorsManager();
    
    //! setups the manager
    void setup();
    
    //! updates the manager
    void update();
    
private:
    
    void setupSensors();

    void updateSensors();
    

private:
    
 
    
};

