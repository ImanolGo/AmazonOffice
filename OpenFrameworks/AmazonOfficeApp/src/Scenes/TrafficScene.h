/*
 *  TrafficScene.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 02/05/18.
 *
 */

#pragma once


#include "ofxScene.h"
#include "ImageVisual.h"


class TrafficScene : public ofxScene {

public:

    //! Constructor
    TrafficScene();
    
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
    
    void setupImages();
    
    void drawImages();
    
    
private:
    
    ImageVisual           m_map;

};

