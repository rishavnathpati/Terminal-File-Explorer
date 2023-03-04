#include "myheader.h"

/*
1. DIR is a pointer to the directory stream. The type DIR is declared in dirent.h.
2. struct dirent is a structure for directory entry. The type struct dirent is declared in dirent.h.
3. The variable d is a pointer to the directory stream.
4. The variable dir is a pointer to the directory entry.

1. The openDirectory() function accepts the path of the directory as the argument.
	The path of the directory is passed as a character array from the main function.
2. The opendir() function opens the directory and if it's successful it returns a pointer of type DIR which is assigned to d.
	Else it prints out an error message.
3. The while loop checks if the directory is empty or not.
	If it's not empty, it reads the directory and stores it in a pointer of type struct dirent which is assigned to dir.
4. The display() function is called with the name of the file and the path of the directory as the argument.
5. The closedir() function closes the directory.
*/

/// @brief Function to open Directory Content
/// @param path Path of the directory
void openDirectory(const char *path)
{
	DIR *d;
	struct dirent *dir;
	system("clear");
	d = opendir(path);
	if (d)
	{

		while ((dir = readdir(d)) != NULL)
		{
			display((dir->d_name), path);
		}

		closedir(d);
	}
	else
	{
		cout << "No such Directiory Exist !!!" << endl;
	}
}

/*
1. The function takes two parameters.
	The first parameter is the name of the directory that is going to be displayed.
	The second parameter is the root directory of the file system.
2. We declare a string object with the name finalpath.
	The value of finalpath is the concatenation of the root directory and the name of the directory that is going to be displayed.
3. We declare a character pointer with the name path. We allocate memory for the path variable using the new operator.
	The size of the memory allocated is the length of the string stored in the finalpath variable plus one.
	The plus one is necessary because the character array must be null-terminated.
4. We use the strcpy function to copy the contents of the string stored in the finalpath variable to the character array stored in the path variable.
5. We declare a stat structure with the name sb. We use the stat function to retrieve information about the file system object that is specified by the path argument.
	The information is stored in the sb variable.
6. If the stat function returns -1, an error occurred.
7. We use the printf function to display the name of the directory that is going to be displayed.
8. We use the printf function to display the permission bits of the file system object.
	The permission bits are stored in the st_mode member of the stat structure.
	We use the bitwise AND operator & to check whether the permission bits are set or not.
	If the permission bits are set, we display the corresponding character.
	If the permission bits are not set, we display a hyphen (-) character.
9. We use the printf function to display the size of the file system object.
	The size of the file system object is stored in the st_size member of the stat structure.
10. We use the printf function to display the last modification time of the file system object.
	The last modification time of the file system object is stored in the st_mtime member of the stat structure.
	We use the ctime function to convert the modification time to a human-readable format.
*/

/// @brief Function to display file/Directory's MetaData
/// @param dirName Name of the file/directory
/// @param root Path of the directory
void display(const char *dirName, const char *root)
{
	string finalpath = string(root) + "/" + string(dirName);
	char *path = new char[finalpath.length() + 1];
	strcpy(path, finalpath.c_str());

	struct stat sb;
	if (stat(path, &sb) == -1)
	{
		perror("lstat");
	}

	printf("%-20s", dirName);
	printf("\t");
	printf((sb.st_mode & S_IRUSR) ? "r" : "-");
	printf((sb.st_mode & S_IWUSR) ? "w" : "-");
	printf((sb.st_mode & S_IXUSR) ? "x" : "-");
	printf((sb.st_mode & S_IRGRP) ? "r" : "-");
	printf((sb.st_mode & S_IWGRP) ? "w" : "-");
	printf((sb.st_mode & S_IXGRP) ? "x" : "-");
	printf((sb.st_mode & S_IROTH) ? "r" : "-");
	printf((sb.st_mode & S_IWOTH) ? "w" : "-");
	printf((sb.st_mode & S_IXOTH) ? "x" : "-");
	printf((sb.st_mode & S_ISUID) ? "s" : "-");
	printf((sb.st_mode & S_ISGID) ? "s" : "-");
	printf((sb.st_mode & S_ISVTX) ? "t" : "-");
	printf("\t%10lld bytes", (long long)sb.st_size);
	printf("\t%s ", ctime(&sb.st_mtime));
}

/*

The following macros are used to check the permissions of the file/directory:

S_IRUSR: Read permission, owner
S_IWUSR: Write permission, owner
S_IXUSR: Execute/search permission, owner
S_IRGRP: Read permission, group
S_IWGRP: Write permission, group
S_IXGRP: Execute/search permission, group
S_IROTH: Read permission, others
S_IWOTH: Write permission, others
S_IXOTH: Execute/search permission, others
S_ISUID: Set-user-ID on execution
S_ISGID: Set-group-ID on execution
S_ISVTX: On directories, restricted deletion flag
*/
