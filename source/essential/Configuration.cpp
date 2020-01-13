#include "Configuration.h"

Configuration::Configuration() {
	std::ifstream file("config.cfg");
	std::string s, key, value;
	while (std::getline(file, s)) {
		std::string::size_type begin = s.find_first_not_of( " \f\t\v" );
		// Skip blank lines
		if (begin == std::string::npos) continue;

		// Skip commentary
		if (std::string("#;").find(s[begin]) != std::string::npos) continue;

		// Extract the key value
		std::string::size_type end = s.find('=', begin);
		key = s.substr(begin, end - begin);

		// (No leading or trailing whitespace allowed)
		key.erase(key.find_last_not_of(" \f\t\v") + 1);

		// No blank keys allowed
		if (key.empty()) continue;

		// Extract the value (no leading or trailing whitespace allowed)
		begin = s.find_first_not_of(" \f\n\r\t\v", end + 1);
		end   = s.find_last_not_of(" \f\n\r\t\v") + 1;

		value = s.substr(begin, end - begin);
		// Insert the properly extracted (key, value) pair into the map
		this->keyMap[key] = value;
	}
	file.close();
	if (this->keyMap["resolution"] != "") {
		std::string::size_type fo = 0;
		this->configMap["Width"]= stoi(this->keyMap["resolution"], &fo);
		this->configMap["Height"] = stoi(this->keyMap["resolution"].substr(fo + 1));
	}
}

int Configuration::operator[](std::string key) const {
	int value = SDL_GetScancodeFromName(this->keyMap[key].c_str());
	if (value == SDL_SCANCODE_UNKNOWN) {
		value = stoi(this->configMap[key]);
	}
	return value;
}

void Configuration::output(std::ostream& output) const {
	for (std::map<std::string, std::string>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
		output << iter->first << " = " << iter->second << std::endl;
	}
}

void Configuration::reload() {
	*this = Configuration();
}
