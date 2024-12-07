#include "Scheduler.h"
#include <algorithm>
#include <vector>
#include <omnetpp.h>
#include <random>

// Generate a random link quality
double generateRadioLinkQuality(cRNG *rng)
{
    return uniform(rng, 1, 10);
}

Define_Module(Scheduler);

Scheduler::Scheduler()
{
    selfMsg = nullptr;
}

Scheduler::~Scheduler()
{
    cancelAndDelete(selfMsg);
}

void Scheduler::initialize()
{
    // The number of users is determined by gateSize
    numUsers = par("gateSize");

    // Retrieve parameters from NED/ini file
    // schedulingPeriod (in ms) and nrOfChannels (RBs)
    scheduleInterval = par("schedulingPeriod").doubleValue(); // ms
    numRbs = par("nrOfChannels").intValue();

    // Initialize arrays/vectors based on number of users
    servedLastTime.assign(numUsers, simTime());
    q.assign(numUsers, 0);
    NrBlocks.assign(numUsers, 0);

    // Initialize weight factors
    // If you have exactly 10 users, this is fine:
    if (numUsers == 10) {
        int wf[10] = {6,6,2,2,2,2,2,1,1,1};
        weightFactors.assign(wf, wf+10);
    } else {
        // If numUsers != 10, handle accordingly (for now just assume 10)
        throw cRuntimeError("Number of users != 10. Adjust weight factors accordingly.");
    }

    selfMsg = new cMessage("schedule");
    // Convert scheduleInterval to seconds for scheduleAt
    scheduleAt(simTime() + scheduleInterval/1000.0, selfMsg);
}

void Scheduler::handleMessage(cMessage *msg)
{
    if (msg == selfMsg) {
        // Perform the scheduling algorithm
        scheduleUsers();

        // Re-schedule the next cycle
        scheduleAt(simTime() + scheduleInterval/1000.0, selfMsg);
        return;
    }

    // Otherwise, the message must have arrived from one of the rxInfo gates
    for (int i = 0; i < numUsers; i++) {
        if (msg->arrivedOn("rxInfo", i)) {
            // Extract queue length information from the message parameter
            q[i] = msg->par("ql_info").longValue();
            EV << "Update: q[" << i << "] = " << q[i] << endl;
            delete msg;
            return;
        }
    }

    // If it doesn't match any known condition, just delete the message
    delete msg;
}

void Scheduler::scheduleUsers()
{
    // Compute radio link qualities for all users and RBs
    std::vector<std::vector<double>> radioQualities(numUsers, std::vector<double>(numRbs));
    for (int i = 0; i < numUsers; i++) {
        for (int rb = 0; rb < numRbs; rb++) {
            radioQualities[i][rb] = generateRadioLinkQuality(getRNG(0));
            EV << "Random Radio Quality: user=" << i << " RB=" << rb
               << " quality=" << radioQualities[i][rb] << endl;
        }
    }

    // Allocation vector: how many RBs each user gets
    std::vector<int> allocation(numUsers, 0);

    // For each RB, run an "auction"
    for (int rb = 0; rb < numRbs; rb++)
    {
        int bestUser = -1;
        double bestParam = -1.0;

        // Compute per-RB scheduling parameter for each user and select the best
        for (int i = 0; i < numUsers; i++) {
            simtime_t timeElapsed = simTime() - servedLastTime[i];
            double param = radioQualities[i][rb] * timeElapsed.dbl() * weightFactors[i];

            if (param > bestParam) {
                bestParam = param;
                bestUser = i;
            }
        }

        // Allocate this RB to the bestUser
        if (bestUser != -1) {
            allocation[bestUser]++;
            EV << "RB " << rb << " allocated to user " << bestUser << " (param=" << bestParam << ")\n";
        }
    }

    // Send out scheduling commands
    for (int i = 0; i < numUsers; i++) {
        EV << "User " << i << " allocated " << allocation[i] << " RBs.\n";
        if (allocation[i] > 0) {
            cMessage *scheduleMsg = new cMessage("schedulingInfo");
            scheduleMsg->addPar("nrOfBlocks").setLongValue(allocation[i]);
            send(scheduleMsg, "txScheduling", i);

            // Update servedLastTime for users who got at least one RB
            servedLastTime[i] = simTime();
        }
    }
}
