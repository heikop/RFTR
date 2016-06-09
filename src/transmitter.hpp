#ifndef __SENDER_HPP_
#define __SENDER_HPP_

#include "RFTR.hpp"


namespace RFTR
{

class Transmitter
{
public:
    Transmitter() = delete;
    Transmitter(const unsigned int pinnumber);
    Transmitter(const Transmitter&);
    Transmitter(Transmitter&&) = delete;
    Transmitter& operator=(const Transmitter&) = delete;
    Transmitter& operator=(Transmitter&&) = delete;
    ~Transmitter();

    void transmit_pulse(const millisec ontime, const millisec offtime, unsigned int numreps) const;

private:
    const unsigned int _pinnumber;
};//class Transmitter

}//namespace RFTR


#endif//ifndef __SENDER_HPP_
