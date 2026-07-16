//
// Created by itamar on 7/16/26.
//

#ifndef APP_TIMER_H
#define APP_TIMER_H
#include <string>
#include <nlohmann/json.hpp>

struct Timer {
    int timerId = -1;
    std::string timerName;
    std::string creatorUsername;
    int creationTime;
    int duration;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Timer, timerId, timerName, creatorUsername, creationTime, duration)
};

#endif //APP_TIMER_H
