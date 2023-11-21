#ifndef TIMEMETER_MEMBERSWIN_H
#define TIMEMETER_MEMBERSWIN_H

#include <memory>
#include <windows.h>

class Members{
private:
    unsigned count;
    std::unique_ptr<double[]> timeStamps;
public:
    explicit Members(unsigned count){
        this->count = count;
        this->timeStamps = std::unique_ptr<double[]>(new double[count]);
    }

    double setTimeStamp(unsigned num) {
        LARGE_INTEGER frequency;
        LARGE_INTEGER time;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&time);
        timeStamps[num] = time.QuadPart * 1.0 / frequency.QuadPart;
        return timeStamps[num];
    }

    double getSTimeStamp(unsigned num) {
        return timeStamps[num];
    }

    int64_t getMSTimeStamp(unsigned num) {
        return timeStamps[num] / 1000000;
    }

    double getSDiff(unsigned first, unsigned second) {
        return timeStamps[second] - timeStamps[first];
    }

    int64_t getMSDiff(unsigned first, unsigned second) {
        return (timeStamps[second] - timeStamps[first]) * 1000;
    }

    bool isLess(unsigned first, unsigned second, int64_t expected) {
        return getMSTimeStamp(second) - getMSTimeStamp(first) < expected;
    }

    bool isLess(unsigned num, int64_t expected) {
        return getMSTimeStamp(num) < expected;
    }
};

#endif
