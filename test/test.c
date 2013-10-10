#include <stdio.h>
#include "../include/libsimplelog_level.h"
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include "../include/libsimplelog.h"

int main() {
	LogSetLevel(NULL, Info);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show on stderr");

	LogSetOutputFile(NULL, stdout);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show on stdout");

	LogSetLevel(NULL, Warn);
	LogInfo("Generate a compile time warning: %s", 5);

	LogInit();

	return 0;
}
