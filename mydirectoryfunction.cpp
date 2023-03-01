#include "myheader.h"

//************************************************************************
// function to open Directory Content
//************************************************************************
void openDirectory(const char *dirName)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dirName);
	if (d) {

	    while ((dir = readdir(d)) != NULL) {
	      //printf("\n%-10s", dir->d_name);
	      display(dir->d_name);
	    }

	    closedir(d);
	}
}


//************************************************************************
// function to display file/Directory's MetaDta
//************************************************************************
void display(const char *dirName)
{
	struct stat sb;
	stat(dirName,&sb);
	 	
		printf("\n");
		printf("%-20s",dirName);
		printf("\t");
		printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
	    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    	printf("\t%10lld bytes", (long long) sb.st_size);
    	printf("\t%s ",ctime(&sb.st_mtime));	
}

/* Here is the explanation for the code above:
1. The stat structure is defined in sys/stat.h. It contains the following members:

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

2. The stat() function is defined in sys/stat.h. It returns 0 on success, and -1 on error. It takes the following arguments:

int stat(const char *path, struct stat *buf);

path: The path of the file/directory whose metadata is to be displayed.

buf: A pointer to a stat structure which will be filled by stat().

3. The following macros are used to check the permissions of the file/directory:

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

The following code snippet shows the use of the stat() function to display the metadata of a file:

#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat sb;

    stat("sample.txt", &sb);

    printf("File Size: \t\t%lld bytes

", (long long) sb.st_size);
    printf("Number of Links: \t%ld

", (long long) sb.st_nlink);
    printf("File inode: \t\t%ld

", (long long) sb.st_ino);

    return 0;
}

The output of the above code is:

File Size: 		12 bytes
Number of Links: 	1
File inode: 		2621440

The following code snippet shows the use of the stat() function to display the metadata of a directory:

#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat sb;

    stat(".", &sb);

    printf("Total size: \t\t%lld bytes

", (long long) sb.st_size);
    printf("Number of Links: \t%ld

", (long long) sb.st_nlink);
    printf("File inode: \t\t%ld

", (long long) sb.st_ino);

    return 0;
}

The output of the above code is:

Total size: 		4096 bytes
Number of Links: 	3
File inode: 		2621440 */