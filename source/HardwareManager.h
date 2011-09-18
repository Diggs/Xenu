/* 
 * File:   HardwareManager.h
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 10, 2011, 5:27 PM
 */

#ifndef HARDWAREMANAGER_H
#define	HARDWAREMANAGER_H

class HardwareManager {
    
    
    
public:
    HardwareManager();
    virtual ~HardwareManager();
    
    static void InitializeXbox();
    
    static void GetSystemTemperatures(float *cpu, float *gpu, float *memory, float *motherboard);
private:
    
};

#endif	/* HARDWAREMANAGER_H */