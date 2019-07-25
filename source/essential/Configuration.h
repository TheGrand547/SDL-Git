#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<SDL2/SDL.h>
#include<map>


/* Modified -lightly- from http://www.cplusplus.com/forum/general/21115/ */
class Configuration {
	private:
		std::map<std::string, std::string> configMap;
	public:
		Configuration() {
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
				key.erase( key.find_last_not_of(" \f\t\v") + 1);

				// No blank keys allowed
				if (key.empty()) continue;

				// Extract the value (no leading or trailing whitespace allowed)
				begin = s.find_first_not_of(" \f\n\r\t\v", end + 1);
				end   = s.find_last_not_of(" \f\n\r\t\v") + 1;

				value = s.substr(begin, end - begin);
				// Insert the properly extracted (key, value) pair into the map
				configMap[key] = value;
			}
			file.close();
		}
		
		int operator[](std::string key) {
			return SDL_GetScancodeFromName(configMap[key].c_str());
		}

		void output() {
			for (std::map<std::string, std::string>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
				std::cout << iter->first << " = " << iter->second << std::endl;
			}
		}
		
		void reload() {
			*this = Configuration();
		}
};
