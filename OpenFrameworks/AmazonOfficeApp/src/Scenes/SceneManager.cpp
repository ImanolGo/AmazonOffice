/*
 *  SceneManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */
#include "ofMain.h"


#include "SceneManager.h"
#include "scenes.h"
#include "AppManager.h"

SceneManager::SceneManager(): Manager(), m_alpha(-1), m_transitionTime(1.0)
{
	//Intentionally left empty
}


SceneManager::~SceneManager()
{
    ofLogNotice() <<"SceneManager::Destructor";
}


void SceneManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();

    this->createScenes();
    this->setupFbo();
    this->setupTimer();
    this->initializeSceneList();

    ofLogNotice() <<"SceneManager::initialized";

}


void SceneManager::createScenes()
{
    m_mySceneManager.setTransitionFade();
	//m_mySceneManager.setTransitionDissolve();
    
    ofPtr<ofxScene> scene;
    
    //Create Blank Scene
    scene = ofPtr<ofxScene> (new BlankScene());
    m_mySceneManager.addScene(scene);
    
    
    //Create Video Scene
    scene = ofPtr<ofxScene> (new VideoScene("Test_Video"));
    m_mySceneManager.addScene(scene);
    
    //Create Image Scene
    scene = ofPtr<ofxScene> (new ImageScene("Rainbow"));
    m_mySceneManager.addScene(scene);
    
    //Create Weather Scene
    scene = ofPtr<ofxScene> (new WeatherScene());
    m_mySceneManager.addScene(scene);
    
    //Create Tides Scene
    scene = ofPtr<ofxScene> (new TidesScene());
    m_mySceneManager.addScene(scene);
    
    //Create Traffic Scene
    scene = ofPtr<ofxScene> (new TrafficScene());
    m_mySceneManager.addScene(scene);
    
    //Create Wind Scene
    scene = ofPtr<ofxScene> (new WindScene());
    m_mySceneManager.addScene(scene);
    
    //Create Planes Scene
    scene = ofPtr<ofxScene> (new PlanesScene());
    m_mySceneManager.addScene(scene);
 
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();

    m_mySceneManager.run(width, height);
    this->onTransitionTimeChange(m_transitionTime);
}


void SceneManager::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    //float width = ofGetWidth();
    //float height = ofGetHeight();

    m_fbo.allocate(width, height, GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void SceneManager::setupTimer()
{
    auto time = AppManager::getInstance().getSettingsManager().getSceneTimer();

    m_sceneTimer.setup( time*1000 );
    m_sceneTimer.start( false ) ;
    ofAddListener( m_sceneTimer.TIMER_COMPLETE , this, &SceneManager::sceneTimerCompleteHandler ) ;
    
    ofLogNotice() <<"SceneManager::setupTimer << Time = : " << time << "s";
}

void SceneManager::onChangeSceneDuration(float& value)
{
    m_sceneTimer.setup( value*1000 );
    m_sceneTimer.start( false ) ;
    ofLogNotice() <<"SceneManager::setupTimer << Time = : " << value << "s";
}

void SceneManager::initializeSceneList()
{
    m_sceneList.clear();
    m_sceneList  = { "Weather", "Tides", "Traffic", "Wind", "Planes"};
}


void SceneManager::update()
{
    this->updateScenes();
    this->updateFbo();
    this->updateTimer();
}

void SceneManager::updateFbo()
{
    m_fbo.begin();
        ofClear(0);
        ofPushStyle();
        ofSetColor(255);
        ofEnableAlphaBlending();
            m_mySceneManager.draw();
        ofDisableAlphaBlending();
        ofPopStyle();
    m_fbo.end();
}


void SceneManager::updateScenes()
{
    m_mySceneManager.update();
}

void SceneManager::updateTimer()
{
    m_sceneTimer.update();
}


void SceneManager::draw()
{
	ofEnableAlphaBlending();
    m_fbo.draw(0,0);
	ofDisableAlphaBlending();
}

void SceneManager::draw(const ofRectangle& rect)
{
    m_fbo.draw(rect.x,rect.y,rect.width,rect.height);
}


void SceneManager::changeScene(string sceneName)
{
    m_mySceneManager.changeScene(sceneName);
    m_sceneTimer.start(false,true);
    m_currentSceneName = sceneName;
    this->sendSceneChange();
    
    
}

void SceneManager::changeScene(int sceneIndex)
{
    
     m_mySceneManager.changeScene(sceneIndex);
     m_sceneTimer.start(false,true);
     m_currentSceneName = this->getSceneName(sceneIndex);
     this->sendSceneChange();
}


void SceneManager::onTransitionTimeChange(float value)
{
   m_mySceneManager.setSceneDuration(value,value);
   m_sceneTimer.start(false,true);
}

string SceneManager::getSceneName(int sceneIndex)
{
    string name = "";
    if(sceneIndex < 0 || sceneIndex >= m_mySceneManager.scenes.size()){
        return name;
    }
    
    return m_mySceneManager.scenes[sceneIndex]->getName();
   
}

int SceneManager::getIndex(string& sceneName)
{
    for(int i = 0; i< m_mySceneManager.scenes.size(); i++){
        if(m_mySceneManager.scenes[i]->getName() == sceneName){
            return i;
        }
    }
    
    return -1;
}

void SceneManager::sceneTimerCompleteHandler( int &args )
{
    m_sceneTimer.start(false);
    
    this->nextScene();
}

void SceneManager::nextScene()
{
    if(m_sceneList.empty()){
        this->initializeSceneList();
    }
    
    string sceneName = m_sceneList.back();  m_sceneList.pop_back();
    AppManager::getInstance().getGuiManager().onSceneChange(sceneName);
    
    ofLogNotice() <<"SceneManager::nextScene << Change Scene: " << sceneName;
}

void SceneManager::sendSceneChange()
{
    
    string address = "preset" + m_currentSceneName;
    
    ofLogNotice() <<"SceneManager::sendSceneChange << OSC Message Scene: " << address;
    
    AppManager::getInstance().getOscManager().sendIntMessage(1, address);
  
}





