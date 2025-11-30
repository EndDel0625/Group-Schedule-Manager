//
// Created by 김영빈 on 10/20/25.
//
#include <iostream>
#include "SystemAlgorithm.h"
#include "StudentEvent.h"
#include "CollegeEvent.h"
#include "DaySchedule.h"
#include "FileInOut.h"


void testTime() {
    std::cout << "\n=== [Time Class Test] ===" << std::endl;
    MyTime t1(2025, 11, 10, DayOfWeek::Monday, 9, 30);
    MyTime t2(2025, 11, 10, DayOfWeek::Monday, 12, 15);

    std::cout << "Start: ";
    t1.display();
    std::cout << ", End: ";
    t2.display();
    std::cout << "\nDifference: " << t1.diffMinutes(t2) << " minutes" << std::endl;
}

void testEvent() {
    std::cout << "\n=== [Event Class Test] ===" << std::endl;
    MyTime s1(2025, 11, 10, DayOfWeek::Monday, 9, 0);
    MyTime e1(2025, 11, 10, DayOfWeek::Monday, 12, 15);
    MyTime s2(2025, 11, 10, DayOfWeek::Monday, 13, 30);
    MyTime e2(2025, 11, 10, DayOfWeek::Monday, 16, 20);

    Event ev1("CIS 25 LEC/LAB", s1, e1, "");
    Event ev2("CHEM 30A LAB", s2, e2, "");

    ev1.display();
    ev2.display();
}

void testStudentEvent() {
    std::cout << "\n=== [StudentEvent Class Test] ===" << std::endl;
    MyTime start(2025, 11, 10, DayOfWeek::Monday, 9, 30);
    MyTime end(2025, 11, 10, DayOfWeek::Monday, 12, 15);

    StudentEvent st("30088851", "CIS 25 LEC/LAB", start, end, 1, true, "Room 323");
    st.display();

    st.setPriority(5);
    st.setIsPrivate(false);
    std::cout << "\nAfter updates:\n";
    st.display();
}

void testCollegeEvent() {
    std::cout << "\n=== [CollegeEvent Class Test] ===" << std::endl;
    MyTime start(2025, 11, 10, DayOfWeek::Monday, 11, 30);
    MyTime end(2025, 11, 10, DayOfWeek::Monday, 13, 0);

    CollegeEvent ce("Spring Festival", start, end,
                    CollegeCategory::FESTIVAL, false, "Main Quad");

    std::cout << "\n-- Before Updates --" << std::endl;
    ce.display();

    ce.setCategory(CollegeCategory::HOLIDAY);
    ce.setMandatory(true);
    ce.updateNote("Rescheduled");

    std::cout << "\n-- After Updates --" << std::endl;
    ce.display();
}

void testDaySchedule() {
    std::cout << "\n=== [DaySchedule Class Test] ===" << std::endl;

    MyTime s1(2025, 11, 10, DayOfWeek::Monday, 9, 0);
    MyTime e1(2025, 11, 10, DayOfWeek::Monday, 12, 15);
    MyTime s2(2025, 11, 10, DayOfWeek::Monday, 13, 30);
    MyTime e2(2025, 11, 10, DayOfWeek::Monday, 16, 0);
    MyTime s3(2025, 11, 10, DayOfWeek::Monday, 11, 30);
    MyTime e3(2025, 11, 10, DayOfWeek::Monday, 13, 0);

    StudentEvent* ev1 = new StudentEvent("30088851", "CIS 25", s1, e1, 1, false, "");
    StudentEvent* ev2 = new StudentEvent("30088851", "CHEM 30A", s2, e2, 2, true, "");
    CollegeEvent* ev3 = new CollegeEvent("Spring Festival", s3, e3,
        CollegeCategory::FESTIVAL, false, "");

    DaySchedule ds("30088851");
    ds.addEvent(ev1);
    ds.addEvent(ev2);
    ds.addEvent(ev3);

    ds.displayDaySchedule();

    std::cout << "\n-- Remove CHEM 30A --" << std::endl;
    ds.removeEvent("CHEM 30A");
    ds.displayDaySchedule();

    std::cout << "\n-- Free Time --" << std::endl;
    for (int h : ds.findFreeSlots())
        std::cout << h << ":00 ~ " << h + 1 << ":00\n";

    ds.clearEvents();
}

void testSystemAlgorithmAndWeekScheduleTest() {
    std::cout << "\n=== [SystemAlgorithm & WeekSchedule Test] ===" << std::endl;

    SystemAlgorithm system;

    WeekSchedule* w1 = new WeekSchedule("S1");
    WeekSchedule* w2 = new WeekSchedule("S2");

    w1->getDay(DayOfWeek::Monday)->addEvent(
    new CollegeEvent(
        "Spring Festival",
        MyTime(2025, 11, 10, DayOfWeek::Monday, 10, 0),
        MyTime(2025, 11, 10, DayOfWeek::Monday, 12, 0),
        CollegeCategory::FESTIVAL,true,"Main Quad – Opening Ceremony")
);

    w2->getDay(DayOfWeek::Monday)->addEvent(
        new StudentEvent("S2", "Part time Job",
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 10, 30),
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 12, 30),
                         3, false, "")
    );

    w1->getDay(DayOfWeek::Tuesday)->addEvent(
        new CollegeEvent("VACATION",
                         MyTime(2025, 11, 11, DayOfWeek::Tuesday, 9, 0),
                         MyTime(2025, 11, 13, DayOfWeek::Thursday, 18, 0),
                         CollegeCategory::VACATION, false, "")
    );

    system.addStudentSchedule(w1);
    system.addStudentSchedule(w2);

    std::cout << "\n-- Weekly Schedules --" << std::endl;
    w1->displayWeekSchedule();
    w2->displayWeekSchedule();

    std::cout << "\n-- Common Free Time --" <<std::endl;
    system.displayCommonFreeSlots();

    delete w1;
    delete w2;
}

int main() {
    testTime();
    testEvent();
    testStudentEvent();
    testCollegeEvent();
    testDaySchedule();
    testSystemAlgorithmAndWeekScheduleTest();

    std::cout << "\n=== [All Tests Complete] ===" << std::endl;
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