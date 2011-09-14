/* 
 * File:   HardwareManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 10, 2011, 5:27 PM
 */

#include "HardwareManager.h"
#include <stdio.h>
#include <string.h>
#include <usb/usbmain.h>
#include <input/input.h>
#include <xenos/xenos.h>
#include <xenos/xe.h>
#include <diskio/ata.h>
#include <diskio/diskio.h>
#include <diskio/dvd.h>
#include <console/console.h>
#include <xenon_soc/xenon_power.h>
#include <xenon_smc/xenon_smc.h>

HardwareManager::HardwareManager() {
}


HardwareManager::~HardwareManager() {
}

void HardwareManager::InitializeXbox(bool enableConsole)
{
    // Will only be instantiated once for the lifetime of the application
    static int initialized = 0;
    
    // Don't do anything if we've already initialized
    if(initialized == 1) return;
    
    // Initialize the display
    xenos_init(VIDEO_MODE_AUTO);
    
    // Make sure all CPU cores are at full speed
    xenon_make_it_faster(XENON_SPEED_FULL);
    
    // Initialize the debug console
    
    // ConsoleEnabled = enableConsole;
    
    // if(ConsoleEnabled) {
    //    console_init();
    // }
    
    // Initialize USB and scan for devices
    usb_init();
    usb_do_poll();
    
    // Initialize HDD's
    xenon_ata_init();
    
    // Initialize DVD
    dvd_init();
    
    // Make sure this only happens once
    initialized = 1;
}


void HardwareManager::GetSystemTemperatures(float *cpu, float *gpu, float *memory, float *motherboard)
{
    uint16_t buf[4];
    xenon_smc_query_sensors(buf);
    
    *cpu = (float)buf[0] / 256.0f;
    *gpu = (float)buf[1] / 256.0f;
    *memory = (float)buf[2] / 256.0f;
    *motherboard = (float)buf[3] / 256.0f;
}