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
    static struct controller_data_s xboxController;
    
    // Poll for USB devices..
    usb_do_poll();
    
    // Update the game pad state
    get_controller_data(&xboxController, 0);
    
    // Logo quits the app...
    if(xboxController.logo) {
        shouldQuit = true;
    }
    
    return xboxController;
}


void update()
{
    //struct controller_data_s xboxController = updateInput();

    LogManager::Log("Running main loop update()\n");
    
    gui.update();
}


void draw()
{
    
    LogManager::Log("Running main loop draw()\n");
    
    gui.draw();
}


int main()
{
    // Initialize the Xbox 360 hardware
    HardwareManager::InitializeXbox(false);
    
    gui.initialize();
    
    LogManager::Log("Xbox Hardware initialized, running main loop.\n");
    
    // Run the main loop
    while(!shouldQuit) {

        LogManager::Log("Running main loop.\n");
        
        update();

        draw();
    }
    
    return 0;
}