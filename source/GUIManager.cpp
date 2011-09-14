/* 
 * File:   GUIManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 10:06 PM
 */

#include "GUIManager.h"
#include "HardwareManager.h"
#include "LogManager.h"
#include "Verdana_16_abc.h"
#include "Verdana_16_png.h"
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
    //void *pFontData = NULL;
    //static ZLXTexture *pFontTexture = NULL;

    //pFontData = (void*) Verdana_16_abc;
    //extern struct XenosSurface * loadPNGFromMemory(unsigned char *PNGdata);
    //pFontTexture = loadPNGFromMemory((unsigned char*) Verdana_16_png);
    
    //xenuFont.Create(pFontTexture, pFontData);
}


void GUIManager::update() {

    LogManager::Log("Running GUIManager update().\n");
    
    // Update system temperatures
    HardwareManager::GetSystemTemperatures(&cpuTemp, &gpuTemp, &memoryTemp, &motherboardTemp);
    
}


void GUIManager::draw() {

    LogManager::Log("Running gui manager draw().\n");
    
    Begin();

    
    End();
    
    LogManager::Log("Finished running gui manager draw().\n");
}