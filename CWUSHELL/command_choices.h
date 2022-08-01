#ifndef COMMAND_CHOICES_H
#define COMMAND_CHOICES_H

#include <string>
#include <vector>

void cmd_change_prompt(std::vector<std::string> &args, std::string &prompt);
void cmd_distro(std::vector<std::string> &args);
void cmd_info(std::vector<std::string> &args);
void external_command(std::vector<std::string> &args, std::string, int &);

#endif