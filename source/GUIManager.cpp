/* 
 * File:   GUIManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 10:06 PM
 */

#include "GUIManager.h"
#include "DeviceManager.h"
#include "LibXenonApplication.h"
#include "LibXenonApplicationManager.h"
#include "HardwareManager.h"
#include "ThemeManager.h"
#include "LogManager.h"
#include "Verdana_16_abc.h"
#include "Verdana_16_png.h"
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <zlx/zlx.h>
#include <zlx/Utils.h>


using namespace ZLX;
using namespace std;


GUIManager::GUIManager() {
    
    
}


GUIManager::~GUIManager() {
    
}


void GUIManager::initialize() 
{
    // Initialize video once for the life time of the application
    InitialiseVideo();
    
    // Load font data
    void *pFontData = (void*) Verdana_16_abc;
    ZLXTexture *pFontTexture = loadPNGFromMemory((unsigned char*) Verdana_16_png);
    
    // Create the font
    xenuFont.Create(pFontTexture, pFontData);
    
    // Set the default view mode
    viewMode = APPLICATIONS;
    
    // Scan and create panels for all applications
    CreateApplicationPanels();
}


void GUIManager::CreateApplicationPanels()
{
    // Get a list of all devices
    vector<string> allDevices = DeviceManager::GetDevices();
    
    // Iterate through all devices
    for(vector<string>::iterator iter = allDevices.begin(); iter != allDevices.end(); ++iter) {
        
        // Construct paths to the applications, games and emulators on the device
        string device = (string(*iter));
        string deviceRootPath = DeviceManager::GetDeviceRootPath(device);
        string applicationsPath = deviceRootPath + "Applications";
        string gamesPath = deviceRootPath + "Games";
        string emulatorsPath = deviceRootPath + "Emulators";
        
        // Get lists of all LibXenon applications in the above paths
        vector<LibXenonApplication> applications = LibXenonApplicationManager::GetApplications(applicationsPath);
        vector<LibXenonApplication> games = LibXenonApplicationManager::GetApplications(gamesPath);
        vector<LibXenonApplication> emulators = LibXenonApplicationManager::GetApplications(emulatorsPath);
        
        // Create panels for applications
        for(vector<LibXenonApplication>::iterator iter = applications.begin(); iter != applications.end(); ++iter) {
            applicationPanels.push_back(GUIApplicationPanel((*iter)));
        }
        
        // Create panels for games
        for(vector<LibXenonApplication>::iterator iter = games.begin(); iter != games.end(); ++iter) {
            gamePanels.push_back(GUIApplicationPanel((*iter)));
        }
        
        // Create panels for emulators
        for(vector<LibXenonApplication>::iterator iter = emulators.begin(); iter != emulators.end(); ++iter) {
            emulatorPanels.push_back(GUIApplicationPanel((*iter)));
        }
    }
}


void GUIManager::UpdateViewMode(controller_data_s controller)
{
    // If left shoulder button push move backwards through views
    if(controller.lb) {
        switch(viewMode) {
            
            case APPLICATIONS:
                viewMode = EMULATORS;
                break;
            
            case GAMES:
                viewMode = APPLICATIONS;
                break;

            case EMULATORS:
                viewMode = GAMES;
                break;
        }
    }
    
    // If right shoulder button push move forwards through views
    if(controller.rb) {
        switch(viewMode) {
            
           case EMULATORS:
                viewMode = APPLICATIONS;
                break;
                
           case APPLICATIONS:
                viewMode = GAMES;
                break;
                
           case GAMES:
                viewMode = EMULATORS;
                break;
        }
    }
}


void GUIManager::update(controller_data_s controller) {

    // Update system temperatures
    HardwareManager::GetSystemTemperatures(&cpuTemp, &gpuTemp, &memoryTemp, &motherboardTemp);
    
    // Update view based on new controller input
    UpdateViewMode(controller);
    
    // Depending on the view mode we only want to target specific panels for update and drawing.
    switch(viewMode) {
        
        case APPLICATIONS:
            currentPanels = &applicationPanels;
            break;
            
        case GAMES:
            currentPanels = &gamePanels;
            break;
            
        case EMULATORS:
            currentPanels = &emulatorPanels;
            break;
    }
    
    // Update the currently selected panels
    int i = 0;
    for(vector<GUIApplicationPanel>::iterator iter = currentPanels->begin(); iter != currentPanels->end(); ++iter) {
        (iter)->update(0.1f * i, 0.3f * i);
        i++;
    }
}


void GUIManager::draw() {
    
    // Update temps
    stringstream ss;
    ss << "CPU " << cpuTemp << "C GPU " << gpuTemp << "C Memory " << memoryTemp << "C Motherboard " << motherboardTemp << "C" << "View Mode: " << viewMode;
    
    // Draw the background
    Xe_SetClearColor(g_pVideoDevice, ThemeManager::GetBackgroundColor());
    
    // Draw the currently selected panels
    for(vector<GUIApplicationPanel>::iterator iter = currentPanels->begin(); iter != currentPanels->end(); ++iter) {
        (iter)->draw();
    }
    
    xenuFont.Begin();
    xenuFont.Scale(0.5f);
    xenuFont.DrawText(ss.str().c_str(), ThemeManager::GetTextColor(), -30, -30);
    xenuFont.End();
}