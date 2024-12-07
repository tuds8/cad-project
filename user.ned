import myQ;
import Source;

module User
{
    parameters:
        @display("i=block/user");
    gates:
        output txPackets;   // Packets sent to the sink
        output txInfo;      // Queue info sent to the scheduler
        input rxScheduling; // Input for receiving scheduling instructions

    submodules:
        generator: Source {
            @display("p=50,50");
        }

        myqq: myQ {
            @display("p=50,100");
        }

    connections:
        rxScheduling --> myqq.rxScheduling;
        generator.txPackets --> myqq.rxPackets;
        myqq.txPackets --> txPackets;
        myqq.txInfo --> txInfo;
}
