#include "timer.h"

int Timer::initTimer() {
    timerMsgPort = CreateMsgPort();
    if (timerMsgPort == 0) {
        return -1;
    }

	timerIO = (struct timerequest*) CreateIORequest(timerMsgPort, sizeof(struct timerequest));
	if (timerIO == 0) {
		return -1;
	}

	LONG error = OpenDevice(TIMERNAME, UNIT_VBLANK, (struct IORequest*)timerIO, 0);
	if (error != 0) {
		return -1;
	}	

	sendTimerRequest();

    timerWasSent = TRUE;

	return 0;
}

void Timer::killTimer() {
	if (timerIO) {
		if (timerWasSent) {
			AbortIO((struct IORequest*)timerIO);
			WaitIO((struct IORequest*)timerIO);
		}
		CloseDevice((struct IORequest*)timerIO);
		DeleteIORequest(timerIO);
	}

	if (timerMsgPort) {
		DeleteMsgPort((struct MsgPort*)timerMsgPort);
	}
}

void Timer::sendTimerRequest() {
	tv.tv_secs = 1;
	tv.tv_micro = 0;
    timerIO->tr_time = tv;
    timerIO->tr_node.io_Command = TR_ADDREQUEST;

	SendIO((struct IORequest*)timerIO);
}

void Timer::readTimerMessage() {
	while (TRUE) {
		struct IntuiMessage* msg = (struct IntuiMessage*)GetMsg(timerMsgPort);
		if (msg == NULL) {
			break;
		}
	}

	sendTimerRequest();
}
