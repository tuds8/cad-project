#ifndef __SCHED_TST_SOURCE_H_
#define __SCHED_TST_SOURCE_H_

#include <omnetpp.h>

using namespace omnetpp;

class Source : public cSimpleModule
{
private:
    cMessage *sendMessageEvent;

public:
    Source();
    virtual ~Source();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
