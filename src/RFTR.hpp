#ifndef __RFTR_HPP_
#define __RFTR_HPP_

// including some libraries most classes/functions need (maybe delete this later)
#include <iostream>//TODELETE
#include <wiringPi.h>
#include <chrono>

// some typedefs
namespace RFTR
{
//typedef std::chrono::milliseconds millisec;
typedef std::chrono::microseconds microsec;
typedef unsigned int millisec;
//typedef unsigned int microsec;
}//namespace RFTR

// all headers you probably want to use as a black box outside this 'library'
#include "transmitter.hpp"
#include "receiver.hpp"

#endif//ifndef __RFTR_HPP_
