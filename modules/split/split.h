#pragma once

#include <string>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string &str, const char &separator);
std::pair<std::string, std::string> split_once(const std::string &str, const char &separator);
