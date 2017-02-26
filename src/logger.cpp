#include "logger.h"

#include <stdarg.h>

Logger::Logger() {
    file = fopen("output.log", "w");
    elapsedTime = 0;
}

void Logger::log(const char* format, ...) {
    char buffer[256];
    
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, (char *) args);
    va_end(args);
    
    fprintf(file, "%d: %s\n", elapsedTime, buffer);
    fflush(file);
}

void Logger::onTimeTick() {
    elapsedTime++;
}
