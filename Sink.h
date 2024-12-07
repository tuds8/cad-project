#ifndef __SCHED_TST_SINK_H_
#define __SCHED_TST_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule
{
private:
    simsignal_t lifetimeSignal;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
