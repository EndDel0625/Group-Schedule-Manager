//
// Created by 김영빈 on 11/4/25.
//

#ifndef FINAL_PROJECT_FILEINOUT_H
#define FINAL_PROJECT_FILEINOUT_H

#include "WeekSchedule.h"
#include "CollegeEvent.h"
#include <string>
#include <vector>

void saveScheduleToFile(const WeekSchedule* week);
WeekSchedule* loadScheduleFromFile(const std::string& studentId);

void saveCollegeEventsToFile(const std::vector<CollegeEvent*>& events, const std::string& filename);
std::vector<CollegeEvent*> loadCollegeEventsFromFile(const std::string& filename);

#endif //FINAL_PROJECT_FILEINOUT_H