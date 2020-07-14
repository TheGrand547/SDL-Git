#include "FileStructureAnalyzer.h"
#include "Sector.h"
#include "SectorGroup.h"
#include "../essential/log.h"

typedef std::string::size_type StringPos;

Rect rectFromString(const std::string& string) {
	try {
		StringPos next;
		std::string sub = string.substr(string.find("Rect") + 5);
		double vals[4];
		for (int i = 0; i < 4; i++) {
			vals[i] = std::stod(sub, &next);
			sub = sub.substr(next);
		}
		return Rect(vals[0], vals[1], vals[2], vals[3]);
	} catch (...) {
		return Rect();	
	}
}

void analyzeFile(const std::string& source, GameInstance& instance) {
	std::ifstream file(source);
	std::string line, sub;
	int lineNumber = 0;
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
		}
		LOG("Line %i of %s is improperly formatted for analysis.", lineNumber, source.c_str());	
	}
	file.close();
}
