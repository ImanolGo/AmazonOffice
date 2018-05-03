/*
 *  OscManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */


#include "OscManager.h"
#include "SettingsManager.h"
#include "AppManager.h"



const string OscManager::OSC_PARENT_ADDRESS = "/amazon";

OscManager::OscManager(): Manager()
{
    //Intentionally left empty
}

OscManager::~OscManager()
{
   ofLogNotice() << "OscManager::destructor";
}


//--------------------------------------------------------------

void OscManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupOscReceiver();
    this->setupOscSender();
    this->readSenderInformation();
    
    ofLogNotice() <<"OscManager::initialized" ;
}

void OscManager::readSenderInformation()
{
    ofXml xml;
    string fileName = SettingsManager::APPLICATION_SETTINGS_FILE_NAME;
    if(!xml.load( fileName)){
        ofLogNotice() <<"OscManager::readSenderInformation-> unable to load file: " << fileName;
        return;
    }
    
    ofLogNotice() <<"OscManager::readSenderInformation->  successfully loaded " << fileName ;
    
    string path = "//networks/network";
    auto xmlNetworks = xml.find(path);
    if(!xmlNetworks.empty()) {
        
        for(auto & xmlNetwork: xmlNetworks)
        {
            ofxOscSender  oscSender;
            auto ipAddress =  xmlNetwork.getAttribute("ipAddress").getValue();
            auto port = xmlNetwork.getAttribute("port").getIntValue();
            auto name =  xmlNetwork.getAttribute("name").getValue();
            oscSender.setup(ipAddress, port);
            m_oscSenders[name] = oscSender ;
           
            ofLogNotice() <<"OscManager::readSenderInformation->  name = " << name
            <<", ipAddress = "<< ipAddress  << ", port = " <<port;
        }
        
        return;
    }
    
    ofLogNotice() <<"OscManager::readSenderInformation->  path not found: " << path;
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
    ofLogNotice() <<"OscManager::setupOscReceiver -> listening for osc messages on port  " << portReceive;
    m_oscReceiver.setup(portReceive);
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    m_oscSender.setup(host, portSend);
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
    
}


void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(&m);
        
        if(m.getAddress() == OSC_PARENT_ADDRESS + "/StateMachine/Scene")
        {
            string sceneName = m.getArgAsString(0);
            AppManager::getInstance().getGuiManager().onSceneChange(sceneName);
        }
        
        ofLogNotice() <<"OscManager::received -> " << this->getMessageAsString(m);
    }

	this->sendOscAll();
    
}


void OscManager::sendFloatMessage(float value, string& name)
{
    string message = OSC_PARENT_ADDRESS + "/" + name;
    ofxOscMessage m;
    m.setAddress(message);
    m.addFloatArg(value);
    //m_oscSender.sendMessage(m);
    
    for (auto& oscSender : m_oscSenders) {
        oscSender.second.sendMessage(m);
    }
}

void OscManager::sendIntMessage(int value, string& name)
{
    string message = OSC_PARENT_ADDRESS + "/" + name;
    ofxOscMessage m;
    m.setAddress(message);
    m.addIntArg(value);
    //m_oscSender.sendMessage(m);
    
    for (auto& oscSender : m_oscSenders) {
        oscSender.second.sendMessage(m);
    }
}


void OscManager::sendStringMessage(string value, string& name)
{
    string message = OSC_PARENT_ADDRESS + "/" + name;
    ofxOscMessage m;
    m.setAddress(message);
    m.addStringArg(value);
    //m_oscSender.sendMessage(m);
    
    for (auto& oscSender : m_oscSenders) {
        oscSender.second.sendMessage(m);
    }
    
}

void OscManager::sendMessage(ofxOscMessage& message)
{
    //m_oscSender.sendMessage(message);
    for (auto& oscSender : m_oscSenders) {
        oscSender.second.sendMessage(message);
    }
    message.clear();
}


string OscManager::getMessageAsString(const ofxOscMessage& m) const
{
    string msg_string;
    msg_string = m.getAddress();
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += " ";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    
    return msg_string;
}

void OscManager::sendOscAll()
{
	this->sendOscUnity();
	this->sendOscIpad();
}

void OscManager::sendOscUnity()
{
	auto weather = AppManager::getInstance().getApiManager().getCurrentWeather();

	string message = "weather/norm/temperature";
	this->sendFloatMessage(weather.getTemperatureNorm(), message);

	message = "weather/norm/humidity";
	this->sendFloatMessage(weather.getHumidityNorm(), message);

	message = "weather/norm/windvelocity";
	this->sendFloatMessage(weather.getWindSpeedNorm(), message);

	message = "weather/norm/winddirection";
	this->sendFloatMessage(weather.getWindDirectionNorm(), message);

	message = "weather/norm/clouds";
	this->sendFloatMessage(weather.getCloudinessNorm(), message);

	message = "weather/norm/rain";
	this->sendFloatMessage(weather.getPrecipitationNorm(), message);

	message = "tides/norm/height";
	this->sendFloatMessage(weather.getSwellHeightNorm(), message);

	message = "tides/norm/period";
	this->sendFloatMessage(weather.getSwellPeriodNorm(), message);

//    message = "weather/norm/MoonPhaseNorm";
//    this->sendFloatMessage(weather.getMoonPhaseNorm(), message);
//
//    message = "weather/norm/SunPositionNorm";
//    this->sendFloatMessage(weather.getSunPositionNorm(), message);

}

void OscManager::sendOscIpad()
{
	auto weather = AppManager::getInstance().getApiManager().getCurrentWeather();

    string message = "weather/temperature";
    this->sendFloatMessage(weather.getTemperatureNorm(), message);
    
    message = "weather/humidity";
    this->sendFloatMessage(weather.getHumidityNorm(), message);
    
    message = "weather/windvelocity";
    this->sendFloatMessage(weather.getWindSpeedNorm(), message);
    
    message = "weather/winddirection";
    this->sendFloatMessage(weather.getWindDirectionNorm(), message);
    
    message = "weather/clouds";
    this->sendFloatMessage(weather.getCloudinessNorm(), message);
    
    message = "weather/rain";
    this->sendFloatMessage(weather.getPrecipitationNorm(), message);
    
    message = "tides/height";
    this->sendFloatMessage(weather.getSwellHeightNorm(), message);
    
    message = "tides/period";
    this->sendFloatMessage(weather.getSwellPeriodNorm(), message);

//    message = "Weather/MoonPhase";
//    this->sendStringMessage(weather.getMoonPhase(), message);
//
//    message = "Weather/SunPosition";
//    this->sendStringMessage(weather.getSunPosition(), message);
//
//    message = "Weather/Sunrise";
//    this->sendStringMessage(weather.getSunrise(), message);
//
//    message = "Weather/Sunset";
//    this->sendStringMessage(weather.getSunset(), message);
}



