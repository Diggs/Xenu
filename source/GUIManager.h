/* 
 * File:   GUIManager.h
 * Author: Tyler Power
 *
 * Created on September 12, 2011, 10:06 PM
 */

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <zlx/zlx.h>
#include <zlx/Font.h>
#include <usb/usbmain.h>
#include <input/input.h>
#include "GUIApplicationPanel.h"
#include "LibXenonApplication.h"

using namespace std;

#ifndef GUIMANAGER_H
#define	GUIMANAGER_H

class GUIManager {
public:
    GUIManager();

    virtual ~GUIManager();
    
    void initialize();
    
    void update(controller_data_s controller);
    
    void draw();
    
private:
    
    enum ViewMode {APPLICATIONS, GAMES, EMULATORS};
    
    ViewMode viewMode;
    
    void UpdateViewMode(controller_data_s controller);
    
    void UpdatePanels(controller_data_s controller);
    
    void UpdateCurrentPanels();
    
    void DrawViewMode();
    
    void DrawTemperatures();
    
    void DrawPanels();
    
    void CreateApplicationPanels();
       
    ZLX::Font xenuFont;
    
    vector<GUIApplicationPanel> *currentPanels;
    
    vector<GUIApplicationPanel> applicationPanels;
    
    vector<GUIApplicationPanel> gamePanels;
    
    vector<GUIApplicationPanel> emulatorPanels;
    
    float cpuTemp;
    
    float gpuTemp;
    
    float memoryTemp;
    
    float motherboardTemp;
    
    bool isKeyDown;
    
    enum CurrentKeyDown {RB, LB};
    
    CurrentKeyDown currentKeyDown;
};

#endif	/* GUIMANAGER_H */

