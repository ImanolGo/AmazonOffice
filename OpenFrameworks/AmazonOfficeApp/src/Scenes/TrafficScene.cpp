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
    this->setupImageMap();
    this->setupImageTraffic();
}


void TrafficScene::setupImageMap()
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

void TrafficScene::setupImageTraffic()
{
    ofRectangle boundingBox;
    glm::vec2 pos(m_map.getPosition().x, m_map.getPosition().y);
    boundingBox.setFromCenter(pos, m_map.getWidth(), m_map.getHeight());
//    boundingBox.x = m_map.getPosition().x -  m_map.getWidth()*0.5;
//    boundingBox.y = m_map.getPosition().y -  m_map.getHeight()*0.5;
//    boundingBox.width = m_map.getWidth(); boundingBox.height = m_map.getHeight();
//
    auto & trafficVector = AppManager::getInstance().getApiManager().getTrafficStatus();
    auto  trafficSettings =  AppManager::getInstance().getSettingsManager().getTrafficSettings();
    
    for(auto traffic: trafficVector){
        string resurceName = "Brush";
        float x = ofMap(traffic->m_latitude,trafficSettings.lat, trafficSettings.lat2, boundingBox.getMaxY(),  boundingBox.getMinY());
        float y = ofMap(traffic->m_longitude,trafficSettings.lon, trafficSettings.lon2, boundingBox.getMinX(),  boundingBox.getMaxX());
        ofPtr<ImageVisual> imageTraffic =  ofPtr<ImageVisual> (new ImageVisual(ofPoint(x,y),resurceName,true));
        m_trafficStatus[traffic->m_name] = imageTraffic;
    }
    
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
    
    for(auto traffic: m_trafficStatus){
        traffic.second->draw();
    }
}

void TrafficScene::willFadeIn() {
     AppManager::getInstance().getApiManager().loadTrafficData();
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
