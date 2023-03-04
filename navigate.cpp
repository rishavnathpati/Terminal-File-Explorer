
#include "myheader.h"
int xcor = 1, ycor = 1;
#define esc 27 // The esc variable is a macro for the ASCII escape character 27 (the ESC key).
#define cls printf("%c[2J", esc) // The cls macro uses the escape character to clear the terminal screen.
#define pos() printf("%c[%d;%dH", esc, xcor, ycor) // The pos() macro uses the escape character to position the cursor at the given coordinates.

void navigate()
{
    xcor = 1, ycor = 1;
    struct termios initialrsettings, newrsettings;
    char ch;

    tcgetattr(fileno(stdin), &initialrsettings);

    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ICANON;
    newrsettings.c_lflag &= ~ECHO;

    if (tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0)
    {
        fprintf(stderr, "Could not set attributes\n");
    }
    else
    {
        while (1)
        {
            ch = cin.get();

            if (ch == 27)
            {
                ch = cin.get();
                ch = cin.get();
                if (ch == 'A')
                {
                    if (xcor > 1)
                        --xcor;
                    pos();
                }
                else if (ch == 'B')
                {
                    ++xcor;
                    pos();
                }
            }
        }
    }

    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
}