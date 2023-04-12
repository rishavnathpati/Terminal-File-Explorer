//**********************************************************************
// Header file included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Declaration of global variables
//**********************************************************************
vector< string > dirList;
unsigned int totalFiles;
int wintrack;

//**********************************************************************
// Method returns total number of files + Directory withing given path
//**********************************************************************
int getDirectoryCount(const char * path)
{
	int count=0;
	dirList.clear();
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d) {

	    while ((dir = readdir(d)) != NULL) {
	      //printf("\n%-10s", dir->d_name);
	      if( (string(dir->d_name) == "..") && (strcmp(path,root) == 0))	
	      {   } 
	  	  else{
	  	  		dirList.push_back(string(dir->d_name));	
	  	  		count++;
	  	   }

	    }
	    closedir(d);
	}
	else{
	
	}
	return count;
}

/* Here is the explanation for the code above:
1. getDirectoryCount() takes the path of a directory as a parameter and returns the number of files in the directory.
2. The dirList vector contains the names of the files in the directory.
3. The root variable is the path of the directory that the user has chosen. It is set in the main() function.
4. The if statement in lines 18-21 checks if the current directory is the root directory. If it is, then the ".." directory is not included in the count or the dirList vector.
5. The else statement in line 22 adds the name of the file to the dirList vector and increments the count variable. */


//************************************************************************
// function that prints directory/file within given terminal size
//************************************************************************
void openDirectory(const char *path)
{
	dirList.clear();
	DIR *d;
	totalFiles = getDirectoryCount(path);
	int len = getFilePrintingcount();
	//sort(dirList.begin(),dirList.end());
	int itr=1;
	wintrack=0;
	struct dirent *dir;
	printf("\033[H\033[J");
	printf("%c[%d;%dH",27,1,1);
	//cout<<"\n*******total files  : "<<totalFiles<<endl;
	//cout<<"\n***********total files needs to be printed : "<<len<<endl;
	d = opendir(path);
	//printf("\n");
	if (d) {

	    while (((dir = readdir(d)) != NULL) && (itr<=len)){
	      //printf("\n%-10s", dir->d_name);
	      if( (string(dir->d_name) == "..") && (strcmp(path,root) == 0))	
	      {   } 
	  	  else{

	      		display((dir->d_name), path);
	      		itr++;
	  	   }

	    }

	    closedir(d);
	}
	else{
		//perror(d);
	}
	printf("%c[%d;%dH",27,0,1);
}

/* Here is the explanation for the code above:
1. The openDirectory() function takes the path of the directory as argument.
2. It first gets the number of files in the directory and stores it in totalFiles.
3. Then it gets the number of files that can be printed on the screen at once. This is stored in len.
4. Then the directory is opened and it's content is read using readdir() function. It is stored in dir.
5. The while loop is used to print the files. The condition checks if the directory has been fully read or not. It also checks if the number of files printed is less than the number of files that can be printed on the screen at once.
6. The first condition checks if the file is ".." and the directory is root. If it is, it does not print the file.
7. The second condition checks if the file is ".." and the directory is not root. If it is, it prints the file.
8. The display() function is called to print the files.
9. The closedir() function is used to close the directory.
10. The printf() function is used to set the cursor position to 0,0. This is done so that the cursor is at the top of the screen when the user goes to the previous directory. */


//************************************************************************
// function to display file/Directory's MetaDta
//************************************************************************
void display(const char *dirName, const char *root)
{
	string finalpath=string(root) + "/" +string(dirName);;
	char* path = new char[finalpath.length() + 1];
	strcpy(path, finalpath.c_str());
	//cout<<finalpath<<endl;
	//cout<<path<<endl;

	struct stat sb;
	if (stat(path,&sb) == -1) {
               perror("lstat");
    }
    
    printf(  (S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");

    //stat(filename, &info);  // Error check omitted
	struct passwd *pw = getpwuid(sb.st_uid);
	struct group  *gr = getgrgid(sb.st_gid);
	if(pw != 0)
		printf("\t%s", pw->pw_name);
	if(gr != 0)
		printf(" %s", gr->gr_name);

	printf("\t%10.2fK", ((double) sb.st_size)/1024);
	char *tt=(ctime(&sb.st_mtime));
	tt[strlen(tt)-1]='\0';
	printf("\t%s",tt);
	
	printf("\t%s\n",dirName);
}

/* Here is the explanation for the code above:
1. The first thing you need to do is to check the mode of the file, which is stored in the sb.st_mode. 
	You can use the S_ISDIR() macro to check if the file is a directory. 
	If it is a directory, you can use the opendir() function to open the directory and use the readdir() function to read the directory entries. 
	You can use the strcmp() function to check if the directory entry name is "." or "..", if so, ignore it. 
	Otherwise, you need to call the display() function recursively to display the information of the directory entry. 
	Remember to use the strcat() function to concatenate the directory path and directory entry name to form the path of the directory entry.
2. If the file is not a directory, you can use the printf() function to display the mode, size, modification time, and name of the file. */


