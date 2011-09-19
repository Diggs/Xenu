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
    return 0xFF545454;
}

ZLXColor ThemeManager::GetDisabledTextColor()
{
    return 0x66FFFFFF;
}

ZLXColor ThemeManager::GetActiveTextColor()
{
    return 0xFF545454;
}


ZLXColor ThemeManager::GetPanelColor()
{
    return 0xFFF09609;
}