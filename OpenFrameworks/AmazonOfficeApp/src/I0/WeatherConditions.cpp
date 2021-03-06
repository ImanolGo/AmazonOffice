/*
 *  WeatherConditions.cpp
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */

#include "WeatherConditions.h"

#include <math.h>

#define        RAD    (PI/180.0)
#define        SMALL_FLOAT    (1e-12)


WeatherConditions::WeatherConditions()
{
    this->setupPatameters();
}

WeatherConditions::~WeatherConditions()
{
    //Intentionally left empty
}


//--------------------------------------------------------------

void WeatherConditions::setupPatameters()
{
    m_temp.set("Temperature", 20.0, 10.0, 30.0);
    m_humidity.set("Humidity", 30.0, 0, 100.0);
    m_windSpeed.set("Wind Speed", 10.0, 0, 100.0);
    m_windDirection.set("Wind Direction", 10.0, 0, 360);
    m_sunPosition.set("Sun Position", 0.0, 0.0, 1.0);
    m_moonPhase.set("Moon Phase", 0.0, 0.0, 1.0);
    m_clouds.set("Clouds", 0.0, 0.0, 100.0);
    m_precipitationValue.set("Precipitation", 0.0, 0.0, 20.0);
    m_precipitationMode = "no";
    m_city = "La Caleta";
    m_swellHeight.set("Swell Height", 1.0, 0.0, 4);
    m_swellPeriod.set("Swell Period", 15.0, 0.0, 20);
    m_swellPeriod.set("ID", 0, 0, 900);
    
}

float WeatherConditions::getTemperatureNorm()
{
    return ofMap(m_temp, m_temp.getMin(), m_temp.getMax(), 0.0, 1.0,true);
}

float WeatherConditions::getCloudinessNorm()
{
    return ofMap(m_clouds, m_clouds.getMin(), m_clouds.getMax(), 0.0, 1.0,true);
}
float WeatherConditions::getPrecipitationNorm()
{
    return ofMap(m_precipitationValue, m_precipitationValue.getMin(), m_precipitationValue.getMax(), 0.0, 1.0,true);
}

float WeatherConditions::getHumidityNorm()
{
    return ofMap(m_humidity, m_humidity.getMin(), m_humidity.getMax(), 0.0, 1.0,true);
}

float WeatherConditions::getWindSpeedNorm()
{
    return ofMap(m_windSpeed, m_windSpeed.getMin(), m_windSpeed.getMax(), 0.0, 1.0,true);
}

float WeatherConditions::getWindDirectionNorm()
{
     return ofMap(m_windDirection, m_windDirection.getMin(), m_windDirection.getMax(), 0.0, 1.0,true);
}


float WeatherConditions::getSunPositionNorm()
{
    return m_sunPosition;
}
float WeatherConditions::getMoonPhaseNorm()
{
    return m_moonPhase;
}

float WeatherConditions::getSwellHeightNorm()
{
    return ofMap(m_swellHeight, m_swellHeight.getMin(), m_swellHeight.getMax(), 0.0, 1.0,true);
}
float WeatherConditions::getSwellPeriodNorm()
{
    return ofMap(m_swellPeriod, m_swellPeriod.getMin(), m_swellPeriod.getMax(), 0.0, 1.0,true);
}

bool WeatherConditions::isDayTime()
{
    float currentTime = 10000*ofGetHours() + 100*ofGetMinutes() + ofGetSeconds();
    float sunrise = this->parseTime(m_sunrise );
    float sunset = this->parseTime(m_sunset );
    ofLogNotice() <<"WeatherConditions::isDayTime -> current time : "<< currentTime
    << ", sunrise = " << sunrise << ", sunset = " << sunset;
    if(currentTime> sunrise && currentTime< sunset){
        ofLogNotice() <<"WeatherConditions::isDayTime -> It's day time";
        return true;
    }
    else{
        ofLogNotice() <<"WeatherConditions::isDayTime -> It's night time";
        return false;
    }
}

float WeatherConditions::parseTime(string timeString)
{
    auto split_string = ofSplitString(timeString, ":");
    
    float time = 0;
    
    if(split_string.size()>0){
        time = time + 10000* ofToFloat(split_string[0]);
    }
    
    if(split_string.size()>1){
        time = time + 100*ofToFloat(split_string[2]);
    }
    
    if(split_string.size()>2){
        time = time +  ofToFloat(split_string[1]);
    }
    
    return time;
}

float WeatherConditions::calculatePosition()
{
    float currentTime = 10000*ofGetHours() + 100*ofGetMinutes() + ofGetSeconds();
    float sunrise = this->parseTime(m_sunrise );
    float sunset = this->parseTime(m_sunset );
    
    return ofMap(currentTime, sunrise, sunset, 0.0,1.0, true);
}

string WeatherConditions::getFormatTime(string timeString)
{
    if(timeString.empty()){
        return "";
    }
    
    
    auto split_string = ofSplitString(timeString, "T");
    
    if(split_string.empty()){
        return "";
    }
    
    if(split_string.size()>1){
        return split_string[1];
    }
    
    return "";
}



