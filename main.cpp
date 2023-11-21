#include <iostream>
#include "TimeMeter.h"
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <cmath>

//Функция для подсчёта времени выполнения функции
int64_t timeFunc(const std::function<void()>& func) {
    TimeMeter timeMeter(2);
    timeMeter.setTimeStamp(0);
    func();
    timeMeter.setTimeStamp(1);
    return timeMeter.getMSTimeStamp(1);
}

int sum(int a, int b) {
    sleep(2);
    return a + b;
}

int main() {
    
    TimeMeter timeMeter(2);
    timeMeter.setTimeStamp(0);
    sleep(10);
    timeMeter.setTimeStamp(1);
    std::cout << timeMeter.getMSTimeStamp(1) << std::endl;
    std::cout << timeMeter.getSDiff(0, 1) << std::endl;
    std::cout << timeMeter.getMSDiff(0, 1) << std::endl;
    std::cout << timeMeter.isLess(0, 1, 1000) << std::endl;
    std::cout << timeMeter.isLess(0, 1000) << std::endl;
    
    auto factorial = [](int n){
        std::function<int(int)> fact = [&fact](int n) -> int {
            if (n == 0) return 1;
            return n * fact(n - 1);
        };
        return fact(n);
    };

    std::cout << timeFunc(std::bind(sum, 1, 2)) << std::endl;
    std::cout << timeFunc(std::bind(factorial, 15)) << std::endl;
    std::cout << timeFunc([&]{return factorial(20);}) << std::endl;

    std::vector<int> v = {1, 6, 4, 8, 9, 10, 3, 2, 5, 7};
    std::vector<int> v2 = v;
    std::transform(v.begin(), v.end(), v.begin(), std::bind(std::multiplies<>(), std::placeholders::_1, std::placeholders::_1));
    std::cout << "Vector in power 2:" << std::endl;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int power = 3;
    std::transform(v2.begin(), v2.end(), v2.begin(), std::bind(std::pow<int, int>, std::placeholders::_1, power));
    std::cout << "Vector in power 3:" << std::endl;
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}
