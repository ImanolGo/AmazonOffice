/*
 *  WeatherScene.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 02/05/18.
 *
 */


#include "AppManager.h"
#include "WeatherScene.h"


WeatherScene::WeatherScene(): ofxScene("Weather"), m_weatherId(-1)
{
    
}

void WeatherScene::setup() {
    ofLogNotice("WeatherScene::setup");
    this->loadImages();
    this->setupText();
}

void WeatherScene::loadImages()
{
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
  
    m_weatherIcon.setResource("ClearSky");
    m_weatherIcon.setHeight(height*0.5,true);
    m_weatherIcon.setCentred(false);

    auto pos =  m_weatherIcon.getPosition();
    pos.x = width*0.5 - m_weatherIcon.getWidth();
    pos.y = height*0.5 - m_weatherIcon.getHeight()*0.5;
    m_weatherIcon.setPosition(pos);

}

void WeatherScene::setupText()
{
    float size = m_weatherIcon.getHeight()*0.15;
    float w = size*10;
    float h = size;
    float x =  m_weatherIcon.getPosition().x + m_weatherIcon.getWidth();
    float y =  m_weatherIcon.getPosition().y + m_weatherIcon.getHeight()*0.5;
    ofPoint pos = ofPoint(x, y);
    string text = "0°C";
    string fontName = LayoutManager::LAYOUT_FONT;
    
    m_textTemperature = TextVisual(pos,w,h,false);
    m_textTemperature.setText(text, fontName, size, ofColor::white);
    
}

void WeatherScene::update()
{
    this->checkNewId();
    this->updateText();
}

void WeatherScene::draw() {
    ofBackground(0);
    this->drawImages();
    this->drawText();
}


void WeatherScene::updateText()
{
    string temp  = AppManager::getInstance().getApiManager().getCurrentWeather().getTemperature();
    m_textTemperature.setText(temp);
}

void WeatherScene::checkNewId() {
    auto & weatherConditions = AppManager::getInstance().getApiManager().getCurrentWeather();
    if(m_weatherId!=weatherConditions.m_id){
        m_weatherId=weatherConditions.m_id;
        this->changeIcon();
    }
}

void WeatherScene::changeIcon() {
    
    if(m_weatherId>=200 && m_weatherId<300){
        m_weatherIcon.setResource("Thunderstorm");
    }
    else if(m_weatherId>=300 && m_weatherId<400){
        m_weatherIcon.setResource("ShowerRain");
    }
    else if(m_weatherId>=500 && m_weatherId<600){
        m_weatherIcon.setResource("Rain");
    }
    else if(m_weatherId>=600 && m_weatherId<700){
        m_weatherIcon.setResource("Snow");
    }
    else if(m_weatherId>=700 && m_weatherId<800){
        m_weatherIcon.setResource("Mist");
    }
    else if(m_weatherId==800){
        m_weatherIcon.setResource("ClearSky");
    }
    else if(m_weatherId==801){
        m_weatherIcon.setResource("FewClouds");
    }
    else if(m_weatherId==802){
        m_weatherIcon.setResource("ScatteredClouds");
    }
    else if(m_weatherId>=803 && m_weatherId<900){
        m_weatherIcon.setResource("Cloudy");
    }
}


void WeatherScene::drawImages() {
    m_weatherIcon.draw();
}

void WeatherScene::drawText() {
    m_textTemperature.draw();
}


void WeatherScene::willFadeIn() {
     AppManager::getInstance().getApiManager().loadWeatherData();
     ofLogNotice("WeatherScene::willFadeIn");
}

void WeatherScene::willDraw() {
    ofLogNotice("WeatherScene::willDraw");
}

void WeatherScene::willFadeOut() {
    ofLogNotice("WeatherScene::willFadeOut");
}

void WeatherScene::willExit() {
    ofLogNotice("WeatherScene::willExit");
}
