/* 
 * File:   Main.cpp
 * Author: Tyler Power
 *
 * Created on September 8, 2011, 6:54 PM
 */


#include <usb/usbmain.h>
#include <input/input.h>
#include "HardwareManager.h"
#include "GUIManager.h"
#include "LogManager.h"
#include <iostream>
#include <sstream>
#include <string>
#include <zlx/zlx.h>
#include <zlx/Utils.h>
#include <zlx/Draw.h>

using namespace ZLX;
using namespace std;

/*
 Xenu Version number
 */
const int XENU_VERSION = 1;

/*
 * If set to true will cause the main loop to break and as
 * a result the application will close.
 */
bool shouldQuit = false;


static GUIManager gui;


struct controller_data_s controller;


struct controller_data_s updateInput()
{
    // Poll for USB devices..
    usb_do_poll();
    
    // Update the game pad state
    get_controller_data(&controller, 0);
    
    /*
    if(controller.s1_x > STICK_THRESHOLD || controller.s1_x < -STICK_THRESHOLD || controller.s1_y > STICK_THRESHOLD || controller.s1_y < -STICK_THRESHOLD) {
        stringstream ss;
        ss << "stick1Y " << controller.s1_y << " stick1X " << controller.s1_x << endl;
        LogManager::Log(ss.str().c_str());
    }
    */
    
    // Logo quits the app...
    if(controller.logo) {
        shouldQuit = true;
    }
    
    return controller;
}


void update()
{
    updateInput();

    gui.update(&controller);
}


void draw()
{   
    Begin();
    
    gui.draw();
    
    End();
}


int main()
{
    memset(&controller, 0, sizeof (struct controller_data_s));
    
    // Initialize the Xbox 360 hardware
    HardwareManager::InitializeXbox();
    
    // Initialiaze the GUI
    gui.initialize();
    
    // Run the main loop
    while(!shouldQuit) {
        
        update();

        draw();
    }
    
    return 0;
}