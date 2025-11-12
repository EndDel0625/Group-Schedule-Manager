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
    MyTime checkStart(hour, 0);
    MyTime checkEnd(hour + 1, 0);
    for (auto* e : events) {
        if (!(e->getEndTime().toMinutes() <= checkStart.toMinutes() || e->getStartTime().toMinutes() >= checkEnd.toMinutes())) {
            return false;
              }
    }
    return true;
}

int DaySchedule::getEventCount() const {
    return (int)events.size();
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
    for (auto* e : events) e->display();
}
