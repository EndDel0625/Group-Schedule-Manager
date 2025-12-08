//
// Created by 김영빈 on 11/16/25.
//

#include "DayConverter.h"

std::string dayToString(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::Monday:
            return "Monday";
        case DayOfWeek::Tuesday:
            return "Tuesday";
        case DayOfWeek::Wednesday:
            return "Wednesday";
        case DayOfWeek::Thursday:
            return "Thursday";
        case DayOfWeek::Friday:
            return "Friday";
        case DayOfWeek::Saturday:
            return "Saturday";
        case DayOfWeek::Sunday:
            return "Sunday";
    }
    return "Unknown";
}