/* 
 * File:   ThemeManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 14, 2011, 2:04 AM
 */

#include "ThemeManager.h"

ThemeManager::ThemeManager() {
}

ThemeManager::ThemeManager(const ThemeManager& orig) {
}

ThemeManager::~ThemeManager() {
}


ZLXColor ThemeManager::GetBackgroundColor()
{
    return 0xFFFFFFFF;
}


ZLXColor ThemeManager::GetTextColor()
{
    return 0xFF000000;
}


ZLXColor ThemeManager::GetPanelColor()
{
    return 0xFF000000;
}