simple myQ
{
    parameters:
        int qlp;
    @display("i=block/queue");
    gates:
        input rxScheduling;
        input rxPackets;
        output txPackets;
        output txInfo;
}
