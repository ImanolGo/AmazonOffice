/*
 *  GuiManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"
#include "GuiTheme.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "GUI";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true), m_cityLabel(NULL)
{
    //Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupGuiParameters();
    this->setupGeneralGui();
    this->setupScenesGui();
    this->setupTileGui();
    this->setupSkyGui();
    this->setupTrafficGui();
    this->setupWeatherGui();
    this->setupGuiEvents();
    this->loadGuiValues();
	this->onWeatherChange();
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    
    ofxDatGuiLog::quiet();
    
    m_gui.setPosition(ofxDatGuiAnchor::TOP_LEFT);
    //m_gui.setAssetPath(ofToDataPath("fonts/"));
    //m_gui.setAssetPath("../Resources/data/fonts/");
    m_gui.setTheme(new GuiTheme());
    
    
    int margin =  LayoutManager::MARGIN;
    m_gui.setAutoDraw(false);
    auto pos = m_gui.getPosition();
    m_gui.setPosition(pos.x + margin, pos.y + margin);
    m_gui.addHeader(GUI_SETTINGS_NAME, false);
    
    m_gui.addFRM(0.1);
    
    m_gui.addBreak();
}

void GuiManager::setupGeneralGui()
{
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_sceneDuration.set("Scene Dur.", 60.0, 0.0, 300.0);
    m_sceneDuration.addListener(sceneManager, &SceneManager::onChangeSceneDuration);
    m_parameters.add(m_sceneDuration);
    
    ofxDatGuiFolder* folder = m_gui.addFolder("GENERAL", ofColor::white);
    folder->addSlider(m_sceneDuration);
    auto* toggle = folder->addToggle("* APIs");
    toggle->setChecked(true);
    folder->expand();
    m_gui.addBreak();
}

void GuiManager::setupScenesGui()
{
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    vector<string> opts;
    
    for(int i = 0; i < sceneManager->getNumberScenes(); i++)
    {
        opts.push_back(sceneManager->getSceneName(i));
    }
    
    string label = "SCENES";
    
    m_gui.addDropdown(label, opts);
    auto menu = m_gui.getDropdown(label);
    menu->expand(); //let's have it open by default
    menu->setStripeColor(ofColor::pink);
    for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(ofColor::pink);
    m_gui.addBreak();
}


void GuiManager::setupTileGui()
{
    auto sensorManager = &AppManager::getInstance().getSensorManager();
    
    ofxDatGuiFolder* folder = m_gui.addFolder("SENSORS", ofColor::darkRed);
    
    for(int i=0; i<m_sensorValues.size(); i++)
    {
        m_sensorValues[i].set("Sensor" + ofToString(i+1),0, 0, 1024);
        folder->addSlider(m_sensorValues[i]);
         //m_parameters.add(m_sensorValues[i]);
    }
    
    for(int i=0; i<m_sensorThresholds.size(); i++)
    {
        m_sensorThresholds[i].set("SensorThr" + ofToString(i+1),0, 0, 1024);
        folder->addSlider(m_sensorThresholds[i]);
        m_parameters.add(m_sensorThresholds[i]);
    }
    
    m_tileStandby.set("Time", 2, 0, 30);
    m_tileStandby.addListener(sensorManager, &SensorsManager::setWaitingTime);
    m_parameters.add(m_tileStandby);
    
    m_pirCount.set("PirCount", 0, 0, 100000);
    m_pirCount.addListener(sensorManager, &SensorsManager::setPirCount);
    
    m_pirValue.set("PirValue", 0, 0, 1);
    m_pirValue.addListener(sensorManager, &SensorsManager::updatePir);
    
    folder->addSlider(m_tileStandby);
    folder->addSlider(m_pirCount);
    folder->addSlider(m_pirValue);
    folder->expand();
    
    m_gui.addBreak();
}

void GuiManager::setupSkyGui()
{
    auto apiManager = &AppManager::getInstance().getApiManager();
    
    m_numAirport.set("Airport", 10, 0, 100.0);
    m_numAirport.addListener(apiManager, &ApiManager::onNumAirportChange);
    m_parameters.add(m_numAirport);
    
    m_numNorth.set("North", 10, 0, 100.0);
    m_numNorth.addListener(apiManager, &ApiManager::onNumNorthChange);
    m_parameters.add(m_numNorth);
    
    m_numEast.set("East", 10, 0, 100.0);
    m_numEast.addListener(apiManager, &ApiManager::onNumEastChange);
    m_parameters.add(m_numEast);
    
    m_numSouth.set("East", 10, 0, 100.0);
    m_numSouth.addListener(apiManager, &ApiManager::onNumSouthChange);
    m_parameters.add(m_numSouth);
    
    m_numWest.set("West", 10, 0, 100.0);
    m_numWest.addListener(apiManager, &ApiManager::onNumWestChange);
    m_parameters.add(m_numWest);

    
    ofxDatGuiFolder* folder = m_gui.addFolder("AIR", ofColor::skyBlue);
    folder->addSlider(m_numAirport);
    folder->addSlider(m_numNorth);
    folder->addSlider(m_numEast);
    folder->addSlider(m_numSouth);
    folder->addSlider(m_numWest);
    folder->expand();
    
    m_gui.addBreak();
    
}


void GuiManager::setupTrafficGui()
{
    
    ofxDatGuiFolder* folder = m_gui.addFolder("STREETS", ofColor::grey);
    
    auto streets = AppManager::getInstance().getApiManager().getTrafficStatus();
   // m_streetFlow.assign(streets.size(), ofParameter<float>());
    
    for(int i=0; i<streets.size(); i++)
    {
        m_streetFlow[i].set(streets[i]->m_name, 0.0, 0.0, 1.0);
        folder->addSlider(m_streetFlow[i]);
    }
    
    folder->expand();
    m_gui.addBreak();
}




void GuiManager::setupWeatherGui()
{
    auto apiManager = &AppManager::getInstance().getApiManager();
    
    m_weatherTemperature.set("Temp.", 20.0, -5, 40.0);
    m_weatherTemperature.addListener(apiManager, &ApiManager::onTemperatureChange);
    m_parameters.add(m_weatherTemperature);
    
    m_weatherHumidity.set("Humidity", 0.0, 0.0, 100.0);
    m_weatherHumidity.addListener(apiManager, &ApiManager::onHumidityChange);
    m_parameters.add(m_weatherHumidity);
    
    m_weatherWindSpeed.set("Wind Speed", 0.0, 0.0, 100.0);
    m_weatherWindSpeed.addListener(apiManager, &ApiManager::onWindSpeedChange);
    m_parameters.add(m_weatherWindSpeed);
    
    m_weatherWindDirection.set("Wind Dir", 0.0, 0.0, 360.0);
    m_weatherWindDirection.addListener(apiManager, &ApiManager::onWindDirChange);
    m_parameters.add(m_weatherWindDirection);
    
    m_weatherPrecipitation.set("Prec.", 0.0, 0.0, 20.0);
    m_weatherPrecipitation.addListener(apiManager, &ApiManager::onPrecipitationChange);
    m_parameters.add(m_weatherPrecipitation);
    
    m_weatherClouds.set("Clouds", 0.0, 0.0, 100);
    m_weatherClouds.addListener(apiManager, &ApiManager::onCloudsChange);
    m_parameters.add(m_weatherClouds);
    
    m_weatherMoon.set("Moon Phase", 0.0, 0.0, 1.0);
    m_weatherMoon.addListener(apiManager, &ApiManager::onMoonChange);
    m_parameters.add(m_weatherMoon);
    
    m_weatherSun.set("Sun Position", 0.0, 0.0, 1.0);
    m_weatherSun.addListener(apiManager, &ApiManager::onSunChange);
    m_parameters.add(m_weatherSun);
    
    m_swellHeight.set("Swell Height", 0.0, 0.0, 4);
    m_swellHeight.addListener(apiManager, &ApiManager::onSwellHeightChange);
    m_parameters.add(m_swellHeight);
    
    m_swellPeriod.set("Swell Period", 0.0, 0.0, 20);
    m_swellPeriod.addListener(apiManager, &ApiManager::onSwellPeriodChange);
    m_parameters.add(m_swellPeriod);
    
    
    ofxDatGuiFolder* folder = m_gui.addFolder("WEATHER", ofColor::green);
    m_cityLabel = folder->addLabel("CITY: ");
    folder->addSlider(m_weatherTemperature);
    folder->addSlider(m_weatherHumidity);
    folder->addSlider(m_weatherWindSpeed);
    folder->addSlider(m_weatherWindDirection);
    folder->addSlider(m_weatherPrecipitation);
    folder->addSlider(m_weatherClouds);
    folder->addSlider(m_weatherMoon);
    folder->addSlider(m_weatherSun);
    folder->addSlider(m_swellHeight);
    folder->addSlider(m_swellPeriod);
    //folder->expand();
    
    m_gui.addBreak();
}


void GuiManager::update()
{
    m_gui.update();
    this->updateSensors();
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    this->drawGui();
}


void GuiManager::drawGui()
{
    ofEnableAlphaBlending();
    m_gui.draw();
    ofDisableAlphaBlending();
}

void GuiManager::setupGuiEvents()
{
    m_gui.onDropdownEvent(this, &GuiManager::onDropdownEvent);
    m_gui.onColorPickerEvent(this, &GuiManager::onColorPickerEvent);
    m_gui.onButtonEvent(this, &GuiManager::onButtonEvent);
    m_gui.onToggleEvent(this, &GuiManager::onToggleEvent);
    m_gui.onMatrixEvent(this, &GuiManager::onMatrixEvent);
}


void GuiManager::saveGuiValues()
{
    ofXml xml;
    ofSerialize(xml, m_parameters);
    xml.save(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    ofXml xml;
    xml.load(GUI_SETTINGS_FILE_NAME);
    ofDeserialize(xml, m_parameters);
}

void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    int margin =  LayoutManager::MARGIN;
    ofPushStyle();
    ofSetColor(15);
    ofDrawRectangle( m_gui.getPosition().x - margin, 0, m_gui.getWidth() + 2*margin, ofGetHeight());
    ofPopStyle();
}



void GuiManager::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "SCENES")
    {
        AppManager::getInstance().getSceneManager().changeScene(e.child);
        m_gui.getDropdown(e.target->getName())->expand();
        m_gui.getDropdown(e.target->getName())->setLabel("SCENES:" + e.target->getLabel());
    }
}

void GuiManager::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent: " << e.target->getName() << " Selected" << endl;
    
}

void GuiManager::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getName() << " Selected" << endl;
    
}


void GuiManager::onToggleEvent(ofxDatGuiToggleEvent e)
{
    cout << "onToggleEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "* APIs")
    {
        AppManager::getInstance().getApiManager().onEnableApis(e.target->getChecked());
    }
    
}

void GuiManager::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
}



void GuiManager::onWeatherChange()
{
    auto value = AppManager::getInstance().getApiManager().getCurrentWeather();
    
    m_weatherTemperature = value.m_temp;
    m_weatherHumidity = value.m_humidity;
    m_weatherWindSpeed = value.m_windSpeed;
    m_weatherWindDirection = value.m_windDirection;
    m_weatherPrecipitation = value.m_precipitationValue;
    m_weatherMoon = value.m_moonPhase;
    m_weatherClouds = value.m_clouds;
	m_weatherSun = value.calculatePosition();
    
    m_swellHeight = value.m_swellHeight;
    m_swellPeriod = value.m_swellPeriod;

    
    if(m_cityLabel!=NULL){
        m_cityLabel->setLabel("CITY: " +  value.m_city);
    }
}

void GuiManager::onAirTrafficChange()
{
    auto value = AppManager::getInstance().getApiManager().getCurrentAirTraffic();
        
    m_numAirport = value.numAirport;
    m_numNorth = value.numNorth;
    m_numSouth = value.numSouth;
    m_numEast = value.numEast;
    m_numWest = value.numWest;
}

void GuiManager::onTrafficChange()
{
    auto streets = AppManager::getInstance().getApiManager().getTrafficStatus();
    
    for(int i=0; i<streets.size(); i++)
    {
        m_streetFlow[i] = streets[i]->getSpeedNorm();
    }
}

void GuiManager::updateSensors()
{
    for(int i=0; i<m_sensorValues.size(); i++)
    {
        AppManager::getInstance().getSensorManager().updateValue(m_sensorValues[i], i);
    }
    
    for(int i=0; i<m_sensorThresholds.size(); i++)
    {
        AppManager::getInstance().getSensorManager().setThreshold(m_sensorThresholds[i], i);
    }
}

void GuiManager::setTileValue(int value, int index)
{
    if(index< 0 || index>=m_sensorValues.size()){
        return;
    }
    
    m_sensorValues[index] = value;
}

void GuiManager::setTileThreshold(int value, int index)
{
    if(index< 0 || index>=m_sensorThresholds.size()){
        return;
    }
    
    m_sensorThresholds[index] = value;
}


void GuiManager::onSceneChange(string &sceneName)
{
    int index = AppManager::getInstance().getSceneManager().getIndex(sceneName);
    this->onSceneChange(index);
}

void GuiManager::onSceneChange(int sceneIndex)
{
    string dropBoxName = "SCENES";
    auto menu = m_gui.getDropdown(dropBoxName);
    menu->select(sceneIndex);
    string label =  menu->getChildAt(sceneIndex)->getLabel();
    menu->setLabel(dropBoxName + ":" + label);
    AppManager::getInstance().getSceneManager().changeScene(sceneIndex);
}
