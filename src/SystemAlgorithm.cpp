//
// Created by 김영빈 on 11/16/25.
//

#include "SystemAlgorithm.h"
#include "DayConverter.h"
#include <iostream>
#include <vector>


void SystemAlgorithm::distributeMultiDayEvents(WeekSchedule* schedule) {
    if (schedule == nullptr) {
        return;
    }

    for (int d = static_cast<int>(DayOfWeek::Monday);
         d <= static_cast<int>(DayOfWeek::Sunday); ++d) {

        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* daySched = schedule->getDay(day);
        std::vector<Event*> evList = daySched->getEvents();

        for (Event* e : evList) {
            int startDay = static_cast<int>(e->getStartTime().getDay());
            int endDay   = static_cast<int>(e->getEndTime().getDay());

            // 하루짜리라면 건너뛰기
            if (startDay == endDay) {
                continue;
            }

            // 여러 날짜에 걸쳐서 진행되는 이벤트면 다음 날들에 추가
            for (int nd = startDay + 1; nd <= endDay; ++nd) {
                DayOfWeek nextDay = static_cast<DayOfWeek>(nd);
                DaySchedule* nextSched = schedule->getDay(nextDay);

                Event* newEvt = nullptr;
                if (StudentEvent* se = dynamic_cast<StudentEvent*>(e)) {
                    newEvt = new StudentEvent(*se);
                }
                else if (CollegeEvent* ce = dynamic_cast<CollegeEvent*>(e)) {
                    newEvt = new CollegeEvent(*ce);
                }
                else {
                    newEvt = new Event(*e);
                }

                nextSched->addEvent(newEvt);
            }
        }
         }
}