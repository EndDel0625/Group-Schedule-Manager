//
// Created by 김영빈 on 11/16/25.
//

#include "SystemAlgorithm.h"
#include <iostream>


void SystemAlgorithm::addStudentSchedule(WeekSchedule* schedule) {
    distributeMultiDayEvents(schedule);
    resolveConflicts(schedule);
    allSchedules.push_back(schedule);
}

void SystemAlgorithm::distributeMultiDayEvents(WeekSchedule* schedule) {
    for (int d = 0; d < 7; d++) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = schedule->getDay(day);
        std::vector<Event*> copy = ds->getEvents();

        for (Event* ev : copy) {
            CollegeEvent* ce = dynamic_cast<CollegeEvent*>(ev);
            if (!ce) continue;

            DayOfWeek startDow = ce->getStartTime().getDayOfWeek();
            DayOfWeek endDow   = ce->getEndTime().getDayOfWeek();

            int start = static_cast<int>(startDow);
            int end   = static_cast<int>(endDow);
            if (end <= start) continue;

            for (int i = start + 1; i <= end; ++i) {
                DayOfWeek target = static_cast<DayOfWeek>(i);
                DaySchedule* nextDay = schedule->getDay(target);
                if (nextDay) {
                    nextDay->addEvent(new CollegeEvent(*ce));
                }
            }
        }
    }
}


void SystemAlgorithm::resolveConflicts(WeekSchedule* schedule) {
    for (int d = 0; d < 7; d++) {
        DaySchedule* day = schedule->getDay(static_cast<DayOfWeek>(d));
        auto& events = day->getEvents();

        std::vector<Event*> removeList;

        for (int i = 0; i < (int)events.size(); i++) {
            for (int j = i + 1; j < (int)events.size(); j++) {
                Event* a = events[i];
                Event* b = events[j];

                if (!a->overlapsWith(*b)) continue;

                CollegeEvent* ca = dynamic_cast<CollegeEvent*>(a);
                CollegeEvent* cb = dynamic_cast<CollegeEvent*>(b);

                if (ca && ca->getIsMandatory() && !cb) {
                    removeList.push_back(b);
                }
                else if (cb && cb->getIsMandatory() && !ca) {
                    removeList.push_back(a);
                }
                else if (ca && cb && ca->getIsMandatory() && cb->getIsMandatory()) {
                    removeList.push_back(b);   // delete the later-added event
                }
            }
        }

        for (Event* e : removeList) {
            day->removeEventByPointer(e);
        }
    }
}


std::vector<int> SystemAlgorithm::findCommonFreeSlots() const {
    std::vector<int> result;
    if (allSchedules.empty()) return result;

    for (int h = 7; h < 23; h++) {
        bool allFree = true;
        for (WeekSchedule* ws : allSchedules) {
            for (int d = 0; d < 7; d++) {
                if (!ws->getDay(static_cast<DayOfWeek>(d))->isSlotFree(h)) {
                    allFree = false;
                    break;
                }
            }
            if (!allFree) break;
        }
        if (allFree) result.push_back(h);
    }
    return result;
}

void SystemAlgorithm::displayCommonFreeSlots() const {
    std::vector<int> free = findCommonFreeSlots();
    std::cout << "\n=== Common Free Time ===\n";
    if (free.empty()) {
        std::cout << "No shared free time.\n";
        return;
    }
    for (int h : free) std::cout << h << ":00 ~ " << h + 1 << ":00\n";
}