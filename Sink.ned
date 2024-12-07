simple Sink
{
    
    parameters:
        int gateSize;
    @display("i=block/sink");
    // Declare a signal to record packet lifetime
    @signal[lifetime](type=simtime_t);
    @statistic[lifetime](title="Packet Lifetime"; unit=s; record=mean,vector);
    gates:
        input rxPackets[gateSize];
}
