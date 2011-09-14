/* 
 * File:   GUIManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 10:06 PM
 */

#include "GUIManager.h"
#include "HardwareManager.h"
#include "ThemeManager.h"
#include "LogManager.h"
#include "Verdana_16_abc.h"
#include "Verdana_16_png.h"
#include <xenos/xe.h>
#include <sstream>
#include <iostream>
#include <zlx/zlx.h>
#include <zlx/Utils.h>

using namespace ZLX;
using namespace std;


GUIManager::GUIManager() {
    
    
}

//GUIManager::GUIManager(const GUIManager& orig) {
//}

GUIManager::~GUIManager() {
    
}


void GUIManager::initialize() 
{
    LogManager::Log("Running GUIManager constructor.\n");
    
    // Initialize video once for the life time of the application
    InitialiseVideo();
    
    // Load font data
    void *pFontData = (void*) Verdana_16_abc;
    ZLXTexture *pFontTexture = loadPNGFromMemory((unsigned char*) Verdana_16_png);
    
    // Create the font
    xenuFont.Create(pFontTexture, pFontData);
}


void GUIManager::update() {

    // Update system temperatures
    HardwareManager::GetSystemTemperatures(&cpuTemp, &gpuTemp, &memoryTemp, &motherboardTemp);
    
}


void GUIManager::draw() {
    
    Begin();
    
    // Draw the background
    Xe_SetClearColor(g_pVideoDevice, ThemeManager::GetBackgroundColor());
    
    xenuFont.Begin();
    
    // Draw the system temps
    xenuFont.DrawText("Temps", 0xFFFFFF00, 0, 50);
    
    xenuFont.End();
    
    End(); 
}