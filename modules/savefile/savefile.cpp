#include "savefile.h"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "savefile/encryption.h"
#include "split/split.h"

SaveFile::SaveFile(const char* encryption_key, const char* file) : encryption_key(encryption_key), file(file) {
    data = std::map<std::string, std::string>();
}

bool SaveFile::load() {
    if (!std::filesystem::exists(file)) {
        return 1;
    }

    std::ifstream stream(file);
    if (!stream.is_open()) {
        return 2;
    }

    std::string txt;
    std::string line;
    while (std::getline(stream, line)) {
        txt.append(line);
    }

    decrypt(this->encryption_key, txt);

    std::vector<std::string> entries = split(txt, ';');
    for (const auto &entry : entries) {
        auto pair = split_once(entry, '=');
        data.insert(pair);
    }

    stream.close();
    return 0;
}

bool SaveFile::save() const {
    std::string values = stringify();
    std::ofstream ofs(file);

    encrypt(this->encryption_key, values);

    ofs << values;
    ofs.close();

    return 0;
}

std::string SaveFile::get(std::string key) {
    std::map<std::string, std::string>::iterator it = data.find(key);

    if (it == data.end()) {
        return "";
    }

    return it->second;
}

std::string SaveFile::stringify() const {
    std::string result {};

    for (const auto &[key, value] : this->data) {
        result.append(std::string(key) + '=' + std::string(value) + ';');
    }

    return result;
}
