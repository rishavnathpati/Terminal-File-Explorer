//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Global declaration
//**********************************************************************
unsigned int rowsize,colsize;


//**********************************************************************
// Method returns count of maximun file to be printed on terminal
//**********************************************************************
int getFilePrintingcount()
{
	int lenRecord;
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	rowsize = win.ws_row-1;
	colsize = win.ws_col;
	if(totalFiles <= rowsize) {
		lenRecord = totalFiles;
	}
	else {
		lenRecord = rowsize;
	}
	return lenRecord;
}

/* Here is the explanation for the code above:
1. The function getFilePrintingcount() is used to determine the number of files to be printed on the screen. 
	It is based on the number of files present in the current directory and the size of the screen. 
	If the number of files is less than the number of rows in the screen, then all the files are printed.
2. If the number of files is greater than the number of rows in the screen, then only the number of files equal to the number of rows in the screen are printed.
3. The function ioctl() is used to get the size of the screen (number of rows and columns).
4. The function returns the number of files that are to be printed. */