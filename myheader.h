/************************************************************************
**      This file includes all header files, extern variables, and     **
**      global functions required by other CPP files.                  **
**                                                                     **
************************************************************************/

//**********************************************************************
// Included/imported header files
//**********************************************************************
#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
using namespace std;

//**********************************************************************
// Extern global variables
//**********************************************************************
extern char *root;
extern char *curPath;
extern int searchFlag;
extern vector<string> dirList;
extern stack<string> backStack;
extern stack<string> forwardStack;
extern unsigned int rowSize, colSize;
extern unsigned int totalFiles;
extern int winTrack;

//**********************************************************************
// Global method declarations
//**********************************************************************
void openDirectory(const char *path);
void display(const char *dirName, const char *root);
int getFilePrintingCount();
void clearStack(stack<string> &s);
void navigate();

int isDirectory(char *newPath);
string getFileNameFromPath(string newDataw);

int startCommandMode();
void clearCommand();
string pathProcessing(string str);
void createNewFiles(vector<string> list);
void createSingleFile(char *path);
void makeDirectories(vector<string> list);
void removeDirectories(vector<string> list);
void removeSingleDirectory(char *path);
void removeFiles(vector<string> list);
void removeSingleFile(char *path);
void renameFiles(vector<string> list);
string gotoPath(vector<string> list);
void copyCommand(vector<string> list);
void copyDirectory(char *path, char *destination);
void copyFile(char *path, char *destination);
void moveCommand(vector<string> list);
void takeSnapshot(vector<string> list);
void takeDirSnapshot(char *path, char *dump);
int searchCommand(vector<string> list);
void searchAnything(char *path, string filename);
void showError(string str);