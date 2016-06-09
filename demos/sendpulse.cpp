//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// small demo about sending a pulse (on - off, x times)                         //
//                                                                              //
// usage: ./sendpulse [<pinnumber> [<ontime> [<offtime> [<numreps>]]]]          //
// example: ./sendpulse 0 100 100 1                                             //
//                                                                              //
// command line arguments:                                                      //
// pinnumber - the pin the signal is send from (WiringPi numbering!)            //
//             default: 0 (WiringPi numbering!)                                 //
// ontime    - time in milliseconds for which a signal is send                  //
//             default: 100                                                     //
// offtime   - time in milliseconds for pausing between signals                 //
//             default: 100                                                     //
// numreps   - number of on-off repetitions (pulses)                            //
//             default: 1                                                       //
// (invalid input (like characters) causes zero assignment, minus becomes plus) //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "../src/RFTR.hpp"

int main(const int argc, const char* argv[])
{
    // reading data from command line arguments
    auto cast_uint_abs = [](const char a[]) { return static_cast<unsigned int>(std::abs(std::stoi(a))); };
    const unsigned int pinnumber{argc > 1 ? cast_uint_abs(argv[1]) : 0};
    const unsigned int ontime{argc > 2 ? cast_uint_abs(argv[2]) : 100};
    const unsigned int offtime{argc > 3 ? cast_uint_abs(argv[3]) : 100};
    const unsigned int numreps{argc > 4 ? cast_uint_abs(argv[4]) : 1};

    // setup
    wiringPiSetup();
    const RFTR::Transmitter pulsetransmitter{pinnumber};

    // send pulse(s)
    std::cout << "start sending " << std::endl
              << numreps << " pulse(s) with " << std::endl
              << ontime << "ms ontime and " << std::endl
              << offtime << "ms offtime through " << std::endl
              << "pin " << pinnumber<< std::endl;
    pulsetransmitter.transmit_pulse(ontime, offtime, numreps);
    std::cout << "pulse(s) send" << std::endl;

    return 0;
}
