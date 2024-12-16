#ifndef __SCHED_TST_MYQ_H_
#define __SCHED_TST_MYQ_H_

#include <omnetpp.h>

using namespace omnetpp;

class myQ : public cSimpleModule
{
  protected:
    cQueue queue;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
