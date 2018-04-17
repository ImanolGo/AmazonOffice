/*
 *  AmazonOfficeApp.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */



#include "AppManager.h"

#include "AmazonOfficeApp.h"

//--------------------------------------------------------------
void AmazonOfficeApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void AmazonOfficeApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void AmazonOfficeApp::draw(){
    AppManager::getInstance().draw();
}

void AmazonOfficeApp::exit()
{
    ofLogNotice() <<"AmazonOfficeApp::exit";

}

//--------------------------------------------------------------
void AmazonOfficeApp::keyPressed(int key){

}

//--------------------------------------------------------------
void AmazonOfficeApp::keyReleased(int key){

}

//--------------------------------------------------------------
void AmazonOfficeApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void AmazonOfficeApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void AmazonOfficeApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void AmazonOfficeApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void AmazonOfficeApp::windowResized(int w, int h){
    AppManager::getInstance().getLayoutManager().windowResized(w,h);


}

//--------------------------------------------------------------
void AmazonOfficeApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void AmazonOfficeApp::dragEvent(ofDragInfo dragInfo){

}
