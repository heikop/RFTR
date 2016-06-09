//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// small demo about receiving raw data (for x seconds)                          //
//                                                                              //
// usage: ./receiverawdata [<pinnumber> [<duration>]]                           //
// example: ./receiverawdata 1 5000000                                          //
//                                                                              //
// command line arguments:                                                      //
// pinnumber - the pin the signal is received from (WiringPi numbering!)        //
//             default: 1 (WiringPi numbering!)                                 //
// duration  - time in microseconds for which a signal is received              //
//             default: 5000000                                                 //
// (invalid input (like characters) causes zero assignment, minus becomes plus) //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

#include "../src/RFTR.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

int main(const int argc, const char* argv[])
{
    // reading data from command line arguments
    auto cast_uint_abs = [](const char a[]) { return static_cast<unsigned int>(std::abs(std::stoi(a))); };
    const unsigned int pinnumber{argc > 1 ? cast_uint_abs(argv[1]) : 1};
    const unsigned int duration{argc > 2 ? cast_uint_abs(argv[2]) : 5000000};

//    std::chrono::high_resolution_clock clock;
//    std::chrono::time_point<std::chrono::high_resolution_clock> end_time{clock.now() + static_cast<std::chrono::microseconds>(duration)};
//    std::time_t now = std::chrono::high_resolution_clock::to_time_t(clock.now());
//    std::cout << std::put_time(std::localtime(&now), "%F %T") << std::endl;
//    while (clock.now() < end_time) { }
//    now = std::chrono::high_resolution_clock::to_time_t(clock.now());
//    std::cout << std::put_time(std::localtime(&now), "%F %T") << std::endl;

    // setup
    wiringPiSetup();
    const RFTR::Receiver receiver{pinnumber};

    // receive data
    std::cout << "start receiving data for" << std::endl
              << duration/10e6 << "s ontime through" << std::endl
              << "pin " << pinnumber<< std::endl;
    std::vector<RFTR::microsec> data = receiver.receive_raw_data(duration);
    std::cout << "data received:" << std::endl;
    for (const auto x : data)
        std::cout << x << ", ";
    std::cout << std::endl;

    return 0;
}
