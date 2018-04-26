/*
 *  ApiManager.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxSimpleTimer.h"
#include "MoonCalculator.h"
#include "WeatherConditions.h"
#include "AirplaneStatus.h"
#include "TrafficStatus.h"

struct api_settings
{
    float lat{0.0};
    float lon{0.0};
    float lat2{0.0};
    float lon2{0.0};
    float request_time{2.0};
    string city{"berlin"};
    string key{""};
    string units{"metric"};
    string url{""};
    string id{""};
};



//========================== class ApiManager =======================================
//===================================================================================
/** \class ApiManager ApiManager.h
 *    \brief class for managing several APIs
 *    \details It reads from weather APIs, tide APIs, parses the informations and provides the
 *    methods to read it
 */


class ApiManager: public Manager
{
    
public:
    //! Constructor
    ApiManager();
    
    //! Destructor
    virtual ~ApiManager();
    
    //! setups the manager
    void setup();
    
    //! updates the manager
    void update();
    
    void urlResponse(ofHttpResponse & response);
    
    void weatherTimerCompleteHandler( int &args ) ;
    
    void skyTimerCompleteHandler( int &args ) ;
    
    void surfTimerCompleteHandler( int &args );
    
    void trafficTimerCompleteHandler( int &args ) ;
    
    WeatherConditions& getCurrentWeather() {return m_weatherConditions;}
    
    void onWindSpeedChange(float& value){m_weatherConditions.m_windSpeed = value;}
    
    void onWindDirChange(float& value){m_weatherConditions.m_windDirection = value;}
    
    void onTemperatureChange(float& value){m_weatherConditions.m_temp = value;}
    
    void onHumidityChange(float& value){m_weatherConditions.m_humidity = value;}
    
    void onPrecipitationChange(float& value){m_weatherConditions.m_precipitationValue = value;}
    
    void onCloudsChange(float& value){m_weatherConditions.m_clouds = value;}
    
    void onMoonChange(float& value){m_weatherConditions.m_moonPhase = value;}
    
    void onSunChange(float& value){m_weatherConditions.m_sunPosition = value;}
    
    void onSwellHeightChange(float& value){m_weatherConditions.m_swellHeight = value;}
    
    void onSwellPeriodChange(float& value){m_weatherConditions.m_swellPeriod = value;}
    
    bool isDayTime() {return m_weatherConditions.isDayTime();}
    
private:
    
    void setupApis();
    
    void setupWeatherApi();
    
    void setupSkyApi();
    
    void setupSurfApi();
    
    void setupTrafficApi();
    
    void setupTimers();
    
    void setupWeatherTimer();
    
    void setupSkyTimer();
    
    void setupSurfTimer();
    
    void setupTrafficTimer();
    
    void updateTimers();
    
    void parseWeather(string response);
    
    void parseSky(string response);
    
    void parseSurf(string response);
    
    void parseTraffic(string name, string response);

private:
    
    ofxSimpleTimer          m_weatherTimer;
    ofxSimpleTimer          m_skyTimer;
    ofxSimpleTimer          m_surfTimer;
    ofxSimpleTimer          m_trafficTimer;
    string                  m_weatherUrl;
    string                  m_surfUrl;
    string                  m_skyUrl;
    WeatherConditions       m_weatherConditions;
    
    vector<ofPtr<AirplaneStatus>> m_flights;
    vector<ofPtr<TrafficStatus>> m_streets;
    
};

