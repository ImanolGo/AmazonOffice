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
    
}

void ApiManager::setupWeatherTimer()
{
    auto weatherSettings = AppManager::getInstance().getSettingsManager().getWeatherSettings();
    
    m_weatherTimer.setup( weatherSettings.request_time*1000 );
    
    m_weatherTimer.start( false ) ;
    ofAddListener( m_weatherTimer.TIMER_COMPLETE , this, &ApiManager::weatherTimerCompleteHandler ) ;
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


void ApiManager::update()
{
    this->updateTimers();
}

void ApiManager::updateTimers()
{
    m_weatherTimer.update();
 
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
    }
}




void ApiManager::parseWeather(string xml)
{
    ofXml weatherXml;
    
    if(!weatherXml.parse( xml )){
        ofLogNotice() <<"ApiManager::parseWeather << Unable to parse weather: " << xml;
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





