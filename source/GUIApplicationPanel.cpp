/* 
 * File:   GUIApplicationPanel.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 10:00 PM
 */

#include "GUIApplicationPanel.h"
#include "ThemeManager.h"
#include <zlx/Draw.h>

using namespace ZLX;

GUIApplicationPanel::GUIApplicationPanel(LibXenonApplication libXenonApplication) 
{
    application = libXenonApplication;
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
}

    
void GUIApplicationPanel::draw()
{
    Draw::DrawColoredRect(_x, _y, 0.3f, 0.3f, ThemeManager::GetPanelColor());
}