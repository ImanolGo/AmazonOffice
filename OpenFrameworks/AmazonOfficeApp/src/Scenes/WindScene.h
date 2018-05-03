/*
 *  WindScene.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */

#pragma once


#include "ofxScene.h"
#include "ImageVisual.h"
#include "TextVisual.h"

class WindScene : public ofxScene {

public:

    //! Constructor
    WindScene();
    
    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();

private:
    
    void loadImages();
    
    void setupText();
    
    void updateText();
    
    void drawImages();
    
    void drawText();
    
private:
    
    ImageVisual       m_weatherIcon;
    TextVisual        m_textTemperature;
};

