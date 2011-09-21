/* 
 * File:   LogManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 12, 2011, 1:53 PM
 */

#include "LogManager.h"
#include "HardwareManager.h"
#include <stdio.h>

LogManager::LogManager() {
    
}


LogManager::~LogManager() {
    
}


void LogManager::Log(const char* str)
{
    //#ifdef DEBUGLOG
        // Log out to file
        FILE *log = fopen("uda:/XenuLog.txt","a+");
        fprintf(log, "%s", str);
        fclose(log);
    //#endif
}