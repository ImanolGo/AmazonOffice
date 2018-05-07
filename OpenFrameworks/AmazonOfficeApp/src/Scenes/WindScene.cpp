/*
 *  WindScene.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */


#include "AppManager.h"
#include "WindScene.h"


WindScene::WindScene(): ofxScene("Wind")
{
    
}

void WindScene::setup() {
    ofLogNotice("WindScene::setup");
    this->loadImages();
    this->setupText();
}

void WindScene::loadImages()
{
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
  
    m_weatherIcon.setResource("Mist");
    m_weatherIcon.setHeight(height*0.5,true);
    m_weatherIcon.setCentred(false);

    auto pos =  m_weatherIcon.getPosition();
    pos.x = width*0.5 - m_weatherIcon.getWidth();
    pos.y = height*0.5 - m_weatherIcon.getHeight()*0.5;
    m_weatherIcon.setPosition(pos);

}

void WindScene::setupText()
{
    float size = m_weatherIcon.getHeight()*0.15;
    float w = size*10;
    float h = size;
    float x =  m_weatherIcon.getPosition().x + m_weatherIcon.getWidth();
    float y =  m_weatherIcon.getPosition().y + m_weatherIcon.getHeight()*0.5;
    ofPoint pos = ofPoint(x, y);
    string text = "0 kph";
    string fontName = LayoutManager::LAYOUT_FONT;
    
    m_textTemperature = TextVisual(pos,w,h,false);
    m_textTemperature.setText(text, fontName, size, ofColor::white);
    
}

void WindScene::update()
{
    this->updateText();
}

void WindScene::draw() {
    ofBackground(0);
    this->drawImages();
    this->drawText();
}


void WindScene::updateText()
{
    string speed  = AppManager::getInstance().getApiManager().getCurrentWeather().getWindSpeed();
    m_textTemperature.setText(speed);
}


void WindScene::drawImages() {
    m_weatherIcon.draw();
}

void WindScene::drawText() {
    m_textTemperature.draw();
}


void WindScene::willFadeIn() {
     ofLogNotice("WindScene::willFadeIn");
     AppManager::getInstance().getApiManager().loadWeatherData();
}

void WindScene::willDraw() {
    ofLogNotice("WindScene::willDraw");
}

void WindScene::willFadeOut() {
    ofLogNotice("WindScene::willFadeOut");
}

void WindScene::willExit() {
    ofLogNotice("WindScene::willExit");
}
