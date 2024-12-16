#include "Sink.h"

Define_Module(Sink);

void Sink::initialize()
{
    lifetimeSignal = registerSignal("lifetime");
    hpLifetimeSignal = registerSignal("hpLifetime");
    mpLifetimeSignal = registerSignal("mpLifetime");
    lpLifetimeSignal = registerSignal("lpLifetime");
}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t lifetime = simTime() - msg->getCreationTime();

    // Retrieve userId from the packet
    int userId = msg->par("userId").longValue();

    // Determine category based on userId
    const char *category = "LP"; // default
    if (userId == 0 || userId == 1)
        category = "HP";
    else if (userId >= 2 && userId <= 6)
        category = "MP";

    // Emit the category-specific lifetime signal
    if (strcmp(category, "HP") == 0) {
        emit(hpLifetimeSignal, lifetime);
    } else if (strcmp(category, "MP") == 0) {
        emit(mpLifetimeSignal, lifetime);
    } else {
        emit(lpLifetimeSignal, lifetime);
    }

    // Emit the overall lifetime if you still need the combined metric
    emit(lifetimeSignal, lifetime);

    EV << "Received " << msg->getName() << " from userId=" << userId << ", lifetime: " << lifetime << "s, category=" << category << endl;
    delete msg;
}
