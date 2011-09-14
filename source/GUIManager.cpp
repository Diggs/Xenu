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
#include <time/time.h>
#include <iostream>
#include <zlx/zlx.h>
#include <zlx/Utils.h>
#include <zlx/Draw.h>

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
    
    stringstream ss;
    
    ss << "CPU " << cpuTemp << "C GPU " << gpuTemp << "C Memory " << memoryTemp << "C Motherboard " << motherboardTemp << "C";
    
    Begin();
    
    // Draw the background
    Xe_SetClearColor(g_pVideoDevice, ThemeManager::GetBackgroundColor());

    ZLX::Draw::DrawColoredRect(0, 0, 1, 1, 0xFF00FF00);

    // Draw some text using font
    xenuFont.Begin();

    // It use screen coord
    xenuFont.Scale(2.0f);
    xenuFont.DrawText(ss.str().c_str(), 0x00000000, 100, 18);
    xenuFont.Scale(1.0f);
    xenuFont.DrawText(ss.str().c_str(), 0xFFFF0000, 300, 200);

    // End of using
    xenuFont.End();
    
    End(); 
}