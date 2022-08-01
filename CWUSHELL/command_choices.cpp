#include "command_choices.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>

void cmd_change_prompt(std::vector<std::string> &args, std::string &curPrompt)
{
    using namespace std;
    if (args.size() < 2)
    {
        std::cout << "Please enter the new Prompt" << std::endl;
    }
    else if (args.size() > 2)
    {
        std::cout << "too many arguments" << std::endl;
    }
    else if (args[1] == "-help")
    {
        cout << "change_prompt -'enter what you want to name your shell here'" << endl;
    }
    else
    {
        curPrompt = args[1];
    }
}

void cmd_distro(std::vector<std::string> &inputSplit)
{
    using namespace std;

    if (inputSplit.size() < 2)
    {
        cout << "Please enter the new Prompt" << endl;
    }
    else if (inputSplit.size() > 2)
    {
        cout << "too many arguments" << endl;
    }
    else if (inputSplit[1] == "-v")
    {
        string line;
        ifstream myfile("/etc/os-release");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                if (line.find("VERSION_ID") != std::string::npos)
                {
                    line.replace(0, 12, "");
                    line.replace(line.length() - 1, 1, "");
                    cout << line << '\n';
                }
            }

            myfile.close();
        }
        else
            cout << "Unable to open file";
    }
    else if (inputSplit[1] == "-n")
    {
        string line;
        ifstream myfile("/etc/os-release");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                if (line.find("NAME") != std::string::npos)
                {
                    line.replace(0, 6, "");
                    line.replace(line.length() - 1, 1, "");
                    cout << line << '\n';
                    break;
                }
            }

            myfile.close();
        }

        else
            cout << "Unable to open file";
    }
    else if (inputSplit[1] == "-c")
    {
        string line;
        ifstream myfile("/etc/os-release");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                if (line.find("VERSION_CODENAME") != std::string::npos)
                {
                    line.replace(0, 17, "");
                    cout << line << '\n';
                    break;
                }
            }

            myfile.close();
        }

        else
            cout << "Unable to open file";
    }
    else if (inputSplit[1] == "-help")
    {
        cout << "-v print the distro's version" << endl;
        cout << "-n will print distro's name" << endl;
        cout << "-c will print distro's codename" << endl;
    }
    else
    {
        cout << "type distro -help for valid commands" << endl;
    }
}
void cmd_info(std::vector<std::string> &inputSplit)
{
    using namespace std;

    if (inputSplit.size() < 2)
    {
        cout << "Please enter the new Prompt" << endl;
    }
    else if (inputSplit.size() > 2)
    {
        cout << "too many arguments" << endl;
    }
    else if (inputSplit[1] == "-s")
    {
        cout << "Current memory page size: " << getpagesize() / 1024 << " KB" << endl;
    }
    else if (inputSplit[1] == "-n")
    {

        string line;
        ifstream myfile("/proc/meminfo");

        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                if (line.find("MemAvailable") != std::string::npos)
                {
                    line.replace(0, 17, "");
                    line.replace(8, 3, "");
                    int memory = std::stoi(line);
                    int pagesize = getpagesize() / 1024;
                    cout << memory / pagesize << " pages" << endl;

                    break;
                }
            }

            myfile.close();
        }

        else
            cout << "Unable to open file";
    }
    else if (inputSplit[1] == "-p")
    {
        string line;
        ifstream myfile("/proc/cpuinfo");
        int counter = 0;
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                if (line.find("processor") != std::string::npos)
                {
                    counter++;
                }
            }
            cout << "Number of Processor that I have " << counter << endl;

            myfile.close();
        }

        else
            cout << "Unable to open file";
    }
    else if (inputSplit[1] == "-help")
    {
        cout << "-s will print current memory page size" << endl;
        cout << "-n will print the current available page numbers " << endl;
        cout << "-c will print number of available processors" << endl;
    }
    else
    {
        cout << "type info -help for valid commands" << endl;
    }
}

void external_command(std::vector<std::string> &inputSplit, std::string input,int &ReturnCode)
{
    using namespace std;
    //system(input.c_str());
    pid_t pid;
    int status;
    pid = fork();

    if (pid == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // In child process

        char **args = new char *[inputSplit.size() + 1];
        args[inputSplit.size()] = NULL;

        for (int i = 0; i < inputSplit.size(); i++)
        {
            args[i] = const_cast<char *>(inputSplit[i].c_str());
        }

        execvp(args[0], args);

        delete[] args;

        exit(127);
    }
    else
    {
        if (waitpid(pid, &status, 0) > 0)
        {
            ReturnCode = WEXITSTATUS(status);
            if (WIFEXITED(status) && !WEXITSTATUS(status))
                // ReturnCode is 0
                cout << ("program execution successful") << endl;

            else if (WIFEXITED(status) && WEXITSTATUS(status))
            {
                // ReturnCode is not 0
                if (WEXITSTATUS(status) == 127)
                {
                    // Returncode is 127
                    // execv failed
                    cout << "Program does not exist type help command for help" << endl;
                }
                else
                    cout << "program terminated normally,"
                            " but returned a non-zero status"
                         << endl;
            }
            else
                cout << "program didn't terminate normally" << endl;
        }
        else
        {
            // waitpid() failed
            cout << "waitpid() failed" << endl;
        }
    }
}