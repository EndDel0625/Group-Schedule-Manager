//
// Created by 김영빈 on 11/10/25.
//

#include "StudentEvent.h"
#include <iostream>

StudentEvent::StudentEvent(std::string id, const std::string &title, const MyTime &start,
                            const MyTime &end, int p, bool priv, const std::string &note)
    : Event(title, start, end, note), id(id), priority(p), isPrivate(priv) {
    if (priority < 1) {
        priority = 1;
    }
    if (priority > 5) {
        priority = 5;
    }
}

std::string StudentEvent::getId() const {
    return id;
}
int StudentEvent::getPriority() const {
    return priority;
}
bool StudentEvent::getIsPrivate() const {
    return isPrivate;
}

void StudentEvent::setPriority(int p) {
    if (p < 1) p = 1;
    if (p > 5) p = 5;
    priority = p;
}
void StudentEvent::setIsPrivate(bool priv) {
    isPrivate = priv;
}

void StudentEvent::display() const {
    std::cout << "[StudentEvent] ID: " << id
              << " | Title: " << title
              << " | Priority: " << priority   // ⭐ 1~5로 표시
              << " | Private: " << (isPrivate ? "Yes" : "No");

    if (!note.empty()) std::cout << " | Note: " << note;

    std::cout << " | ";
    startTime.display();
    std::cout << " - ";
    endTime.display();
    std::cout << std::endl;
}