#include "FileStructureAnalyzer.h"
#include "Sector.h"
#include "SectorGroup.h"
#include "BigWall.h"
#include "../essential/log.h"
#include<map>

typedef std::string::size_type StringPos;
typedef std::map<std::string, std::string> StringMap;

Rect rectFromString(const std::string& string) {
	try {
		StringPos next = 0;
		std::string sub = string.substr(string.find("Rect") + 5);
		std::vector<double> vals;
		while (next != std::string::npos) {
			vals.push_back(std::stod(sub, &next));
			sub = sub.substr(next + 1);
			auto pp = sub.find_last_of(" \f\t\v");
			if (pp == std::string::npos) {
				vals.push_back(std::stod(sub));
				break;
			}
		}
		if (vals.size() >= 8) return Rect(Line(Point(vals[0], vals[1]), Point(vals[2], vals[3])), Line(Point(vals[4], vals[5]), Point(vals[6], vals[7])));
		if (vals.size() >= 4) return Rect(vals[0], vals[1], vals[2], vals[3]);
	} catch (...) {
		return Rect();	
	}
	return Rect();
}

void analyzeFile(const std::string& source, GameInstance& instance) {
	std::ifstream file(source);
	std::string line, sub;
	int lineNumber = 0;
	
	StringMap things;
	
	while (std::getline(file, line)) {
		lineNumber++;
		StringPos begin = line.find_first_not_of(" \f\t\v");
		// Skip blank lines
		if (begin == std::string::npos) continue;

		// Skip commentary
		if (std::string("#;").find(line[begin]) != std::string::npos) continue;

		// Extract the key value
		StringPos type, next;
		// Sloppy but gets the job done
		if ((type = line.find("Sector", begin)) != std::string::npos) { // Sector
			if ((next = line.find("Rect", type + 6)) != std::string::npos) {
				Rect rect(rectFromString(line));
				if (rect.isReal()) instance.sectors.addSector(rect);
				else LOG("Improperly formatted 'Rect' on line %i of %s.", lineNumber, source.c_str());
				continue;
			}
		} else if ((type = line.find("BasicWall", begin)) != std::string::npos) { // Big Wall
			Rect rect(rectFromString(line));
			if (rect.isReal()) instance.createThing<BigWall>(rect);
			else LOG("Improperly formatted 'Rect' on line %i of %s.", lineNumber, source.c_str());
			continue;
		} else if ((type = line.find("Thing", begin)) != std::string::npos) { // Definition of a thing
			std::cout << "We makin a thing" << std::endl;
		}
		LOG("Line %i of %s is improperly formatted for analysis.", lineNumber, source.c_str());	
	}
	file.close();
}

void analyzeStructure(const std::string& source, GameInstance& instance, StringMap& map) {
	std::cout << source << "->" << &instance << std::endl;
}
