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

            // If multi-day spreads across days (e.g., Mon -> Thu)
            int start = ce->getStartTime().getDay();
            int end   = ce->getEndTime().getDay();
            if (end <= start) continue;

            // Clone into remaining days
            for (int i = start + 1; i <= end; i++) {
                DaySchedule* nextDay = schedule->getDay(static_cast<DayOfWeek>(i));
                nextDay->addEvent(new CollegeEvent(*ce));
            }
        }
    }
}

void SystemAlgorithm::resolveConflicts(WeekSchedule* schedule) {
    for (int d = 0; d < 7; d++) {
        DaySchedule* day = schedule->getDay(static_cast<DayOfWeek>(d));
        auto& events = day->getEvents();

        for (int i = 0; i < (int)events.size(); i++) {
            for (int j = i + 1; j < (int)events.size(); j++) {
                Event* a = events[i];
                Event* b = events[j];

                if (!a->overlapsWith(*b)) continue;

                CollegeEvent* ca = dynamic_cast<CollegeEvent*>(a);
                CollegeEvent* cb = dynamic_cast<CollegeEvent*>(b);

                // If neither is mandatory → do nothing
                if (!(ca && ca->getIsMandatory()) && !(cb && cb->getIsMandatory()))
                    continue;

                // Mandatory resolution
                Event* removeTarget;
                if (ca && ca->getIsMandatory()) removeTarget = b;
                else removeTarget = a;

                std::cout << "[Conflict resolved] Mandatory event prioritized -> removed: "
                          << removeTarget->getTitle() << "\n";

                day->removeEventByPointer(removeTarget);
                j--; // Reset index after erase
            }
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