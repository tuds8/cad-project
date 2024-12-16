#ifndef __SCHED_TST_SINK_H_
#define __SCHED_TST_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule
{
private:
    simsignal_t lifetimeSignal;    // Overall lifetime signal
    simsignal_t hpLifetimeSignal;  // HP category lifetime
    simsignal_t mpLifetimeSignal;  // MP category lifetime
    simsignal_t lpLifetimeSignal;  // LP category lifetime

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
