//
// Created by 김영빈 on 10/20/25.
//
#include <iostream>
#include "SystemAlgorithm.h"
#include "StudentEvent.h"
#include "CollegeEvent.h"
#include "FileInOut.h"


void testTime() {
    std::cout << "\n=== Time Class Test ===" << std::endl;
    MyTime t1(9, 30);
    MyTime t2(12, 15);

    std::cout << "Start: ";
    t1.display();
    std::cout << ", End: ";
    t2.display();
    std::cout << std::endl;

    std::cout << "Difference: " << t1.diffMinutes(t2) << " minutes" << std::endl;
    std::cout << "Is t2 after t1? " << (t2.isAfter(t1) ? "Yes" : "No") << std::endl;
}

void testEvent() {
    std::cout << "\n=== Event Class Test ===" << std::endl;
    MyTime s1(9, 0), e1(12, 15);
    MyTime s2(13, 30), e2(16, 20);

    Event evnt1("CIS 25 LEC/LAB", s1, e1);
    Event evnt2("CHEM 30A LAB", s2, e2);

    evnt1.display();
    evnt2.display();

    std::cout << "Do events overlap? "
              << (evnt1.overlapsWith(evnt2) ? "Yes" : "No") << std::endl;
}

void testStudentEvent() {
    std::cout << "\n=== StudentEvent Class Test ===" << std::endl;
    MyTime start(9, 30), end(12, 15);
    StudentEvent study("30088851", "CIS 25 LEC/LAB", start, end, 1, true, "");

    study.display();

    study.setPriority(2);
    study.setIsPrivate(false);
    std::cout << "After updates:" << std::endl;
    study.display();
}

int main() {

    testTime();
    testEvent();
    testStudentEvent();

    return 0;



/*
    std::cout << "=== Schedule Manager ===" << std::endl;

    std::string studentId;
    std::cout << "Enter your student ID: ";
    std::cin >> studentId;

    WeekSchedule* week = new WeekSchedule(studentId);

    int numEvents;
    std::cout << "How many events do you want to add? ";
    std::cin >> numEvents;

    for (int i = 0; i < numEvents; ++i) {
        std::string title;
        int day, sh, sm, eh, em, priority;
        char privChar;
        bool isPrivate;

        std::cout << "\n=== Event " << i + 1 << " ===" << std::endl;
        std::cout << "Title: ";
        std::getline(std::cin, title);

        std::cout << "Day of week (0=Mon, 6=Sun): ";
        std::cin >> day;

        std::cout << "Start time (hour minute): ";
        std::cin >> sh >> sm;

        std::cout << "End time (hour minute): ";
        std::cin >> eh >> em;

        std::cout << "Priority (1=high, 5=low): ";
        std::cin >> priority;

        std::cout << "Is this event private? (y/n): ";
        std::cin >> privChar;
        isPrivate = (privChar == 'y' || privChar == 'Y');

        Time start(sh, sm);
        Time end(eh, em);

        StudentEvent* newEvent = new StudentEvent(i + 1, title, start, end, priority, isPrivate);
        week->getDay(static_cast<DayOfWeek>(day))->addEvent(newEvent);
    }

    system.findCommonFreeSlots();
    system.displayCommonFreeSlots();

    return 0;
*/

}