//
// Created by 김영빈 on 11/16/25.
//

#ifndef FINAL_PROJECT_DAYCONVERTER_H
#define FINAL_PROJECT_DAYCONVERTER_H

#include <string>

enum class DayOfWeek {
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

std::string dayToString(DayOfWeek day);

#endif //FINAL_PROJECT_DAYCONVERTER_H