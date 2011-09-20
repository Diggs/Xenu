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
#include <math.h>
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
            applicationPanels.push_back(GUIApplicationPanel(*iter));
        }
        
        // Create panels for games
        for(vector<LibXenonApplication>::iterator iter = games.begin(); iter != games.end(); ++iter) {
            gamePanels.push_back(GUIApplicationPanel(*iter));
        }
        
        // Create panels for emulators
        for(vector<LibXenonApplication>::iterator iter = emulators.begin(); iter != emulators.end(); ++iter) {
            emulatorPanels.push_back(GUIApplicationPanel(*iter));
        }
    }
}


void GUIManager::UpdateViewMode(controller_data_s controller)
{
    // If either of these are being pushed we have a keydown state
    if(controller.rb || controller.lb) {
        
        isKeyDown = true;
        
        if(controller.rb) {
            currentKeyDown = RB;
        } else {
            currentKeyDown = LB;
        }
    }
    
    // If either of the shoulder buttons are not being pushed, when they previously were
    // then we have a key up
    if(!controller.rb && !controller.lb && isKeyDown == true)  {

        // If left shoulder button pushed move backwards through views
        if(currentKeyDown == LB) {
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

        // If right shoulder button pushed move forwards through views
        if(currentKeyDown == RB) {
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
        
        // Reset the key down state
        isKeyDown = false;
    }
}


void GUIManager::UpdateCurrentPanels()
{
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
}


void GUIManager::UpdatePanels(controller_data_s controller)
{   
    const float screenHeight = 2.0f;
    const float screenWidth = 2.0f;
    const float screenTop = 1.0f;
    const float screenLeft = -1.0f;
    const float screenRight = 1.0f;

    // The offset that will be applied to the x postion of each panel
    // This should not be affected by controller input.
    float horizontalOffset = 0;
    
    // This offset can be modified to move all panels left or right i.e. By controller input.
    float horizontalOffsetModifier = 0.0f;
    
    // The width of a panel
    float panelWidth = 0.3f;
    
    // The height of a panel
    float panelHeight = 0.3f;
    
    // The amount of space between each panel
    float panelGap = 0.012f;
    
    // How many panels will we draw per screen horizontally
    int horizontalPanels = 5;
    
    // How many panels will we draw per screen vertically
    int verticalPanels = 4;
    
    // Calculate how much horizontal screen space all the panels will take
    float totalWidthOfPanels = (panelWidth * horizontalPanels) + (panelGap * horizontalPanels);
    
    // Calculate how much screen space is left to pad each side of the panels i.e. Center the panels horizontally
    float horizontalScreenPadding = (screenWidth - totalWidthOfPanels) / 2;
    
    // Calculate how much vertical screen space all the panels will take
    float totalHeightOfPanels = (panelHeight * verticalPanels) + (panelGap * verticalPanels);
    
    // Calculate how much screen space is left to pad top and bottom of the panels i.e. Center the panels vertically
    float verticalScreenPadding = (screenHeight - totalHeightOfPanels) / 2;
    
    // How many screens worth of panels do we have
    int renderPasses = ceil(((double)(currentPanels->size())) / (horizontalPanels * verticalPanels));
    
    // The index of the current panel we are updating
    unsigned int panelIndex = 0;
    
    // Render each screens worth of panels
    for(int currentPass = 0; currentPass < renderPasses; currentPass++) {
        
        // If we're on the first pass then we're dealing with a negative offset
        // All subsequent passes will be positive
        if(currentPass == 0) {
            horizontalOffset = (screenLeft + horizontalScreenPadding) + horizontalOffsetModifier;
        } else {
            horizontalOffset = (currentPass * (screenRight + horizontalScreenPadding)) + horizontalOffsetModifier;
        }
        
        for(int verticalPanel = 0; verticalPanel < verticalPanels; verticalPanel++) {
            
            for(int horizontalPanel = 0; horizontalPanel < horizontalPanels; horizontalPanel++) {
                
                // Make sure we haven't exceeded the amount of panels we're drawing...
                if(panelIndex >= currentPanels->size()){break;}

                // Get the panel at the current index
                GUIApplicationPanel& currentPanel = currentPanels->at(panelIndex);
                
                // Calculate its position
                float panelX = horizontalOffset + (horizontalPanel * panelWidth) + (horizontalPanel * panelGap);
                float panelY = (screenTop - verticalScreenPadding - panelHeight) - (verticalPanel * panelHeight) - (verticalPanel * panelGap);
                
                // Update the panel
                currentPanel.update(panelX, panelY);
                
                // Move to the next panel...
                panelIndex++;
            }
        }
    }
}


void GUIManager::update(controller_data_s controller) {

    // Update system temperatures
    HardwareManager::GetSystemTemperatures(&cpuTemp, &gpuTemp, &memoryTemp, &motherboardTemp);
    
    // Update view based on new controller input
    UpdateViewMode(controller);
    
    // Update the "CurrentPanels" member variable to point to the relevant panel collection
    UpdateCurrentPanels();
    
    // Update panels based on currently selected view
    UpdatePanels(controller);
}


void GUIManager::DrawPanels()
{
    for(vector<GUIApplicationPanel>::iterator iter = currentPanels->begin(); iter != currentPanels->end(); ++iter) {
        iter->draw();
    }
}


void GUIManager::DrawViewMode()
{
    string applications = "applications";
    string games = "games";
    string emulators = "emulators";
    
    xenuFont.Scale(0.7f);
    xenuFont.DrawText(applications.c_str(), (viewMode == APPLICATIONS ? ThemeManager::GetActiveTextColor() : ThemeManager::GetDisabledTextColor()), 20, 20);
    xenuFont.DrawText(games.c_str(), (viewMode == GAMES ? ThemeManager::GetActiveTextColor() : ThemeManager::GetDisabledTextColor()), 20 + xenuFont.GetTextWidth(applications.c_str()), 20);
    xenuFont.DrawText(emulators.c_str(), (viewMode == EMULATORS ? ThemeManager::GetActiveTextColor() : ThemeManager::GetDisabledTextColor()), 20 + xenuFont.GetTextWidth(applications.c_str()) + xenuFont.GetTextWidth(games.c_str()), 20);
}


void GUIManager::DrawTemperatures()
{
    stringstream tempsStringStream;
    tempsStringStream << "CPU " << cpuTemp << "C GPU " << gpuTemp << "C Memory " << memoryTemp << "C Motherboard " << motherboardTemp << "C";
    xenuFont.Scale(0.5f);
    xenuFont.DrawText(tempsStringStream.str().c_str(), ThemeManager::GetTextColor(), -30, -30);
}


void GUIManager::draw() {
    
    Xe_SetClearColor(g_pVideoDevice, ThemeManager::GetBackgroundColor());
    
    DrawPanels();
    
    xenuFont.Begin();
    
    DrawViewMode();
    DrawTemperatures();
    
    xenuFont.End();
}