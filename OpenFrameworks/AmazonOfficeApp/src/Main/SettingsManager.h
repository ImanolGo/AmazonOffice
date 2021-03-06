/*
 *  SettingsManager.h
 *  AmazonOfficeApp
 *
 *  Created by Imanol Gomez on 30/03/18.
 *
 */

#pragma once

#include "Manager.h"
#include "ApiManager.h"


//========================== class SettingsManager ==============================
//============================================================================
/** \class SettingsManager SettingsManager.h
 *    \brief Class managing the whole settings of the application
 *    \details it reads from an xml settings file and provides access to the information
 */

typedef             map<string,string>               ResourcesPathMap;       ///< defines a map of path attached to the resources name

class SettingsManager: public Manager
{

public:
    
    static const string APPLICATION_SETTINGS_FILE_NAME;
    
    //! Destructor
    ~SettingsManager();
    
    //! Constructor
    SettingsManager();
    
    //! Compares two transition objects
    void setup();
    
    const ResourcesPathMap& getTextureResourcesPath() const {return m_texturesPath;}
    
    const ResourcesPathMap& getVideoResourcesPath() const {return m_videoResourcesPath;}
    
    ofColor getColor(const string& colorName);
    
    float getAppWidth() const {return m_appWidth;}
    
    float getAppHeight() const {return m_appHeight;}
    
    string getIpAddress() const {return m_ipAddress;}
    
    string getSpoutName() const {return m_spoutName;}
    
    int getOscPortReceive() const {return m_portOscReceive;}
    
    int getOscPortSend() const {return m_portOscSend;}
    
    float getSceneTimer() const {return m_sceneTimer;}
    
    api_settings getWeatherSettings() const {return m_weatherSettings;}
    
    api_settings getSkySettings() const {return m_skySettings;}
    
    api_settings getSurfSettings() const {return m_surfSettings;}
    
    api_settings getTrafficSettings() const {return m_trafficSettings;}
    
    
private:
    
    //! Loads the settings file
    bool loadSettingsFile();
    
    //! Loads all the settings
    void loadAllSettings();
    
    //! Sets all the debug properties
    void setDebugProperties();
    
    //! Sets all the network properties
    void setNetworkProperties();
    
    //! Sets all the api properties
    void setApiProperties();
    
    //! Sets all the window properties
    void setWindowProperties();
    
    //! Loads all the app colors
    void loadColors();
    
    //! Loads all the textures settings
    void loadTextureSettings();
    
    //! Loads all the video  settings
    void loadVideoSettings();
    
private:
    
    typedef             map< string, ofPtr<ofColor> >    ColorMap;               ///< Defines a map of colors attached to a name
    
    
    ofXml                    m_xml;                  ///< instance of the xml parser
    ResourcesPathMap        m_texturesPath;         ///< stores the texture paths
    ResourcesPathMap        m_videoResourcesPath;   ///< stores the video paths
    ColorMap                m_colors;               ///< stores all the application's colors
    float                   m_appWidth;             ///< stores the applications width
    float                   m_appHeight;            ///< stores the applications height
    int                     m_portOscReceive;       ///< stores the  port to receive OSC messages from
    int                     m_portOscSend;          ///< stores the  port to send OSC messages to
    string                  m_ipAddress;            ///< stores the Ip Address used for the Network communications
    string                  m_spoutName;            ///<stores the name of the spout pipe name
    float                   m_sceneTimer;           ///< stores the time between scene
    api_settings            m_weatherSettings;      ///<stores the weather api's settings
    api_settings            m_skySettings;          ///<stores the sky api's settings
    api_settings            m_surfSettings;         ///<stores the surf's settings
    api_settings            m_trafficSettings;      ///<stores the traffic's settings
    
};


