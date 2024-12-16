simple Sink
{
    parameters:
        int gateSize;
    @display("i=block/sink");

    // Existing overall lifetime signal
    @signal[lifetime](type=simtime_t);
    @statistic[lifetime](title="Packet Lifetime"; unit=s; record=mean,vector);

    // New signals and statistics for each category
    @signal[hpLifetime](type=simtime_t);
    @statistic[hpLifetime](title="HP Packet Lifetime"; unit=s; record=mean,vector);

    @signal[mpLifetime](type=simtime_t);
    @statistic[mpLifetime](title="MP Packet Lifetime"; unit=s; record=mean,vector);

    @signal[lpLifetime](type=simtime_t);
    @statistic[lpLifetime](title="LP Packet Lifetime"; unit=s; record=mean,vector);

    gates:
        input rxPackets[gateSize];
}
