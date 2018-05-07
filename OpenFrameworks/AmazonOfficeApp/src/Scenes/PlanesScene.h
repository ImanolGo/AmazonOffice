/*
 *  PlanesScene.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 03/05/18.
 *
 */

#pragma once


#include "ofxScene.h"
#include "ImageVisual.h"


class PlanesScene : public ofxScene {

public:

    //! Constructor
    PlanesScene();
    
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
    
    void setupImageMap();
    
    void setupImageTraffic();
    
    void drawImages();
    
    void drawPlanes();
    
    
private:
    
    typedef  map<string, ofPtr<ImageVisual>  >    ImageMap;           ///< defines a map of ImageVisual Map attached to an identifier
    
    ImageVisual           m_map;
    ImageMap              m_planes;
    ImageVisual           m_plane;
};

