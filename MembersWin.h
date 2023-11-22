#pragma once 
#include <memory>
#include <windows.h>
#include <cstdint>
#include <iostream>

class Members
{
    public:
        friend class TimeMeter;
        unsigned count;
        double start_stamp;
        std::unique_ptr<double[]> stamps;
        Members(unsigned count);
        ~Members();
    private:
        double setTimeStamp(unsigned num);
        double getSTimeStamp(unsigned num);
        int64_t getMSTimeStamp(unsigned num);
        double getSDiff(unsigned first, unsigned second);
        int64_t getMSDiff(unsigned first, unsigned second);
        bool isLess(unsigned first, unsigned second, int64_t expected);
        bool isLess(unsigned num, int64_t expected);
};

Members::~Members() = default;

Members::Members(unsigned count)
{
    this->count = count;
    LARGE_INTEGER frequency;
    LARGE_INTEGER time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    this->start_stamp = time.QuadPart * 1.0 / frequency.QuadPart;
    this->stamps = std::unique_ptr<double[]>(new double[count]);
}

double Members::setTimeStamp(unsigned num)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    double stamp_tmp = time.QuadPart * 1.0 / frequency.QuadPart;
    this->stamps[num] = stamp_tmp - start_stamp;
    //std::cout << "STAMP " << this->stamps[num] << std::endl;
    return this->stamps[num];
}

double Members::getSTimeStamp(unsigned num) 
{
    return this->stamps[num];
}

int64_t Members::getMSTimeStamp(unsigned num) 
{
    return this->stamps[num] * 1000;
}

double Members::getSDiff(unsigned first, unsigned second) 
{
    return this->stamps[second] - this->stamps[first];
}

int64_t Members::getMSDiff(unsigned first, unsigned second) 
{
    return (this->stamps[second] - this->stamps[first]) * 1000;
}

bool Members::isLess(unsigned first, unsigned second, int64_t expected) 
{
    return this->getMSTimeStamp(second) - this->getMSTimeStamp(first) < expected;
}

bool Members::isLess(unsigned num, int64_t expected) 
{
    // std::cout << this->getMSTimeStamp(num) << std::endl;
    return this->getMSTimeStamp(num) < expected;
}