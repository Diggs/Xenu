/* 
 * File:   DeviceManager.h
 * Author: Tyler Power
 *
 * Created on September 9, 2011, 11:54 PM
 */

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#ifndef DEVICEMANAGER_H
#define	DEVICEMANAGER_H

class DeviceManager {
public:
    DeviceManager();
    virtual ~DeviceManager();
    
    /**
     * Gets a vector of all available devices.
     * @return A vector of available device names as strings.
     */
    static vector<string> GetDevices();
    
    
    /**
     * Creates a path to the root of a device.
     * @param deviceName The name of the device to construct a path for.
     * @return  The path to the root directory of the device.
     */
    static string GetDeviceRootPath(string deviceName);
private:

};

#endif	/* DEVICEMANAGER_H */

