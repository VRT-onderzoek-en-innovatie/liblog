#include <stdio.h>
#include "../include/liblog_level.h"
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include "../include/liblog.h"

int main() {
	LogSetLevel(Info);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show");

	LogSetOutput(NULL);
	LogTrace("This should compile away");
	LogDebug("This should not show");
	LogInfo("This should show");

	return 0;
}
