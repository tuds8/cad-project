#include "Source.h"

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = nullptr;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
}

void Source::handleMessage(cMessage *msg)
{
    ASSERT(msg == sendMessageEvent);

    // Create and send a new job (packet)
    cMessage *job = new cMessage("job");
    send(job, "txPackets");

    // Calculate sending time based on network load
    double netwload = par("netwload").doubleValue();   // network load
    int nrUsers = par("nrUsers").intValue();           // total number of users
    int nrPackets = par("nrPackets").intValue();       // packets per user
    // Scheduling cycle from the scheduler, we can assume 1ms or read from scheduler:
    // For simplicity, we hardcode here or read from .ini if needed.
    double schedulingCycle = 0.001;   // 1ms in seconds
    int nrOfChannels = par("nrOfChannels").intValue(); // number of RBs

    // This formula is just as an example. Adjust as needed.
    double sendingTime = (nrUsers * nrPackets * schedulingCycle) / (netwload * nrOfChannels);

    scheduleAt(simTime() + exponential(sendingTime), sendMessageEvent);
}
