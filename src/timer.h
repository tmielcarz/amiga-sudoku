#ifndef TIMER_H
#define TIMER_H

#include <proto/exec.h>
#include <devices/timer.h>

class Timer {    
private:
    struct timerequest *timerIO;
    struct timeval tv;
    BOOL timerWasSent;

    void sendTimerRequest();

public:
    struct MsgPort *timerMsgPort;

    int initTimer();
    void killTimer();
    void readTimerMessage();
};

#endif
