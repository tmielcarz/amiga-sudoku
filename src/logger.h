#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

class Logger {
private:
    FILE *file;
    int elapsedTime;
    
    Logger();
    Logger(Logger const&);
    void operator=(Logger const&);
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    
    void log(const char* format, ...);
    void onTimeTick();
};

#endif
        