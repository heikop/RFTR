#include <iostream>
#include <vector>
#include <thread>

#include "../src/RFTR.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

void transmit(const int argc, const char* argv[])
{
    // reading data from command line arguments
    auto cast_uint_abs = [](const char a[]) { return static_cast<unsigned int>(std::abs(std::stoi(a))); };
    const unsigned int pinnumber{argc > 1 ? cast_uint_abs(argv[1]) : 0};
    const unsigned int ontime{argc > 2 ? cast_uint_abs(argv[2]) : 1000};
    const unsigned int offtime{argc > 3 ? cast_uint_abs(argv[3]) : 1000};
    const unsigned int numreps{argc > 4 ? cast_uint_abs(argv[4]) : 2};

    // setup
    const RFTR::Transmitter pulsetransmitter{pinnumber};

    // send pulse(s)
    //std::cout << "start sending " << std::endl
    //          << numreps << " pulse(s) with " << std::endl
    //          << ontime << "ms ontime and " << std::endl
    //          << offtime << "ms offtime through " << std::endl
    //          << "pin " << pinnumber<< std::endl;
    pulsetransmitter.transmit_pulse(ontime, offtime, numreps);
    //std::cout << "pulse(s) send" << std::endl;
}

//std::vector<RFTR::microsec> receive(const int argc, const char* argv[])
void receive(const int argc, const char* argv[], std::vector<RFTR::microsec>* returnval)
{
    // reading data from command line arguments
    auto cast_uint_abs = [](const char a[]) { return static_cast<unsigned int>(std::abs(std::stoi(a))); };
    const unsigned int pinnumber{argc > 1 ? cast_uint_abs(argv[1]) : 1};
    const unsigned int duration{argc > 2 ? cast_uint_abs(argv[2]) : 5000000};

    // setup
    const RFTR::Receiver receiver{pinnumber};

    // receive data
    std::vector<RFTR::microsec> data = receiver.receive_raw_data(static_cast<RFTR::microsec>(duration));

    *returnval = data;
}

int main(const int argc, const char* argv[])
{
    std::cout << "running" << std::endl;
    wiringPiSetup();

    std::vector<RFTR::microsec> data;
    std::thread rec(receive, argc, argv, &data);
    std::thread trans(transmit, argc, argv);
    trans.join();
    std::cout << "transmitting completed" << std::endl;
    rec.join();
    std::cout << "receiving completed" << std::endl;

    RFTR::microsec total{0};
    RFTR::microsec low{0};
    RFTR::microsec high{0};
    RFTR::microsec maxnoiselength{0};
    size_t numhigh{0};
    for (size_t i{0}; i < data.size(); ++i)
    {
        std::cout << data[i].count()/1e6 << ", ";
        total += data[i];
        //if (data[i].count()/1e6 < 1e-4) data[i] = static_cast<RFTR::microsec>(0);
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
    std::cout << "high: " << high.count()/1e6 << std::endl
              << "low: " << low.count()/1e6 << std::endl
              << "total: " << total.count()/1e6 << std::endl
              << "max noise length: " << maxnoiselength.count()/1e6 << std::endl
              << "average noise length: " << high.count()/(1e6 * static_cast<double>(numhigh)) << std::endl
              << "noise percentage: " << std::fixed << std::showpoint << static_cast<double>(high.count())/static_cast<double>(total.count()) * 100.0 << "%" << std::endl;
    return 0;
}
