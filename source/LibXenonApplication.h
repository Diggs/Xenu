/* 
 * File:   LibXenonApplication.h
 * Author: Tyler Power
 *
 * Created on September 10, 2011, 6:02 PM
 */
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#ifndef LIBXENONAPPLICATION_H
#define	LIBXENONAPPLICATION_H

class LibXenonApplication {
public:
    LibXenonApplication();
    virtual ~LibXenonApplication();
    
    string ExecutablePath;
    string ThumbnailPath;
    string BackgroundPath;
    string Name;
private:

};

#endif	/* LIBXENONAPPLICATION_H */

