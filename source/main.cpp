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


struct controller_data_s updateInput()
{
    // Will contain current state of game pad
    static struct controller_data_s controller;
    
    // Poll for USB devices..
    usb_do_poll();
    
    // Update the game pad state
    get_controller_data(&controller, 0);
    
    // Logo quits the app...
    if(controller.logo) {
        shouldQuit = true;
    }
    
    return controller;
}


void update()
{
    struct controller_data_s controller = updateInput();

    gui.update(controller);
}


void draw()
{   
    Begin();
    
    gui.draw();
    
    End();
}


int main()
{
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