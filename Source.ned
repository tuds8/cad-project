simple Source
{
    parameters:
        double sendIaTime @unit(ms) = default(10 ms);
        double netwload;      // network load parameter
        int nrUsers;
        int nrOfChannels;
        int nrPackets;

    @display("i=block/source");

    gates:
        output txPackets;
}
