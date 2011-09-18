/* 
 * File:   LibXenonApplicationManager.cpp
 * Author: Tyler Power
 * Email: tyler@digitalreality.co.nz
 * 
 * Created on September 10, 2011, 6:10 PM
 */

#include "LibXenonApplicationManager.h"
#include "FileManager.h"
#include "LogManager.h"
#include <iostream>

using namespace std;

LibXenonApplicationManager::LibXenonApplicationManager() {
}


LibXenonApplicationManager::~LibXenonApplicationManager() {
}

vector<LibXenonApplication> LibXenonApplicationManager::GetApplications(string directoryPath)
{
    //LogManager::Log("Looking for applications in %s\n", directoryPath.c_str());
    
    // A vector of applications we will return
    vector<LibXenonApplication> applications = vector<LibXenonApplication>();
    
    // Get a list of all directories at the specified path
    vector<dirent> directories = FileManager::GetDirectoryListing(directoryPath, FILEMANAGER_DIRECTORIES);
    
    // Iterate through all directories
    for(std::vector<dirent>::iterator iter = directories.begin(); iter != directories.end(); ++iter) {
        
        // Create a path to this subfolder
        string subFolderName = (dirent(*iter)).d_name;
        string subFolderPath = directoryPath + "/" + subFolderName;
        
        // Get a list of all files in the subfolder
        vector<dirent> files =  FileManager::GetDirectoryListing(subFolderPath, FILEMANAGER_FILES);
        
        // Iterate through the files
        for(std::vector<dirent>::iterator iter = files.begin(); iter != files.end(); ++iter) {

            string fileName = (dirent(*iter)).d_name;
            string elfExtension = ".elf";
            
            // Check if the file is an executable
            if(fileName.find(elfExtension) != string::npos) {
                
                // Create a new application
                LibXenonApplication application;
                
                // Set the name of the application
                application.Name = subFolderName;
                
                // Set the path to the executable
                application.ExecutablePath = subFolderPath + "/" + fileName;
                
                // Set the path to the thumbnail
                application.ThumbnailPath = subFolderPath + "/" + "thumbnail.png";
                
                // Set the path to the background image
                application.BackgroundPath = subFolderPath + "/" + "background.png";
                
                // Add the application to the vector
                applications.push_back(application);
            }
        }
    }
    
    return applications;
}