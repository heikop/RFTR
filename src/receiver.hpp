#ifndef __RECEIVER_HPP_
#define __RECEIVER_HPP_

#include "RFTR.hpp"
#include <vector>

namespace RFTR
{

class Receiver
{
public:
    Receiver() = delete;
    Receiver(const unsigned int pinnumber, const microsec max_noise_length=static_cast<microsec>(0));
    Receiver(const Receiver&);
    Receiver(Receiver&&) = delete;
    Receiver& operator=(const Receiver&) = delete;
    Receiver& operator=(Receiver&&) = delete;
    ~Receiver();

    microsec get_max_noise_length() const;
    void set_max_noise_length(const microsec max_noise_length);

    // returns a vector with timeintervals: even entries contain duration of receiving no signal, odd contain duration of receiving signal
    std::vector<microsec>& receive_raw_data(const microsec duration) const;

private:
    const unsigned int _pinnumber;
    microsec _max_noise_length;
};//class Receiver

}//namespace RFTR

#endif//ifndef __RECEIVER_HPP_
