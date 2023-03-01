#include "myheader.h"

char *root;

/* Here is the explanation for the code below:
1. stat() function returns the information about the file in structure sb.
2. (sb.st_mode & S_IFMT) is a mask which extracts file type information.
3. (sb.st_mode & S_IFMT) == S_IFDIR is a comparison which checks whether the file is a directory or not.
4. (sb.st_mode & S_IFMT) == S_IFREG is a comparison which checks whether the file is a regular file or not. */

/// @brief Function to open Directory Content
void checkFile()
{
	struct stat sb;
	stat("FileName", &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		cout << "DIR" << endl;
	}
	else if ((sb.st_mode & S_IFMT) == S_IFREG)
	{
		cout << "FILE" << endl;
	}
	else
	{
		cout << "unknown?" << endl;
	}
}

/*Function to open Directory Content
1. The main function takes two arguments.
	The first argument is the directory name which is to be searched for the files.
	And the second argument is the pattern to be searched.
2. The root is the directory path which is to be searched.
	If the first argument is not passed to the program, then the current directory is taken as the root directory.
3. The openDirectory function takes a directory name as the argument and opens it.
	It then reads the directory and checks if it is a file or a directory.
	If it is a file then it checks if the file name matches the pattern.
	If it is a directory then it calls the openDirectory function recursively for the sub-directory.
4. The openDirectory function is called recursively until all the sub-directories are searched for the given pattern.
5. The files which match the given pattern are printed on the screen. */

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		openDirectory(".");
	}
	else if (argc == 2)
	{
		root = argv[1];
		openDirectory(argv[1]);
	}
	else
	{
		cout << "Invalid Argument !!!" << endl;
	}
	return 0;
}

/* The stat structure is defined in sys/stat.h. It contains the following members:

struct stat {
	dev_t     st_dev;         ID of device containing file
	ino_t     st_ino;         inode number
	mode_t    st_mode;        protection
	nlink_t   st_nlink;       number of hard links
	uid_t     st_uid;         user ID of owner
	gid_t     st_gid;         group ID of owner
	dev_t     st_rdev;        device ID (if special file)
	off_t     st_size;        total size, in bytes
	blksize_t st_blksize;     blocksize for filesystem I/O
	blkcnt_t  st_blocks;      number of 512B blocks allocated

	time_t    st_atime;       time of last access
	time_t    st_mtime;       time of last modification
	time_t    st_ctime;       time of last status change
};

2. The stat() function returns 0 on success, and -1 on error. It takes the following arguments:

int stat(const char *path, struct stat *buf);

path: The path of the file/directory whose metadata is to be displayed.

buf: A pointer to a stat structure which will be filled by stat().*/