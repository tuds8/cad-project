#include "myQ.h"

Define_Module(myQ);

void myQ::initialize()
{
    queue.setName("queue");
}

void myQ::handleMessage(cMessage *msg)
{
    int ql; // Queue length

    if (msg->arrivedOn("rxPackets")) {
        // Packet arrived at the queue
        queue.insert(msg);
    } else if (msg->arrivedOn("rxScheduling")) {
        // Scheduling information received
        if (msg->hasPar("nrOfBlocks")) {
            int nrOfRadioBlocks = msg->par("nrOfBlocks").longValue();
            delete msg;

            // Dequeue packets based on the number of RBs assigned
            for (int i = 0; i < nrOfRadioBlocks && !queue.isEmpty(); i++) {
                cMessage *packet = (cMessage *)queue.pop();
                send(packet, "txPackets");
            }
        } else {
            EV << "Received scheduling message without nrOfBlocks parameter\n";
            delete msg;
        }
    }

    // Send queue length to the scheduler for statistics
    ql = queue.getLength();
    cMessage *qInfo = new cMessage("qInfo");
    qInfo->addPar("ql_info");
    qInfo->par("ql_info").setLongValue(ql);

    send(qInfo, "txInfo");
}
