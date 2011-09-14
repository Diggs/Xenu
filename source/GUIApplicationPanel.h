/* 
 * File:   GUIApplicationPanel.h
 * Author: tyler
 *
 * Created on September 12, 2011, 10:00 PM
 */

#include "LibXenonApplication.h"

#ifndef GUIAPPLICATIONPANEL_H
#define	GUIAPPLICATIONPANEL_H

/**
 * This class manages the Xenu GUI. It is responsible for updating and drawing
 * all aspects of the GUI at the appropriate time.
 */
class GUIApplicationPanel {
public:
    GUIApplicationPanel(LibXenonApplication libXenonApplication);
    virtual ~GUIApplicationPanel();
    
    void update();
    
    void draw();
private:
    LibXenonApplication application;
};

#endif	/* GUIAPPLICATIONPANEL_H */

