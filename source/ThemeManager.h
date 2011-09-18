/* 
 * File:   ThemeManager.h
 * Author: tyler
 *
 * Created on September 14, 2011, 2:04 AM
 */

#include <zlx/zlx.h>

#ifndef THEMEMANAGER_H
#define	THEMEMANAGER_H

class ThemeManager {
public:
    ThemeManager();
    ThemeManager(const ThemeManager& orig);
    virtual ~ThemeManager();
    
    static ZLXColor GetBackgroundColor();
    static ZLXColor GetTextColor();
    static ZLXColor GetActiveTextColor();
    static ZLXColor GetDisabledTextColor();
    static ZLXColor GetPanelColor();
private:

};

#endif	/* THEMEMANAGER_H */

