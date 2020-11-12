#include "FileStructureAnalyzer.h"
#include "Sector.h"
#include "SectorGroup.h"
#include "BigWall.h"
#include "../essential/log.h"
#include <map>
#include <array>
#include <boost/spirit/include/qi.hpp>

typedef std::string::size_type StringPos;
typedef std::map<std::string, std::string> StringMap;

BOOST_FUSION_ADAPT_STRUCT(
    Point,
    (double, x)
	(double, y)
)

template<typename Iterator> struct PointParser : boost::spirit::qi::grammar<Iterator, Point(), boost::spirit::qi::ascii::space_type> {
	boost::spirit::qi::rule<Iterator, Point(), boost::spirit::qi::ascii::space_type> start;
	PointParser() : PointParser::base_type(this->start) {
		this->start %= boost::spirit::qi::double_ >> boost::spirit::qi::double_ | 
						boost::spirit::qi::double_ >>  ',' >> boost::spirit::qi::double_ |
						'(' >> this->start >> ')';
	}
};

Point parsePoint(const std::string& string) {
	Point point;
	PointParser<std::string::const_iterator> parse;
	if (!boost::spirit::qi::phrase_parse(string.cbegin(), string.cend(), parse, boost::spirit::qi::ascii::space, point)) {
		LOG("Error parsing Point from \"%s\"n", string.c_str());
	}
	return point;
}

std::vector<Point> parsePoints(const std::string& string) {
	std::vector<Point> points;
	PointParser<std::string::const_iterator> parse;
	if (!boost::spirit::qi::phrase_parse(string.cbegin(), string.cend(), *parse, boost::spirit::qi::ascii::space, points)) {
		LOG("Error parsing Points from \"%s\"n", string.c_str());
	}
	return points;
}

Rect rectFromString(const std::string& string) {
	Rect value;
	std::string sub = string.substr(string.find("Rect") + 5);
	std::vector<Point> vals = parsePoints(sub);
	if (vals.size() == 4) value =  Rect(vals[0], vals[1], vals[2], vals[3]);
	if (vals.size() == 2) value = Rect(vals[0], vals[1]);
	return value;
}

Triangle triFromString(const std::string& string) {
	Triangle tri;
	std::string sub = string.substr(string.find("Tri") + 4);
	std::vector<Point> vals = parsePoints(sub);
	if (vals.size() == 3) tri = Triangle(vals[0], vals[1], vals[2]);
	return tri;
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
		StringPos type;
		// Sloppy but gets the job done
		if ((type = line.find("Sector", begin)) != std::string::npos) { // Sector
			// TODO: Functionize this, nerd
			Rect rect = rectFromString(line);
			if (rect.isReal()) {
				instance.sectors.createSector<Rect>(rect);
				continue;
			}
			Triangle tri = triFromString(line);
			if (tri.isReal()) {
				instance.sectors.createSector<Triangle>(tri);
				continue;
			}
		} else if ((type = line.find("BasicWall", begin)) != std::string::npos) { // Big Wall
			Rect rect = rectFromString(line);
			if (rect.isReal()) {
				instance.createThing<BigWall>(rect);
				continue;
			}
		} else if ((type = line.find("Thing", begin)) != std::string::npos) { // Definition of a thing
			std::cout << "We makin a thing" << std::endl;
		}
		LOG("Line %i of %s is improperly formatted for analysis.", lineNumber, source.c_str());	
	}
	file.close();
}

// TODO: Implement
void analyzeStructure(const std::string& source, GameInstance& instance, StringMap& map) {
	std::cout << source << "->" << &instance << &map << std::endl;
}
