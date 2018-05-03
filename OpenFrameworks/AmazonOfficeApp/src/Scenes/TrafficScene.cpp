/*
 *  TrafficScene.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 02/05/18.
 *
 */


#include "AppManager.h"
#include "TrafficScene.h"


TrafficScene::TrafficScene(): ofxScene("Traffic")
{
    
}

void TrafficScene::setup() {
    ofLogNotice("TrafficScene::setup");
    this->setupImages();
}

void TrafficScene::setupImages()
{
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    
    m_map.setResource("MapTraffic");
    m_map.setCentred(true);
    m_map.setHeight(height,true);
    
    if(m_map.getWidth()>width){
         m_map.setWidth(width,true);
    }
    
    ofPoint pos(width*0.5, height*0.5);
    m_map.setPosition(pos);
}


void TrafficScene::update()
{
   
}

void TrafficScene::draw() {
    ofBackground(0);
    this->drawImages();
}


void TrafficScene::drawImages()
{
    m_map.draw();
}

void TrafficScene::willFadeIn() {
     ofLogNotice("TrafficScene::willFadeIn");
}

void TrafficScene::willDraw() {
    ofLogNotice("TrafficScene::willDraw");
}

void TrafficScene::willFadeOut() {
    ofLogNotice("TrafficScene::willFadeOut");
}

void TrafficScene::willExit() {
    ofLogNotice("TrafficScene::willExit");
}
