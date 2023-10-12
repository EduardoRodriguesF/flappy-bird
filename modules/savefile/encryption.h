#pragma once

#include <string>

void encrypt(std::string_view key, std::string &data);
void decrypt(std::string_view key, std::string &data);
