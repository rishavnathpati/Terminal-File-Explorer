#include "myheader.h"

/// @brief Recursively copies all files and directories to the destination path
/// @param sourcePath The source path
/// @param destinationPath The destination path
void copyDirectory(char *sourcePath, char *destinationPath)
{
	int status = mkdir(destinationPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == status)
	{
		showError("Error in creating the directory in path: " + string(sourcePath));
	}

	DIR *dir;
	struct dirent *entry;
	dir = opendir(sourcePath);
	if (dir)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if ((string(entry->d_name) == "..") || (string(entry->d_name) == "."))
			{
				continue;
			}
			else
			{
				string sourceFilePath = string(sourcePath) + "/" + string(entry->d_name);
				char *newSourcePath = new char[sourceFilePath.length() + 1];
				strcpy(newSourcePath, sourceFilePath.c_str());

				string destinationFilePath = string(destinationPath) + "/" + string(entry->d_name);
				char *newDestinationPath = new char[destinationFilePath.length() + 1];
				strcpy(newDestinationPath, destinationFilePath.c_str());

				struct stat sb;
				if (stat(newSourcePath, &sb) == -1)
				{
					perror("lstat");
				}
				else
				{
					if (S_ISDIR(sb.st_mode))
					{
						copyDirectory(newSourcePath, newDestinationPath);
					}
					else
					{
						copyFile(newSourcePath, newDestinationPath);
					}
				}
			}
		}
	}
	else
	{
		showError("No such directory found while copying with path: " + string(sourcePath));
	}
}

/// @brief Copies a file from the source path to the destination path
/// @param sourcePath The source path
/// @param destinationPath The destination path
void copyFile(char *sourcePath, char *destinationPath)
{
	char block[1024];
	int in, out;
	int nread;

	in = open(sourcePath, O_RDONLY);
	out = open(destinationPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	while ((nread = read(in, block, sizeof(block))) > 0)
		write(out, block, nread);

	struct stat sourceStat, destinationStat;
	if (stat(sourcePath, &sourceStat) != -1)
	{
	}
	if (stat(destinationPath, &destinationStat) != -1)
	{
	}

	int status1 = chown(destinationPath, sourceStat.st_uid, sourceStat.st_gid);
	if (status1 != 0)
		showError("Error in setting ownership of file using chown");

	int status2 = chmod(destinationPath, sourceStat.st_mode);
	if (status2 != 0)
		showError("Error in setting permission of file using chmod");
}

/// @brief Copies all files and directories to the destination path
/// @param list The list of files/directories to copy
void copyCommand(vector<string> list)
{
	unsigned int len = list.size();
	if (len < 3)
	{
		showError("Less number of arguments in copy command!");
	}
	else
	{
		for (unsigned int i = 1; i < len - 1; i++)
		{
			string sourcePath = list[i];
			string fileName = getFileNameFromPath(sourcePath);
			string destinationPath = list[len - 1] + "/" + fileName;
			char *destination = new char[destinationPath.length() + 1];
			strcpy(destination, destinationPath.c_str());

			char *source = new char[sourcePath.length() + 1];
			strcpy(source, sourcePath.c_str());

			if (isDirectory(source))
			{
				copyDirectory(source, destination);
			}
			else
			{
				copyFile(source, destination);
			}
		}
	}
}
