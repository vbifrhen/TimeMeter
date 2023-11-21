#ifndef TIMEMETER_TIMEMETER_H
#define TIMEMETER_TIMEMETER_H


#include <cstdint>
#include <memory>

class Members;
class TimeMeter {
public:
    ~TimeMeter();
    explicit TimeMeter(unsigned count);
    double setTimeStamp(unsigned num);
    double getSTimeStamp(unsigned num);
    int64_t getMSTimeStamp(unsigned num);
    double getSDiff(unsigned first, unsigned second);
    int64_t getMSDiff(unsigned first, unsigned second);
    bool isLess(unsigned first, unsigned second, int64_t expected);
    bool isLess(unsigned num, int64_t expected);

private:
    std::unique_ptr<Members> members;
};


#endif
