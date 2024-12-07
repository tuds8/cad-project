#include "Sink.h"

Define_Module(Sink);

void Sink::initialize()
{
    lifetimeSignal = registerSignal("lifetime");
}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t lifetime = simTime() - msg->getCreationTime();
    EV << "Received " << msg->getName() << ", lifetime: " << lifetime << "s" << endl;
    emit(lifetimeSignal, lifetime);
    delete msg;
}
