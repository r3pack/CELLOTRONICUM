// demo0.ck
// basic demo showing time and duration



// create our OSC receiver
OscRecv recv;
// use port 6449
6449 => recv.port;
// start listening (launch thread)
recv.listen();

recv.event( "/ping, i" ) @=> OscEvent oe;



5::second + now => time later;

while ( true )
{
    // wait for event to arrive
    oe => now;

    // grab the next message from the queue. 
    while ( oe.nextMsg() != 0 )
    { 
        oe.getInt() => int zmienna;
        // print
        <<< "ping nr: ", zmienna >>>;
    }
}