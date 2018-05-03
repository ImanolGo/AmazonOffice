/*
 *  TidesScene.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 02/05/18.
 *
 */


#include "AppManager.h"
#include "TidesScene.h"


TidesScene::TidesScene(): ofxScene("Tides")
{
    
}

void TidesScene::setup() {
    ofLogNotice("TidesScene::setup");
    this->setupColor();
}

void TidesScene::setupColor()
{
    m_color = ofColor::darkBlue;
}


void TidesScene::update()
{
    this->updateColor();
}

void TidesScene::draw() {
    ofBackground(m_color);
}


void TidesScene::updateColor()
{
    auto weatherConditions = AppManager::getInstance().getApiManager().getCurrentWeather();
    float f = 1.0/weatherConditions.m_swellPeriod;
    float sine = sin(TWO_PI*f*ofGetElapsedTimef());
    float amp = ofMap(sine, -1, 1, 0, 255);
    m_color.a = amp;
}

void TidesScene::willFadeIn() {
     ofLogNotice("TidesScene::willFadeIn");
}

void TidesScene::willDraw() {
    ofLogNotice("TidesScene::willDraw");
}

void TidesScene::willFadeOut() {
    ofLogNotice("TidesScene::willFadeOut");
}

void TidesScene::willExit() {
    ofLogNotice("TidesScene::willExit");
}
