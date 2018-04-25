/*
 *  ApiManager.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */


#include "ApiManager.h"
#include "AppManager.h"
#include "ofxJSON.h"


ApiManager::ApiManager(): Manager()
{
    //Intentionally left empty
}

ApiManager::~ApiManager()
{
    ofLogNotice() << "ApiManager::destructor";
    ofUnregisterURLNotification(this);
}


//--------------------------------------------------------------

void ApiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    this->setupApis();
    this->setupSkyApi();
    this->setupTimers();
    
    ofRegisterURLNotification(this);
    
    ofLogNotice() <<"ApiManager::initialized" ;
}

void ApiManager::setupApis()
{
    this->setupWeatherApi();
}

void ApiManager::setupTimers()
{
    this->setupWeatherTimer();
    this->setupSkyTimer();
}

void ApiManager::setupWeatherTimer()
{
    auto weatherSettings = AppManager::getInstance().getSettingsManager().getWeatherSettings();
    
    m_weatherTimer.setup( weatherSettings.request_time*1000 );
    
    m_weatherTimer.start( false ) ;
    ofAddListener( m_weatherTimer.TIMER_COMPLETE , this, &ApiManager::weatherTimerCompleteHandler ) ;
}

void ApiManager::setupSkyTimer()
{
    auto skySettings = AppManager::getInstance().getSettingsManager().getSkySettings();
    
    m_skyTimer.setup( skySettings.request_time*1000 );
    
    m_skyTimer.start( false ) ;
    ofAddListener( m_skyTimer.TIMER_COMPLETE , this, &ApiManager::skyTimerCompleteHandler ) ;
}


void ApiManager::setupWeatherApi()
{
    auto weatherSettings = AppManager::getInstance().getSettingsManager().getWeatherSettings();
    
    //m_weatherUrl = "http://api.openweathermap.org/data/2.5/weather?q=";
    m_weatherUrl = weatherSettings.url;
    m_weatherUrl+="lat=";
    m_weatherUrl+=ofToString(weatherSettings.lat);
    m_weatherUrl+="&lon=";
    m_weatherUrl+=ofToString(weatherSettings.lon);
    //m_weatherUrl+=weatherSettings.city;
    m_weatherUrl+="&units=";
    m_weatherUrl+=weatherSettings.units;
    m_weatherUrl+="&appid=";
    m_weatherUrl+=weatherSettings.key;
    m_weatherUrl+="&mode=xml";
    
    ofLogNotice() <<"ApiManager::setupWeatherApi << weather url = " <<  m_weatherUrl;
    
    ofLoadURLAsync(m_weatherUrl, "weather");
    
}

void ApiManager::setupSkyApi()
{
    auto skySettings = AppManager::getInstance().getSettingsManager().getSkySettings();
    
    m_skyUrl = "https://";
    m_skyUrl += skySettings.id;
    m_skyUrl += ":";
    m_skyUrl += skySettings.key;
    m_skyUrl += "@";
    m_skyUrl += skySettings.url;
    m_skyUrl+="lamin=";
    m_skyUrl+=ofToString(skySettings.lat);
    m_skyUrl+="&lomin=";
    m_skyUrl+=ofToString(skySettings.lon);
    m_skyUrl+="&lamax=";
    m_skyUrl+=ofToString(skySettings.lat2);
    m_skyUrl+="&lomax=";
    m_skyUrl+=ofToString(skySettings.lon2);
    
    
    ofLogNotice() <<"ApiManager::setupSkyApi << surf url = " <<  m_skyUrl;
    
    ofLoadURLAsync(m_skyUrl, "sky");
    
}


void ApiManager::update()
{
    this->updateTimers();
}

void ApiManager::updateTimers()
{
    m_weatherTimer.update();
    m_skyTimer.update();

}

void ApiManager::urlResponse(ofHttpResponse & response)
{
    //ofLogNotice() <<"ApiManager::urlResponse -> " << response.request.name << ", " << response.status;
    

    if(response.status==200)
    {
        if(response.request.name == "weather")
        {
            m_weatherTimer.start(false);
            this->parseWeather(response.data);
            AppManager::getInstance().getGuiManager().onWeatherChange();
            AppManager::getInstance().getOscManager ().sendOscAll();
        }
        
        else if(response.request.name == "sky")
        {
            m_skyTimer.start(false);
            this->parseSky(response.data);
        }
    }
}



void ApiManager::parseSky(string response)
{
    //ofLogNotice() << "ApiManager::parseSky << Data: " << response;
    
    ofxJSONElement json(response);
    m_flights.clear();
    
    for(int i=0; i<json["states"].size(); i++)
    {
        ofPtr<AirplaneStatus> flight = ofPtr<AirplaneStatus>(new AirplaneStatus());
        flight->m_callsign = json["states"][i][1].asString();
        flight->m_latitude = json["states"][i][6].asFloat();
        flight->m_longitude = json["states"][i][5].asFloat();
        flight->m_altitude = json["states"][i][7].asFloat();
        flight->m_velocity = json["states"][i][9].asFloat();
        flight->m_heading = json["states"][i][10].asFloat();
        flight->m_verticalRate = json["states"][i][11].asFloat();
        
        ofLogNotice() << "ApiManager::parseSky << Flight: " << flight->m_callsign <<", latitude: " << flight->m_latitude<< ", longitude: " << flight->m_longitude<<", altitude: " << flight->m_altitude<< ", velocity: " << flight->m_velocity<< ", heading: " << flight->m_heading<< ", vertical rate: " << flight->m_verticalRate;
        
        m_flights.push_back(flight);
        
        //flight->m_callsign  = "lalal";
    }
}

void ApiManager::parseWeather(string response)
{
    ofXml weatherXml;
    
    if(!weatherXml.parse( response )){
        ofLogNotice() <<"ApiManager::parseWeather << Unable to parse weather: " << response;
        return;
    }
    
     //ofLogNotice() <<"ApiManager::parseWeather << Parsing weather " << xml;
    
   // weatherXml.parse( xml ); // now get the buffer as a string and make XML
    
    string path = "//current/temperature";
    auto xmlChild = weatherXml.findFirst(path);
    m_weatherConditions.m_temp = xmlChild.getAttribute("value").getFloatValue();
    
    path = "//current/humidity";
    xmlChild =weatherXml.findFirst(path);
    m_weatherConditions.m_humidity = xmlChild.getAttribute("value").getFloatValue();
    
    path = "//current/wind/speed";
    xmlChild =weatherXml.findFirst(path);
    m_weatherConditions.m_windSpeed =  xmlChild.getAttribute("value").getFloatValue();
    
    path = "//current/wind/direction";
    xmlChild =weatherXml.findFirst(path);
    m_weatherConditions.m_windDirection =  xmlChild.getAttribute("value").getFloatValue();
    
    path = "//current/clouds";
    xmlChild =weatherXml.findFirst(path);
    m_weatherConditions.m_clouds =  xmlChild.getAttribute("value").getFloatValue();
    
    path = "//current/precipitation";
    xmlChild = weatherXml.findFirst(path);
    m_weatherConditions.m_precipitationValue =  xmlChild.getAttribute("value").getFloatValue();
    m_weatherConditions.m_precipitationMode =  xmlChild.getAttribute("mode").getValue();
    if(m_weatherConditions.m_precipitationMode  == "no"){
        m_weatherConditions.m_precipitationValue = 0;
    }
    
    path = "//current/city/sun";
    xmlChild =weatherXml.findFirst(path);
    m_weatherConditions.m_sunrise = m_weatherConditions.getFormatTime(xmlChild.getAttribute("rise").getValue());
    m_weatherConditions.m_sunset = m_weatherConditions.getFormatTime(xmlChild.getAttribute("set").getValue());
    
    path = "//current/city";
    xmlChild = weatherXml.findFirst(path);
    m_weatherConditions.m_city = xmlChild.getAttribute("name").getValue();
    
    m_weatherConditions.m_moonPhase = m_weatherConditions.getCurrentMoonPhase();
    
    m_weatherConditions.m_sunPosition = m_weatherConditions.calculatePosition();
    
    ofLogNotice() <<"ApiManager::parseWeather << parseWeather -> city = " << m_weatherConditions.m_city <<", temp = " <<  m_weatherConditions.m_temp
    << ", humidity = " << m_weatherConditions.m_humidity
    << ", wind speed = " << m_weatherConditions.m_windSpeed << ", wind direction = " << m_weatherConditions.m_windDirection
    << ", clouds = " << m_weatherConditions.m_clouds
    << ", precipitation mode = " << m_weatherConditions.m_precipitationMode  << ", precipitation value = " << m_weatherConditions.m_precipitationValue
    << ", sunrise = " << m_weatherConditions.m_sunrise  << ", sunset = " << m_weatherConditions.m_sunset
    << ", moon phase  = " << m_weatherConditions.getMoonPhaseInt() << ", sun position = " << m_weatherConditions.m_sunPosition;
    
}

void ApiManager::weatherTimerCompleteHandler( int &args )
{
    //ofLogNotice() <<"ApiManager::weatherTimerCompleteHandler";
    //m_weatherTimer.start(false);
    ofLoadURLAsync(m_weatherUrl, "weather");
}

void ApiManager::skyTimerCompleteHandler( int &args )
{
    //ofLogNotice() <<"ApiManager::weatherTimerCompleteHandler";
    //m_weatherTimer.start(false);
    ofLoadURLAsync(m_skyUrl, "sky");
}




