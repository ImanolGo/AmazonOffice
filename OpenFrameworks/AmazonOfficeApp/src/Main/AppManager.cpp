/*
 *  AppManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */



#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false), m_initialized(false)
{
   //Intentionally left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;
    
    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    
    m_initialized = true;
    
    //setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
    ofSetBackgroundAuto(true);
    ofTrueTypeFont::setGlobalDpi(72);
}


void AppManager::setupManagers()
{
    m_settingsManager.setup();
    m_resourceManager.setup();
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_maskManager.setup();
    m_layoutManager.setup();
    m_apiManager.setup();
    m_keyboardManager.setup();
    m_sceneManager.setup();
    m_oscManager.setup();
    m_sensorsManager.setup();
    m_guiManager.setup();
    m_sceneManager.nextScene();
}

void AppManager::update()
{
    if(!m_initialized)
        return;
    
    m_visualEffectsManager.update();
    m_viewManager.update();
    m_apiManager.update();
    m_sceneManager.update();
    m_guiManager.update();
    m_layoutManager.update();
    m_oscManager.update();
    m_sensorsManager.update();
}


void AppManager::draw()
{
    
    if(!m_initialized)
        return;
    
    ofBackground(55,55,55);
    m_layoutManager.draw();
    m_guiManager.draw();    
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}



