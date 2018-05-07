/*
 *  GuiManager.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxDatGui.h"
#include "ApiManager.h"
#include "WeatherConditions.h"

//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *    \brief Class managing the application´s grapical user interface (GUI)
 *    \details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Set-up the gui
    void setup();
    
    //! update the gui
    void update();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth() {return m_gui.getWidth();}
    
    int getHeight() {return m_gui.getHeight();}
    
    ofPoint  getPosition() {return m_gui.getPosition();}
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    void onToggleEvent(ofxDatGuiToggleEvent e);
    
    void onMatrixEvent(ofxDatGuiMatrixEvent e);
    
    void onWeatherChange();
    
    void onAirTrafficChange();
    
    void onTrafficChange();
    
    void onSceneChange(string& sceneName);
    
    void onSceneChange(int sceneIndex);
    
    void setTileThreshold1(int value){m_tileThreshold1 = value;}
    
    void setTileThreshold2(int value){m_tileThreshold2 = value;}
    
    void setTileThreshold3(int value){m_tileThreshold3 = value;}
    
    void setTileStandbyTime(float value){m_tileStandby = value;}
    
private:
    
    void setupGuiParameters();
    
    void setupGeneralGui();
    
    void setupScenesGui();
    
    void setupWeatherGui();
    
    void setupSkyGui();
    
    void setupTrafficGui();
    
    void setupTileGui();
    
    void drawRectangle();
    
    void drawGui();
    
    void setupGuiEvents();
    
private:
    
    ofxDatGui            m_gui;
    
    ofParameter<float>    m_guiFPS;
    
    
    ofParameterGroup      m_parameters;
    
    ofParameter<float>      m_sceneDuration;
    
    ofParameter<int>        m_numPlanes;
    ofParameter<int>        m_numGround;
    ofParameter<int>        m_numTakingOff;
    ofParameter<int>        m_numLanding;
    ofParameter<int>        m_numFlyingOver;
    
    ofParameter<float>      m_weatherTemperature;
    ofParameter<float>      m_weatherHumidity;
    ofParameter<float>      m_weatherWindSpeed;
    ofParameter<float>      m_weatherWindDirection;
    ofParameter<float>      m_weatherPrecipitation;
    ofParameter<float>      m_weatherClouds;
    ofParameter<float>      m_weatherMoon;
    ofParameter<float>      m_weatherSun;
    
    ofParameter<float>      m_swellHeight;
    ofParameter<float>      m_swellPeriod;
    
    ofParameter<int>      m_tileThreshold1;
    ofParameter<int>      m_tileThreshold2;
    ofParameter<int>      m_tileThreshold3;
    ofParameter<float>    m_tileStandby;
    
    std::array<ofParameter<float>, 10> m_streetFlow;
    
   // vector<ofParameter<float>>  m_streetFlow;
    
    ofxDatGuiLabel*        m_cityLabel;
    
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


