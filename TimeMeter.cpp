#include "TimeMeter.h"
#include "MembersWin.h"

TimeMeter::TimeMeter(unsigned count) : members(new Members(count)) {}

TimeMeter::~TimeMeter() = default;

double TimeMeter::setTimeStamp(unsigned num) {
    return members->setTimeStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) {
    return members->getSTimeStamp(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) {
    return members->getMSTimeStamp(num);
}

double TimeMeter::getSDiff(unsigned first, unsigned second) {
    return members->getSDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) {
    return members->getMSDiff(first, second);
}

bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) {
    return members->isLess(first, second, expected);
}

bool TimeMeter::isLess(unsigned num, int64_t expected) {
    return members->isLess(num, expected);
}