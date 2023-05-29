#include "myheader.h"

vector<string> tokens;

/**
 * @brief Handles absolute and relative paths in cmd mode
 * @param str The input path
 * @return The absolute path
 */
string pathProcessing(string str)
{
    char firstChar = str[0];
    string absolutePath = "";
    string basePath = string(root);
    if (firstChar == '/')
    {
        absolutePath = basePath + str;
    }
    else if (firstChar == '~')
    {
        absolutePath = basePath + str.substr(1, str.length());
    }
    else if (firstChar == '.')
    {
        absolutePath = string(curPath) + str.substr(1, str.length());
    }
    else
    {
        absolutePath = string(curPath) + "/" + str;
    }

    return absolutePath;
}

/**
 * @brief Splits the input string into tokens separated by space and stores them in the 'tokens' vector
 * @param str The input string
 */
void inputProcessing(string str)
{
    unsigned int i = 0;
    tokens.clear();
    int flag = 0;
    while (i < str.length())
    {
        string sub = "";
        while (str[i] != ' ' && i < str.length())
        {
            if (str[i] == '\\')
            {
                sub += str[i + 1];
                i = i + 2;
            }
            else
            {
                sub += str[i];
                i++;
            }
        }
        if (flag == 1)
        {
            string absolutePath = pathProcessing(sub);
            tokens.push_back(absolutePath);
        }
        else
        {
            tokens.push_back(sub);
            if (tokens[0] != "create_file" && tokens[0] != "create_dir" && tokens[0] != "search")
            {
                flag = 1;
            }
        }
        i++;
    }
}

/**
 * @brief Clears the command line area after each command runs
 */
void clearCommand()
{
    int lastLine = rowSize + 1;
    printf("%c[%d;%dH", 27, lastLine, 1);
    printf("%c[2K", 27);
    cout << ":";
}

/**
 * @brief Starts the command mode, takes input from the user, and processes it
 * @return 0 if the command mode exited normally, otherwise a non-zero value
 */
int startCommandMode()
{
    char ch;
    do
    {
        string input;
        while (((ch = getchar()) != 10) && ch != 27)
        {
            if (ch == 127)
            {
                clearCommand();
                if (input.length() <= 1)
                {
                    input = "";
                }
                else
                {
                    input = input.substr(0, input.length() - 1);
                }
                cout << input;
            }
            else
            {
                input = input + ch;
                cout << ch;
            }
        }
        inputProcessing(input);
        if (ch == 10)
        {
            string command = tokens[0];
            if (command == "copy")
            {
                // cout<<"Copy command  : "<<endl;
                copyCommand(tokens);
                clearCommand();
            }
            else if (command == "move")
            {
                // cout<<"Move command  : "<<endl;
                moveCommand(tokens);
                clearCommand();
            }
            else if (command == "rename")
            {
                // cout<<"rename command  : "<<endl;
                renameFiles(tokens);
                clearCommand();
            }
            else if (command == "create_file")
            {
                // cout<<"create_file command  : "<<endl;
                createNewFiles(tokens);
                clearCommand();
            }
            else if (command == "create_dir")
            {
                // cout<<"create_dir command  : "<<endl;
                makeDirectories(tokens);
                clearCommand();
            }
            else if (command == "delete_file")
            {
                // cout<<"delete_file command  : "<<endl;
                removeFiles(tokens);
                clearCommand();
            }
            else if (command == "delete_dir")
            {
                // cout<<"delete_dir command  : "<<endl;
                removeDirectories(tokens);
                clearCommand();
            }
            else if (command == "goto")
            {
                // cout<<"goto command  : "<<endl;
                string gotoPath = gotoPath(tokens);
                char *path = new char[gotoPath.length() + 1];
                strcpy(path, gotoPath.c_str());
                back_stack.push(string(curPath));
                clearStack(forw_stack);
                curPath = path;
                // cout<<"\ngoto path : "<<path<<endl;
                return 1;
            }
            else if (command == "search")
            {
                // cout<<"search command  : "<<endl;
                int status = searchCommand(tokens);
                if (status != 0)
                    return 2;
                clearCommand();
            }
            else if (command == "snapshot")
            {
                // cout<<"snapshot command  : "<<endl;
                takeSnapshot(tokens);
                clearCommand();
            }
            else
            {
                showError("Invalid Command");
                clearCommand();
            }
        }

    } while (ch != 27);

    return 0;
}
