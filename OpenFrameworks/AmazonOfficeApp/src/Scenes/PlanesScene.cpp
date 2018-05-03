/*
 *  PlanesScene.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */


#include "AppManager.h"
#include "PlanesScene.h"


PlanesScene::PlanesScene(): ofxScene("Planes")
{
    
}

void PlanesScene::setup() {
    ofLogNotice("PlanesScene::setup");
    this->setupImages();
}

void PlanesScene::setupImages()
{
    this->setupImageMap();
    this->setupImageTraffic();
}


void PlanesScene::setupImageMap()
{
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    
    m_map.setResource("MapFlights");
    m_map.setCentred(true);
    m_map.setHeight(height,true);
    
    if(m_map.getWidth()>width){
         m_map.setWidth(width,true);
    }
    
    ofPoint pos(width*0.5, height*0.5);
    m_map.setPosition(pos);
}

void PlanesScene::setupImageTraffic()
{
    
    
}

void PlanesScene::update()
{
   
}

void PlanesScene::draw() {
    ofBackground(0);
    this->drawImages();
}


void PlanesScene::drawImages()
{
    m_map.draw();
}

void PlanesScene::willFadeIn() {
     ofLogNotice("PlanesScene::willFadeIn");
}

void PlanesScene::willDraw() {
    ofLogNotice("PlanesScene::willDraw");
}

void PlanesScene::willFadeOut() {
    ofLogNotice("PlanesScene::willFadeOut");
}

void PlanesScene::willExit() {
    ofLogNotice("PlanesScene::willExit");
}
