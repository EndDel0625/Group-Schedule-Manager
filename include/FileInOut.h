//
// Created by 김영빈 on 11/4/25.
//

#ifndef FINAL_PROJECT_FILEINOUT_H
#define FINAL_PROJECT_FILEINOUT_H

#include "WeekSchedule.h"
#include <string>

void saveScheduleToFile(const WeekSchedule* week);
WeekSchedule* loadScheduleFromFile(const std::string& filename);


#endif //FINAL_PROJECT_FILEINOUT_H