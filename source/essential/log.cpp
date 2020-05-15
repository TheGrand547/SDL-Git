#include "log.h"

void logFormat(const char* file, const char* function, int line) {
	std::time_t now = time(0);
	std::tm* ltm = localtime(&now);
    int millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000;
	printf("[%02i:%02i:%02i:%03i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec, millis);
	printf("[%s][%s] Line %i: ", file, function, line);
}
