/* 
 * File:   LibXenonApplicationManager.h
 * Author: tyler
 *
 * Created on September 10, 2011, 6:10 PM
 */

#include "LibXenonApplication.h"
#include <string>
#include <vector>

using namespace std;

#ifndef LIBXENONAPPLICATIONMANAGER_H
#define	LIBXENONAPPLICATIONMANAGER_H

class LibXenonApplicationManager {
public:
    LibXenonApplicationManager();
    virtual ~LibXenonApplicationManager();
    
    static vector<LibXenonApplication> GetApplications(string directoryPath);
private:

};

#endif	/* LIBXENONAPPLICATIONMANAGER_H */

