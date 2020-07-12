#include "FileStructureAnalyzer.h"
#include "Sector.h"
#include "SectorGroup.h"

typedef std::string::size_type StringPos;

void analyzeFile(const std::string& source, GameInstance& instance) {
	std::ifstream file(source);
	std::string line, sub;
	while (std::getline(file, line)) {
		StringPos begin = line.find_first_not_of(" \f\t\v");
		// Skip blank lines
		if (begin == std::string::npos) continue;

		// Skip commentary
		if (std::string("#;").find(line[begin]) != std::string::npos) continue;

		// Extract the key value
		StringPos type = line.find("Sector", begin);
		if (type == std::string::npos) continue;
		if (type != std::string::npos) {
			// TODO: if type is rect...
			StringPos next = 0;
			sub = line.substr(type + 7);
			std::vector<double> vals;
			while (true) {
				try {
					vals.push_back(std::stod(sub, &next));
					sub = sub.substr(next);
				} catch (...) {
					break;
				}
			}
			if (vals.size() >= 4) instance.sectors.addSector(Rect(vals[0], vals[1], vals[2], vals[3]));
			/*
			double vals[4];
			for (int i = 0; i < 4; i++) {
				StringPos star = line.find_first_of();
				StringPos end
			}*/
		}
		/*
		std::string::size_type end = line.find('=', begin);
		key = line.substr(begin, end - begin);
		// (No leading or trailing whitespace allowed)
		key.erase(key.find_last_not_of(" \f\t\v") + 1);


		// Extract the value (no leading or trailing whitespace allowed)
		begin = s.find_first_not_of(" \f\n\r\t\v", end + 1);
		end   = s.find_last_not_of(" \f\n\r\t\v") + 1;

		value = s.substr(begin, end - begin);
		// Insert the properly extracted (key, value) pair into the map
		*/
	}
	file.close();
}
