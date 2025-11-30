//
// Created by 김영빈 on 11/10/25.
//

#include "Event.h"
#include <iostream>


Event::Event(const std::string& t, const MyTime& s, const MyTime& e, const std::string& n)
    : title(t), startTime(s), endTime(e), note(n) {
}


std::string Event::getTitle() const {
    return title;
}
MyTime Event::getStartTime() const {
    return startTime;
}
MyTime Event::getEndTime() const {
    return endTime;
}
std::string Event::getNote() const {
    return note;
}

void Event::updateTitle(const std::string &newTitle) {
    title = newTitle;
}
void Event::updateTime(const MyTime &newStart, const MyTime &newEnd) {
    startTime = newStart;
    endTime = newEnd;
    if (endTime.toMinutes() < startTime.toMinutes()) {
        MyTime tmp = startTime;
        startTime = endTime;
        endTime = tmp;
    }
}
void Event::updateNote(const std::string &newNote) {
    note = newNote;
}

int Event::getDurationMinutes() const {
    return endTime.toMinutes() - startTime.toMinutes();
}

bool Event::overlapsWith(const Event& other) const {
    return !(endTime.toMinutes() <= other.startTime.toMinutes() ||
            startTime.toMinutes() >= other.endTime.toMinutes());
}


void Event::display() const {
    std::cout << "[Event] " << title;
    if (!note.empty()) std::cout << " | Note: " << note;
    std::cout << " | ";
    startTime.display();
    std::cout << " - ";
    endTime.display();
    std::cout << std::endl;
}