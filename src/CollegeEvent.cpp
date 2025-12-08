//
// Created by 김영빈 on 11/11/25.
//

#include "CollegeEvent.h"
#include <iostream>

static std::string collegeCategoryToString(CollegeCategory cat) {
    switch (cat) {
        case CollegeCategory::HOLIDAY:
            return "Holiday";
        case CollegeCategory::PROFESSOR_DAYOFF:
            return "Professor Day Off";
        case CollegeCategory::FESTIVAL:
            return "Festival";
        case CollegeCategory::VACATION:
            return "Vacation";
        case CollegeCategory::UNKNOWN:
                return "Unknown";
    }
    return "Unknown";
}

CollegeEvent::CollegeEvent(const std::string &title, const MyTime &start,
    const MyTime &end, CollegeCategory cat, bool mandatory, const std::string &note)
        :Event(title,start,end,note), category(cat), isMandatory(mandatory) {
}

void CollegeEvent::setCategory(CollegeCategory cat) {
    category = cat;
}
void CollegeEvent::setMandatory(bool mand) {
    isMandatory = mand;
}

CollegeCategory CollegeEvent::getCategory() const {
    return category;
}
bool CollegeEvent::getIsMandatory() const {
    return isMandatory;
}

void CollegeEvent::display() const {
    std::cout << "[CollegeEvent] Title: " << title
    << " | Category: " << collegeCategoryToString(category)
    << " | Mandatory: " << (isMandatory ? "Yes" : "No");

    if (!note.empty()) {
        std::cout << " | Note: " << note;
    }

    std::cout << " | ";
    startTime.display();
    std::cout << " - ";
    endTime.display();
    std::cout << std::endl;

}

