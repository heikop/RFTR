#include "receiver.hpp"

namespace RFTR
{

Receiver::Receiver(const unsigned int pinnumber, const microsec max_noise_length):
    _pinnumber{pinnumber},
    _max_noise_length{max_noise_length}
{
    pinMode(_pinnumber, INPUT);
    //TODO check if pinnumber is valid. or does wiringPi this already?
}//Receiver::Receiver(const unsigned int pinnumber, const microsec max_noise_length):

Receiver::Receiver(const Receiver& other):
    _pinnumber{other._pinnumber},
    _max_noise_length{other._max_noise_length}
{
}//Receiver::Receiver(const Receiver& other)

Receiver::~Receiver()
{
}//Receiver::~Receiver()

microsec Receiver::get_max_noise_length() const
{
    return _max_noise_length;
}//microsec Receiver::get_max_noise_length() const

void Receiver::set_max_noise_length(const microsec max_noise_length)
{
    _max_noise_length = max_noise_length;
}//void Receiver::set_max_noise_length(const microsec max_noise_length)

std::vector<microsec>& Receiver::receive_raw_data(const microsec duration) const
{
    std::vector<microsec>* data = new std::vector<microsec>(0);

    std::chrono::high_resolution_clock clock;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time{clock.now() + static_cast<std::chrono::microseconds>(duration)};
    std::chrono::time_point<std::chrono::high_resolution_clock> last_time{clock.now()};
    std::chrono::time_point<std::chrono::high_resolution_clock> new_time;
    int last_read{LOW};
    int new_read{LOW};

    do
    {
        new_time = clock.now();
        new_read = digitalRead(_pinnumber);
        if (last_read != new_read)
        {
            //TODO direct noise checking
            data->push_back(std::chrono::duration_cast<microsec>(new_time - last_time));
            last_time = new_time;
            last_read = new_read;
        }
    }while(new_time < end_time);
    if (last_read == new_read)
    {
        //TODO direct noise checking
        data->push_back(std::chrono::duration_cast<microsec>(new_time - last_time));
    }

    return *data;
}//std::vector<microsec>& Receiver::receive_raw_data(const microsec duration) const

}//namespace RFTR
