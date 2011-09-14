/* 
 * File:   FileManager.h
 * Author: Tyler Power
 *
 * Created on September 8, 2011, 6:54 PM
 */

#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>

using namespace std;

#ifndef FILEMANAGER_H
#define	FILEMANAGER_H

const int FILEMANAGER_ALL = 0;
const int FILEMANAGER_DIRECTORIES = 1;
const int FILEMANAGER_FILES = 2;

class FileManager {
public:
    FileManager();
    virtual ~FileManager();
    
    /**
     * Gets a directory listing (All files and folders) from the specified path.
     * @param path The path to get a directory listing of.
     * @param fileType 0 = Folders and files, 1 = Only folders, 2 = Only files;
     * @return A vector of dirent's for each folder/file.
     */
    static vector<dirent> GetDirectoryListing(string directoryPath, int fileType);
    
private:

};

#endif	/* FILEMANAGER_H */

