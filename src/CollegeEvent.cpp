//
// Created by 김영빈 on 11/11/25.
//

#include "CollegeEvent.h"
#include <iostream>

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
    std::cout << "[CollegeEvent] " << getTitle() << " | Category: ";
    switch (category) {
        case CollegeCategory::FESTIVAL:
            std::cout << "FESTIVAL";
            break;
        case CollegeCategory::PROFESSOR_DAYOFF:
            std::cout << "PROFESSOR_DAYOFF";
            break;
        case CollegeCategory::UNKNOWN:
            std::cout << "UNKNOWN";
            break;
        case CollegeCategory::HOLIDAY:
            std::cout << "HOLIDAY";
            break;
        case CollegeCategory::VACATION:
            std::cout << "VACATION";
            break;
    }

    std::cout << " | Mandatory: ";
    if (isMandatory)
        std::cout << "Yes";
    else
        std::cout << "No";

    if (!getNote().empty()) std::cout << " | Note: " << getNote();

    std::cout <<  " | ";
    getStartTime().display();
    std::cout << " - ";
    getEndTime().display();
    std::cout << std::endl;
}
