#ifndef __RFTR_HPP_
#define __RFTR_HPP_

// some typedefs
namespace RFTR
{
//typedef std::chrono::milliseconds millisec;
//typedef std::chrono::microseconds microsec;
typedef unsigned int millisec;
typedef unsigned int microsec;
}//namespace RFTR

// including some libraries most classes/functions need (maybe delete this later)
#include <wiringPi.h>
#include <chrono>

// all headers you probably want to use as a black box outside this 'library'
#include "transmitter.hpp"
#include "receiver.hpp"

#endif//ifndef __RFTR_HPP_
