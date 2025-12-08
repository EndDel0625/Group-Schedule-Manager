//
// Created by 김영빈 on 11/16/25.
//

#include "SystemAlgorithm.h"
#include <iostream>
#include <algorithm>


void SystemAlgorithm::addStudentSchedule(WeekSchedule* schedule) {
    if (!schedule) {
        return;
    }
    distributeMultiDayEvents(schedule);
    resolveConflicts(schedule);
    allSchedules.push_back(schedule);
}

void SystemAlgorithm::distributeMultiDayEvents(WeekSchedule* schedule) {
    for (int d = 0; d < 7; d++) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = schedule->getDay(day);
        if (!ds) {
            continue;
        }
        std::vector<Event*> copy = ds->getEvents();

        for (Event* ev : copy) {
            auto* ce = dynamic_cast<CollegeEvent*>(ev);
            if (!ce) continue;

            DayOfWeek startDow = ce->getStartTime().getDayOfWeek();
            DayOfWeek endDow   = ce->getEndTime().getDayOfWeek();

            if (startDow != day) {
                continue;
            }

            int start = static_cast<int>(startDow);
            int end   = static_cast<int>(endDow);
            if (end <= start) {
                continue;
            }

            for (int i = start + 1; i <= end; ++i) {
                DayOfWeek target = static_cast<DayOfWeek>(i);

                DaySchedule* nextDay = schedule->getDay(target);
                if (!nextDay) {
                    continue;
                }

                const MyTime s = ce->getStartTime();
                const MyTime e = ce->getEndTime();

                MyTime newStart(s.getYear(), s.getMonth(), s.getDay(), target, s.getHour(), s.getMinute());
                MyTime newEnd(e.getYear(), e.getMonth(), e.getDay(), target, e.getHour(), e.getMinute());

                auto* cloned = new CollegeEvent(ce->getTitle(), newStart, newEnd,ce->getCategory(), ce->getIsMandatory(), ce->getNote());

                nextDay->addEvent(cloned);
            }
        }
    }

}


void SystemAlgorithm::resolveConflicts(WeekSchedule* schedule) {
    if (!schedule) {
        return;
    }

    const std::string sid = schedule->getStudentId();

    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = schedule->getDay(day);
        if (!ds) {
            continue;
        }

        auto& evs = ds->getEvents();

        std::sort(evs.begin(), evs.end(),
                  [](Event* a, Event* b) {
                      return a->getStartTime().toMinutes() < b->getStartTime().toMinutes();
                  });

        for (std::size_t i = 0; i < evs.size(); ++i) {
            for (std::size_t j = i + 1; j < evs.size(); ++j) {
                Event* e1 = evs[i];
                Event* e2 = evs[j];

                if (!e1->overlapsWith(*e2)) {
                    continue;
                }

                auto* s1 = dynamic_cast<StudentEvent*>(e1);
                auto* s2 = dynamic_cast<StudentEvent*>(e2);
                auto* c1 = dynamic_cast<CollegeEvent*>(e1);
                auto* c2 = dynamic_cast<CollegeEvent*>(e2);

                std::cout << "[Conflict] Student " << sid << " on " << dayToString(day) << ": "
                          << "'" << e1->getTitle() << "'" << " overlaps with " << "'" << e2->getTitle() << "'";

                if (c1 || c2) {
                    std::cout << " (CollegeEvent involved)";
                }
                std::cout << std::endl;
            }
        }
    }

}


std::vector<int> SystemAlgorithm::findCommonFreeSlots() const {
    std::vector<int> result;
    if (allSchedules.empty()) return result;

    for (int h = 7; h < 23; ++h) {
        bool allFree = true;

        for (WeekSchedule* ws : allSchedules) {
            if (!ws) continue;

            for (int d = 0; d < 7; ++d) {
                DayOfWeek day = static_cast<DayOfWeek>(d);
                DaySchedule* ds = ws->getDay(day);
                if (!ds) {
                    continue;
                }

                if (!ds->isSlotFree(h)) {
                    allFree = false;
                    break;
                }
            }
            if (!allFree) {
                break;
            }
        }

        if (allFree) {
            result.push_back(h);
        }
    }

    return result;
}

void SystemAlgorithm::displayCommonFreeSlots() const {
    std::vector<int> free = findCommonFreeSlots();

    std::cout << "\n=== Common Free Time ===" << std::endl;
    if (free.empty()) {
        std::cout << "No shared free time." << std::endl;
        return;
    }

    for (int h : free) {
        std::cout << h << ":00 ~ " << h + 1 << ":00" << std::endl;
    }
}