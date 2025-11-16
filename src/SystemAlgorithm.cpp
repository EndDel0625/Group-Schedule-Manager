//
// Created by 김영빈 on 11/16/25.
//

#include "SystemAlgorithm.h"
#include "DayConverter.h"
#include <iostream>
#include <vector>


void SystemAlgorithm::distributeMultiDayEvents(WeekSchedule* schedule) {

    for (int d = 0; d <= 6; d++) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* daySchedule = schedule->getDay(day);
        std::vector<Event*> events = daySchedule->getEvents();

        for (Event* e : events) {

            int startDay = static_cast<int>(e->getStartTime().getDay());
            int endDay = static_cast<int>(e->getEndTime().getDay());

            // for one day
            if (startDay == endDay) {
                continue;
            }

            // 여러 날에 걸쳐 있으면 다음 요일들에 복사
            for (int nd = startDay + 1; nd <= endDay; nd++) {
                DayOfWeek nextDay = static_cast<DayOfWeek>(nd);
                DaySchedule* nextSchedule = schedule->getDay(nextDay);

                Event* newCopy = nullptr;
                if (dynamic_cast<StudentEvent*>(e) != nullptr) {
                    newCopy = new StudentEvent(*(dynamic_cast<StudentEvent*>(e)));
                }
                else if (dynamic_cast<CollegeEvent*>(e) != nullptr) {
                    newCopy = new CollegeEvent(*(dynamic_cast<CollegeEvent*>(e)));
                }
                else {
                    newCopy = new Event(*e);
                }

                nextSchedule->addEvent(newCopy);
            }
        }
    }
}