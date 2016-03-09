#include <algorithm>
#include "ae.h"

namespace ae {

EventLoop::EventLoop(int setsize)
{
	/* c++11 suport move semantics, so don't worry too much copy */
	this->events = vector<FileEvent>(setsize);
	this->fired  = vector<FiredEvent>(setsize);

	this->setsize = setsize;
	this->lastTime = time(NULL);
	/* TimeEventHead*/
	this->timeEventNextId = 0;
	this->stop = 0;
	this->maxfd = -1;
	this->beforesleep = nullptr;
}

void EventLoop::resetStop()
{
	this->stop = 1;
}

TimeEvent& EventLoop::searchNearestTimer()
{

}

}