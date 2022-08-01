#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include <regex>

std::vector<std::string> split(const std::string &input, const std::string &regex);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

#endif