#include "myheader.h"

/// @brief Removes a single file from the given path
/// @param path The path of the file to remove
void removeSingleFile(char *path)
{
	int status = remove(path);
	if (status != 0)
	{
		showError("Error in removing the file with path: " + string(path));
	}
}

/// @brief Removes multiple files specified by the user in the argument
/// @param list The list of files to remove
void removeFiles(vector<string> list)
{
	if (list.size() < 2)
	{
		showError("Less number of arguments in delete_file command");
	}

	for (unsigned int i = 1; i < list.size(); i++)
	{
		char *path = new char[list[i].length() + 1];
		strcpy(path, list[i].c_str());
		removeSingleFile(path);
	}
}

/// @brief Creates a single file at the given path
/// @param path The path of the file to create
void createSingleFile(char *path)
{
	int status = open(path, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (status == -1)
	{
		showError("Error in creating new file with path: " + string(path));
	}
}

/// @brief Creates multiple files as specified by the user
/// @param list The list of files to create
void createNewFiles(vector<string> list)
{
	if (list.size() < 3)
	{
		showError("Less number of arguments in renaming!");
		return;
	}

	unsigned int len = list.size();
	string destinationPath = pathProcessing(list[len - 1]);

	for (unsigned int i = 1; i < len - 1; i++)
	{
		string fileName = destinationPath + "/" + list[i];
		char *path = new char[fileName.length() + 1];
		strcpy(path, fileName.c_str());
		createSingleFile(path);
	}
}

/// @brief Renames a file or directory
/// @param list The list containing the initial name and the final name
void renameFiles(vector<string> list)
{
	if (list.size() != 3)
	{
		showError("Invalid arguments in renaming!");
	}
	else
	{
		string initialName = list[1];
		string finalName = list[2];
		rename(initialName.c_str(), finalName.c_str());
	}
}
