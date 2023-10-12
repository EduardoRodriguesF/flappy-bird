#include "split.h"

std::vector<std::string> split(const std::string &str, const char &separator) {
	std::vector<std::string> result;
	std::string entry;

	for (int i = 0; i < str.size(); i++) {
		char c = str[i];

		if (c == separator) {
			result.push_back(entry);
			entry = "";
			continue;
		}

		entry += c;
	}

	if (!entry.empty()) {
		result.push_back(entry);
	}

	return result;
}

std::pair<std::string, std::string> split_once(const std::string &str,
                                               const char &separator) {
    std::pair<std::string, std::string> result;

    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator) {
            result.first = str.substr(0, i);
            result.second = str.substr(i + 1);

            return result;
        }
    }

    // Did not find separator
    result.first = str;

    return result;
}

