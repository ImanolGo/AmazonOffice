/*
 *  TidesScene.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 02/05/18.
 *
 */

#pragma once


#include "ofxScene.h"


class TidesScene : public ofxScene {

public:

    //! Constructor
    TidesScene();
    
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
    
    void setupColor();
    
    void updateColor();
    
    
private:
    
    ofColor           m_color;

};

