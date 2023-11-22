#pragma once 
#include <memory>

class Members{
private:
    unsigned count;
    double start;
    std::unique_ptr<double[]> timeStamps;
public:
    explicit Members(unsigned count){
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        this->count = count;
        this->start = ts.tv_sec + (ts.tv_nsec / 1000000) * 0.001;
        this->timeStamps = std::unique_ptr<double[]>(new double[count]);
    }

    double setTimeStamp(unsigned num) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        timeStamps[num] = (ts.tv_sec + (ts.tv_nsec / 1000000) * 0.001 - this->start);
        return timeStamps[num];
    }

    double getSTimeStamp(unsigned num) {
        return timeStamps[num];
    }

    int64_t getMSTimeStamp(unsigned num) {
        return timeStamps[num] * 1000;
    }

    double getSDiff(unsigned first, unsigned second) {
        return (timeStamps[second] - timeStamps[first]);
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
