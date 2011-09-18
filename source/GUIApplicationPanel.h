/* 
 * File:   GUIApplicationPanel.h
 * Author: tyler
 *
 * Created on September 12, 2011, 10:00 PM
 */

#include "LibXenonApplication.h"

#ifndef GUIAPPLICATIONPANEL_H
#define	GUIAPPLICATIONPANEL_H


class GUIApplicationPanel {
public:
    GUIApplicationPanel(LibXenonApplication libXenonApplication);
    GUIApplicationPanel(const GUIApplicationPanel& orig);
    virtual ~GUIApplicationPanel();
    
    void update(float x, float y);
    
    void draw();

private:
    LibXenonApplication application;

    float _x, _y;
    bool _selected;
};

#endif	/* GUIAPPLICATIONPANEL_H */

