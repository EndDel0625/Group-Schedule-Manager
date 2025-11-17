//
// Created by 김영빈 on 10/25/25.
//

#ifndef FINAL_PROJECT_DAY_SCHEDULE_H
#define FINAL_PROJECT_DAY_SCHEDULE_H

#include <vector>
#include "Event.h"
#include "CollegeEvent.h"
#include "StudentEvent.h"
#include <string>

class DaySchedule {
    private:
        std::string studentId;
        std::vector<Event*> events;
        const int startHour = 7;
        const int endHour = 23;

    public:
        DaySchedule(const std::string& id);
        ~DaySchedule();

        void addEvent(Event* e);
        bool removeEvent(const std::string& title);
        void clearEvents();
        std::vector<Event*>& getEvents();
        const std::vector<Event*>& getEvents() const;
        bool removeEventByPointer(Event* e);

        std::vector<int> findFreeSlots() const;
        bool isSlotFree(int hour) const;

        int getEventCount() const;
        std::string getStudentId() const;
        int getStartHour() const;
        int getEndHour() const;

        void displayDaySchedule() const;
};

#endif // FINAL_PROJECT_DAY_SCHEDULE_H