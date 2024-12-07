simple Scheduler
{
    parameters:
        double schedulingPeriod @unit(ms) = default(1 ms);
        int gateSize; // number of users
        int nrOfChannels; // number of RBs
    @display("i=block/dispatch");
    gates:
        output txScheduling[gateSize];
        input rxInfo[gateSize];
}
