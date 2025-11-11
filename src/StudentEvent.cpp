//
// Created by 김영빈 on 11/10/25.
//

#include "StudentEvent.h"
#include <iostream>

StudentEvent::StudentEvent(std::string id, const std::string &title, const MyTime &start,
                            const MyTime &end, int p, bool priv, const std::string &note)
    : Event(title, start, end), id(id), priority(p), isPrivate(priv) {
    this->updateNote(note);
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
    priority = p;
}
void StudentEvent::setIsPrivate(bool priv) {
    isPrivate = priv;
}

void StudentEvent::display() const {
    std::cout << "[StudentEvent] ID: " << id
              << " | Title: " << getTitle()
              << " | Priority: " << priority
              << " | Private: " << (isPrivate ? "Yes" : "No") << " | ";
    getStartTime().display();
    std::cout << " - ";
    getEndTime().display();
    if (!getNote().empty()) std::cout << " | Note: " << getNote();
    std::cout << std::endl;
}