//Justin Phan
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "tools.h"
#include "command_choices.h"


int ReturnCode = 0;

int main()
{
    using namespace std;

    string Prompt = "cwushell";

    bool running = true;

    while (running)
    {
        cout << Prompt << ": ";
        string input = "";
        getline(cin, input);
        trim(input);
        if (input.empty())
        {
            cout << "Invalid command (Empty)." << endl;
            continue;
        }

        vector<string> inputSplit = split(input, " ");

        // Make index 0 lower case
        transform(inputSplit[0].begin(), inputSplit[0].end(), inputSplit[0].begin(), ::tolower);

        if (inputSplit[0] == "exit")
        {
            running = false;
            if (inputSplit.size()>1)
            {
                try 
                {
                    ReturnCode = stoi(inputSplit[1]);
                }
                catch(const std::invalid_argument& ia) 
                {
                    cout<< "invalid error code"<< endl;
                    running = true;
                }
            }
            
        }
        else if (inputSplit[0] == "hello")
        {
            if (inputSplit.size() > 1)
            {
                cout << "Hello " << inputSplit[1] << "!" << endl;
            }
            else
            {
                cout << "Hello there!" << endl;
            }
        }
        else if (inputSplit[0] =="help")
        {
            cout<< "change_prompt -- will change the current shell prompt to the new prompt name" << endl;
            cout<< "distro -switch -- will print on the screen different cpu related information based on the switch"<< endl;
            cout<< "info -switch -- will print on the screen different memory related information based on the switch"<< endl;
            cout<< "exit --terminate the shell "<<endl;
        }
        else if (inputSplit[0] == "change_prompt")
        {
            cmd_change_prompt(inputSplit, Prompt);
        }
        else if (inputSplit[0] == "distro")
        {
            cmd_distro(inputSplit);
        }
        else if (inputSplit[0] == "info")
        {
            cmd_info(inputSplit);
        }
        else
        {
            external_command(inputSplit, input, ReturnCode);
        }

    }
    return ReturnCode;
}


/*
 go to file /etc/os-release
 use FILE *fp  fopen and try to get some key words out of the file
*/