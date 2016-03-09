#ifndef __AE_H__
#define __AE_H__

#include <vector>
#include <string>

using namespace std;

namespace ae {

#define AE_OK 0
#define AE_ERR -1

#define AE_NONE 0
#define AE_READABLE 1
#define AE_WRITABLE 2

#define AE_FILE_EVENTS 1
#define AE_TIME_EVENTS 2
#define AE_ALL_EVENTS (AE_FILE_EVENTS|AE_TIME_EVENTS)
#define AE_DONT_WAIT 4

#define AE_NOMORE -1

/* File event class */
class FileEvent
{
private:
	int mask;  /* one of AE_(READABLE|WRITABLE) */
	void *clientData;
};

/* Time event class */
class TimeEvent
{
public:
	~TimeEvent();
private:
	long long id;  /* time event identifier */
	long when_sec; /* seconds */
	long when_ms;  /* milliseconds */
	void *clientData;

	TimeProc *timeProc;
	EventFinalizerProc *finalizerProc;
};

/* A fired event*/
struct FiredEvent
{
	it fd;
	int mask;
};

/* State of an event based program */
class EventLoop 
{
public:
	EventLoop(int setsize);
	~EventLoop();

	void restStop();

	int  createFileEvent(int fd, int mask, FileProc *proc, void *clientData);
	void deleteFileEvent(int fd, int mask);
	int  getFileEvents(int fd);

	long long createTimeEvent(long long milliseconds, aeTimeProc *proc, 
		                      void *clientData, EventFinalizerProc *finalizerProc);
	int  deleteTimeEvent(long long id);

	int  processEvents(int flags);

	int  wait(int fd, int mask, long long milliseconds);
	void main();

	string getApiName();
	void setBeforeSleepProc(BeforeSleepProc *beforesleep);

	int getSetSize();
	int resizeSetSize();


private:
	TimeEvent& searchNearestTimer();
	int maxfd;   /* highest file descriptor currently registered */
	int setsize; /* max number of file descriptors tracked */
	long long timeEventNextId;
	time_t lastTime;  /* Used to detect system clock skew */
	vector<FileEvent> events;
	vector<FiredEvent> fired;
	list<TimeEvent> timeEvents;
	int stop;
	void *apidata;
	BeforeSleepProc *beforesleep;

};

}
#endif