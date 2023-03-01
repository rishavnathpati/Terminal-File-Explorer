#include "myheader.h"

using namespace std;

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

	// printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	// if (S_ISREG(mode))
	//        c = '-';
	//    else if (S_ISDIR(mode))
	//        c = 'd';
	//    else if (S_ISBLK(mode))
	//        c = 'b';
	//    else if (S_ISCHR(mode))
	//        c = 'c';
}

int main()
{

	openDirectory(".");
	checkFile();
	// chmod("Assi-1.cpp", S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
	// int mkdir(const char *path, mode_t mode)                      page No: 121
	// int rmdir(const char *path);
	return 0;
}

/* Here is the explanation for the code above:
1. stat() is used to get the status of a file. This function returns 0 on success, and -1 on error.
2. st_mode contains the file type and the file permission bits. These are defined in the header file sys/stat.h.
You can use the macros defined in the header file like S_ISDIR(), S_ISREG() etc. to determine the file type.
3. S_IFMT is a bitmask that extracts the file type bits from the mode.
4. S_IFDIR is the bit mask for a directory.
5. S_IFREG is the bit mask for a regular file.
6. S_IFMT is the bit mask for the file type bit fields.
7. S_ISDIR() is a macro that returns true if the mode is that of a directory.
8. S_ISREG() is a macro that returns true if the mode is that of a regular file. */
