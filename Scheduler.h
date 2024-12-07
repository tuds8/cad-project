#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

class Scheduler : public cSimpleModule
{
private:
    cMessage *selfMsg;
    int numUsers;
    int numRbs; // number of RBs
    double scheduleInterval; // in ms

    std::vector<simtime_t> servedLastTime;
    std::vector<int> q;         // queue lengths for each user
    std::vector<int> NrBlocks;  // allocated blocks per user

    void scheduleUsers();

    // We keep the weight factors fixed as given in the example.
    // If you change the number of users, you need to adapt these weights accordingly.
    std::vector<int> weightFactors;

public:
    Scheduler();
    virtual ~Scheduler();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
