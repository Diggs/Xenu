/* 
 * File:   LogManager.h
 * Author: tyler
 *
 * Created on September 12, 2011, 1:53 PM
 */

#ifndef LOGMANAGER_H
#define	LOGMANAGER_H

class LogManager {
public:
    LogManager();
    virtual ~LogManager();
    
    static void Log(char const * str);
private:

};

#endif	/* LOGMANAGER_H */

