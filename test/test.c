#include <stdio.h>
#include "../include/liblog_level.h"
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include "../include/liblog.h"

int main() {
	LogSetLevel(NULL, Info);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show");

	LogSetOutputFile(NULL, NULL);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show");

	LogInfo("Generate a warning: %s", 5);

	LogInit();

	return 0;
}
