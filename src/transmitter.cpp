#include "transmitter.hpp"

namespace RFTR
{

Transmitter::Transmitter(const unsigned int pinnumber):
    _pinnumber{pinnumber}
{
    pinMode(_pinnumber, OUTPUT);
    //TODO check if pinnumber is valid. or does wiringPi this already?
}//Transmitter::Transmitter(const unsigned int)

Transmitter::Transmitter(const Transmitter& other):
    _pinnumber{other._pinnumber}
{
}//Transmitter::Transmitter(const Transmitter& other)

Transmitter::~Transmitter()
{
}//Transmitter::~Transmitter()

void Transmitter::transmit_pulse(const millisec ontime, const millisec offtime, unsigned int numreps) const
{
    //TODO check for maxlength. what does wiringPi (delay()) do when the number is to big?
    for (; numreps > 0; --numreps)
    {
        digitalWrite(_pinnumber, HIGH);
        delay(ontime);
        digitalWrite(_pinnumber, LOW);
        delay(offtime);
    }
}//void Transmitter::transmit_pulse(const millisec ontime, const millisec offtime, unsigned int numreps) const

}//namespace RFTR
