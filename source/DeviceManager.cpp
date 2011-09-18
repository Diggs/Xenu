/* 
 * File:   DeviceManager.cpp
 * Author: Tyler Power
 * 
 * Created on September 9, 2011, 11:54 PM
 */

#include "DeviceManager.h"
#include <stdio.h>
#include <diskio/diskio.h>
#include "LogManager.h"

DeviceManager::DeviceManager() {
}



DeviceManager::~DeviceManager() {
}


vector<string> DeviceManager::GetDevices()
{
    // A vector that will hold all devices
    vector<string> devices;
    
    // Will contain the name of the current device
    const char *device;
    
    // Handle to the current device
    int deviceHandle = -1;
    
    // Get the first device
    deviceHandle = bdev_enum(deviceHandle, &device);
        
    // Make sure we found a device
    while(deviceHandle >= 0) {
        
        // Create a new string containing the device name
        string deviceString(device);
        
        // Add the device to our vector
        devices.push_back(deviceString);
        
        // Get the next device
        deviceHandle = bdev_enum(deviceHandle, &device);
    }
        
    return devices;
}


string DeviceManager::GetDeviceRootPath(string deviceName)
{
    string deviceRoot = deviceName + ":/";
    
    return deviceRoot;
}