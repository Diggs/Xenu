/* 
 * File:   GUIApplicationPanel.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 10:00 PM
 */

#include "GUIApplicationPanel.h"
#include "ThemeManager.h"
#include "LogManager.h"
#include <stdio.h>
#include <zlx/Draw.h>

using namespace ZLX;

GUIApplicationPanel::GUIApplicationPanel(LibXenonApplication libXenonApplication) 
{
    application = libXenonApplication;
    _x = -1.0f;
    _y = 1.0f;
}


GUIApplicationPanel::GUIApplicationPanel(const GUIApplicationPanel& orig) {
}


GUIApplicationPanel::~GUIApplicationPanel() 
{
    
}


void GUIApplicationPanel::update(float x, float y)
{
    _x = x;
    _y = y;
    
    char* message1;
    message1 = (char*)malloc(512);
    
    sprintf(message1, "Updating %s to x %4.2f y %4.2f\n", application.Name.c_str(), _x, _y);
    
    LogManager::Log(message1);
}

    
void GUIApplicationPanel::draw()
{
    char* message1;
    message1 = (char*)malloc(512);
    
    sprintf(message1, "Drawing %s at x %4.2f y %4.2f\n", application.Name.c_str(), _x, _y);
    
    LogManager::Log(message1);
    
    Draw::DrawColoredRect(_x, _y, 0.3f, 0.3f, ThemeManager::GetPanelColor());
}