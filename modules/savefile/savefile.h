#pragma once

#include <map>
#include <string>
#include <string_view>
#include <utility>

class SaveFile {
public:
    std::map<std::string, std::string> data;

    SaveFile(const char* file);

    SaveFile(const SaveFile &) = delete;
    SaveFile& operator=(const SaveFile &) = delete;
    SaveFile(SaveFile &&) = delete;
    SaveFile& operator=(SaveFile &&) = delete;

    // Encrypts and saves `data` values into save `file`.
    // Returns `0` if operation was successful.
    bool save() const;

    // Decrypts `data` values on `file`.
    // Returns `0` if operation went succesfully.
    // Returns `1` if there was nothing to load.
    // Other return valeus indicate failure.
    bool load();

    std::string get(std::string key);
private:
    const char* file;

    // Transforms `data` into a `string`.
    std::string stringify() const;
};
