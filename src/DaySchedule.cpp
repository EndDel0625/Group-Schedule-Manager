//
// Created by 김영빈 on 11/12/25.
//

#include <DaySchedule.h>
#include <iostream>

DaySchedule::DaySchedule(const std::string& id) : studentId(id) {
}

DaySchedule::~DaySchedule() {
    clearEvents();
}

void DaySchedule::addEvent(Event* e) {
    events.push_back(e);
}

bool DaySchedule::removeEvent(const std::string &title) {
    for (auto it = events.begin(); it != events.end(); ) {
        if ((*it)->getTitle() == title) {
            delete *it;
            it = events.erase(it);
            return true;
        } else {
            ++it;
        }
    }
    return false;
}


void DaySchedule::clearEvents() {
    for (auto* e : events) delete e;
    events.clear();
}

std::vector<Event*>& DaySchedule::getEvents() {
    return events;
}

const std::vector<Event*>& DaySchedule::getEvents() const {
    return events;
}

bool DaySchedule::removeEventByPointer(Event* e) {
    for (auto it = events.begin(); it != events.end(); ++it) {
        if (*it == e) {
            delete *it;
            events.erase(it);
            return true;
        }
    }
    return false;
}


std::vector<int> DaySchedule::findFreeSlots() const {
    std::vector<int> freeHour;
    for (int h = startHour; h < endHour; ++h) {
        if (isSlotFree(h)) {
            freeHour.push_back(h);
        }
    }
    return freeHour;
}

bool DaySchedule::isSlotFree(int hour) const {
    MyTime chkStart(0, 0, 0, DayOfWeek::Monday, hour, 0);
    MyTime chkEnd  (0, 0, 0, DayOfWeek::Monday, hour + 1, 0);

    for (auto* e : events) {
        if (!(e->getEndTime().toMinutes() <= chkStart.toMinutes() ||
              e->getStartTime().toMinutes() >= chkEnd.toMinutes())) {
            return false;
              }
    }
    return true;
}

int DaySchedule::getEventCount() const {
    return static_cast<int>(events.size());
}
std::string DaySchedule::getStudentId() const {
    return studentId;
}
int DaySchedule::getStartHour() const {
    return startHour;
}
int DaySchedule::getEndHour() const {
    return endHour;
}

void DaySchedule::displayDaySchedule() const {
    for (auto* e : events) {
        e->display();
    }
}
