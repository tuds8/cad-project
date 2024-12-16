import User;
import Sink;
import Scheduler;

network RadioSch2
{
    parameters:
        int usersCount; // set from ini file

    submodules:
        scheduler: Scheduler {
            gateSize = parent.usersCount;
            @display("p=120,40");
        }
        sink: Sink {
            gateSize = parent.usersCount;
            @display("p=120,200");
        }
        user[usersCount]: User {
//            @display("p=40,120");
        }

    connections:
        for i = 0..usersCount - 1 {
            scheduler.txScheduling[i] --> user[i].rxScheduling;
            user[i].txPackets --> sink.rxPackets[i];
            user[i].txInfo --> scheduler.rxInfo[i];
        }
}
