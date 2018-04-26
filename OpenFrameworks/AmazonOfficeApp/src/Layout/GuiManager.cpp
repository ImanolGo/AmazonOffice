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
    this->setupSkyGui();
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

void GuiManager::setupSkyGui()
{
    auto apiManager = &AppManager::getInstance().getApiManager();
    
    m_numPlanes.set("Total", 10, 0, 100.0);
    m_numPlanes.addListener(apiManager, &ApiManager::onNumPlanesChange);
    m_parameters.add(m_numPlanes);
    
    m_numGround.set("Ground", 10, 0, 100.0);
    m_numGround.addListener(apiManager, &ApiManager::onNumGroundChange);
    m_parameters.add(m_numGround);
    
    m_numTakingOff.set("Taking Off", 10, 0, 100.0);
    m_numTakingOff.addListener(apiManager, &ApiManager::onNumTakingOffChange);
    m_parameters.add(m_numTakingOff);
    
    m_numLanding.set("Landing", 10, 0, 100.0);
    m_numLanding.addListener(apiManager, &ApiManager::onNumLandingChange);
    m_parameters.add(m_numLanding);
    
    m_numFlyingOver.set("Flying Over", 10, 0, 100.0);
    m_numFlyingOver.addListener(apiManager, &ApiManager::onNumFlyingOverChange);
    m_parameters.add(m_numFlyingOver);
    
    ofxDatGuiFolder* folder = m_gui.addFolder("AIR", ofColor::skyBlue);
    folder->addSlider(m_numPlanes);
    folder->addSlider(m_numGround);
    folder->addSlider(m_numTakingOff);
    folder->addSlider(m_numLanding);
    folder->addSlider(m_numFlyingOver);
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
    
    m_numPlanes = value.numPlanes;
    m_numGround = value.numGround;
    m_numTakingOff = value.numTakingOff;
    m_numLanding = value.numLanding;
    m_numFlyingOver = value.numFlyingOver;
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
