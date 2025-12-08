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
    if (e == nullptr) {
        return;
    }
    events.push_back(e);
}

bool DaySchedule::removeEvent(const std::string& title) {
    for (auto it = events.begin(); it != events.end(); ++it) {
        if ((*it)->getTitle() == title) {
            delete *it;
            events.erase(it);
            return true;
        }
    }
    return false;
}


void DaySchedule::clearEvents() {
    for (auto* e : events) {
        delete e;
    }
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
    std::vector<int> freeSlots;
    for (int h = startHour; h < endHour; ++h) {
        if (isSlotFree(h)) {
            freeSlots.push_back(h);
        }
    }
    return freeSlots;
}

bool DaySchedule::isSlotFree(int hour) const {
    int slotStart = hour * 60;
    int slotEnd = (hour + 1) * 60;

    for (Event* e : events) {
        int eStart = e->getStartTime().toMinutes();
        int eEnd   = e->getEndTime().toMinutes();

        if (!(eEnd <= slotStart || eStart >= slotEnd)) {
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
