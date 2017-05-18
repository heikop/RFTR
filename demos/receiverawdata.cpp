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

    // setup
    wiringPiSetup();
    const RFTR::Receiver receiver{pinnumber};

    // receive data
    std::cout << "---------receive-raw-data---------" << std::endl;
    std::cout << "start receiving data for" << std::endl
              << duration/10e5 << "s ontime through" << std::endl
              << "pin " << pinnumber<< std::endl;
    std::vector<RFTR::microsec> data = receiver.receive_raw_data(static_cast<RFTR::microsec>(duration));
    std::cout << "data received:" << std::endl;

    RFTR::microsec total{0};
    RFTR::microsec low{0};
    RFTR::microsec high{0};
    RFTR::microsec maxnoiselength{0};
    size_t numhigh{0};
    for (size_t i{0}; i < data.size(); ++i)
    {
        std::cout << data[i].count()/10e5 << ", ";
        total += data[i];
        if (i % 2 == 0)
            low += data[i];
        else
        {
            high += data[i];
            ++numhigh;
            if (data[i] > maxnoiselength)
                maxnoiselength = data[i];
        }
    }
    std::cout << std::endl;
    std::cout << "---------result-overview----------" << std::endl;
    std::cout << "high: " << high.count()/10e5 << std::endl
              << "low: " << low.count()/10e5 << std::endl
              << "total: " << total.count()/10e5 << std::endl
              << "max noise length: " << maxnoiselength.count()/10e5 << std::endl
              << "average noise length: " << high.count()/(10e5 * static_cast<double>(numhigh)) << std::endl
              //<< "noise percentage: " << std::setprecision(10) << std::showpoint << static_cast<double>(high.count())/static_cast<double>(total.count()) * 100.0 << "%" << std::endl;
              << "noise percentage: " << std::fixed << std::showpoint << static_cast<double>(high.count())/static_cast<double>(total.count()) * 100.0 << "%" << std::endl;

    return 0;
}
