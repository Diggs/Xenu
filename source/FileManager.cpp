/* 
 * File:   FileManager.cpp
 * Author: Tyler Power
 * 
 * Created on September 8, 2011, 6:54 PM
 */

#include "FileManager.h"
#include <stdio.h>
#include <string.h>


FileManager::FileManager() {
}


FileManager::~FileManager() {
    
}

std::vector<dirent> FileManager::GetDirectoryListing(string directoryPath, int fileType)
{
    // A vector of directory entries we will return
    vector<dirent> directoryEntries = vector<dirent>();
    
    // Open the path we were provided
    DIR *directory = opendir(directoryPath.c_str());
    
    // Make sure we were able to open the directory
    if(directory) {
        
        // Read the first entry in the directory
        struct dirent *directoryEntry = readdir(directory);
        
        // While we have a directory entry
        while(directoryEntry) {
            
            // Make sure we're only adding files that the caller has specified
            if(fileType == FILEMANAGER_ALL || 
                    (fileType == FILEMANAGER_DIRECTORIES && directoryEntry->d_type == DT_DIR) || 
                    (fileType == FILEMANAGER_FILES && directoryEntry->d_type == DT_REG)) {
                
                // Make sure this directory entry is not the current directory or the parent directory
                string fileName = directoryEntry->d_name;
                if(fileName.compare(".") != 0 && fileName.compare("..") != 0) {
                    // Add this directory entry to the vector
                    directoryEntries.push_back(*directoryEntry);
                }
            }

            // Read the next directory
            directoryEntry = readdir(directory);
        }
        
        // Close the directory
        closedir(directory);
    }
    
    return directoryEntries;
}