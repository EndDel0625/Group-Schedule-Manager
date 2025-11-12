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
    StudentEvent study("30088851", "CIS 25 LEC/LAB", start, end, 1, true, "Room 323");

    study.display();

    study.setPriority(2);
    study.setIsPrivate(false);
    std::cout << "After updates:" << std::endl;
    study.display();
}
void testCollegeEvent() {
    std::cout << "\n=== [CollegeEvent Class Test] ===" << std::endl;

    MyTime start(11, 30);
    MyTime end(13, 0);

    CollegeEvent festival("Spring Festival", start, end,
                          CollegeCategory::FESTIVAL, false, "Main Quad");

    std::cout << "\n-- Initial Event --" << std::endl;
    festival.display();

    festival.setCategory(CollegeCategory::HOLIDAY);
    festival.setMandatory(true);
    festival.updateNote("Rescheduled to Friday");

    std::cout << "\n-- After Updates --" << std::endl;
    festival.display();
}


void testDaySchedule() {
    std::cout << "\n=== DaySchedule Class Test ===" << std::endl;

    MyTime s1(9, 0);    // CIS 25 start
    MyTime e1(12, 15);  // CIS 25 end
    MyTime s2(13, 30);  // CHEM 30A start
    MyTime e2(16, 0);   // CHEM 30A end
    MyTime s3(11, 30);  // Festival start
    MyTime e3(13, 0);   // Festival end

    std::string id = "30088851";

    StudentEvent* cis25 = new StudentEvent(id, "CIS 25 LEC/LAB", s1, e1, 1, false, "Room 323");
    StudentEvent* chem30A = new StudentEvent(id, "CHEM 30A LAB", s2, e2, 2, true, "Room 521");
    CollegeEvent* springFestival = new CollegeEvent("Spring Festival", s3, e3,
        CollegeCategory::FESTIVAL, false, "Main Quad");

    DaySchedule myDay(id);

    myDay.addEvent(cis25);
    myDay.addEvent(chem30A);
    myDay.addEvent(springFestival);

    std::cout << "\n=== [Day Schedule] ===" << std::endl;
    myDay.displayDaySchedule();

    std::cout << "\n=== [Overlap Check] ===" << std::endl;

    if (cis25->overlapsWith(*chem30A)) {
        std::cout << "CIS 25 vs CHEM 30A -> Overlap Detected" << std::endl;
    } else {
        std::cout << "CIS 25 vs CHEM 30A -> No Overlap" << std::endl;
    }
    if (cis25->overlapsWith(*springFestival)) {
        std::cout << "CIS 25 vs Festival -> Overlap Detected" << std::endl;
    } else {
        std::cout << "CIS 25 vs Festival -> No Overlap" << std::endl;
    }
    if (chem30A->overlapsWith(*springFestival)) {
        std::cout << "CHEM 30A vs Festival -> Overlap Detected" << std::endl;
    } else {
        std::cout << "CHEM 30A vs Festival -> No Overlap" << std::endl;
    }

    std::cout << "\n=== [Free Time Slots] ===" << std::endl;
    std::vector<int> freeSlots = myDay.findFreeSlots();
    for (int h : freeSlots) {
        std::cout << h << ":00 ~ " << h + 1 << ":00 is free" << std::endl;
    }

    std::cout << "\n=== [Remove Event: CHEM 30A LAB] ===" << std::endl;
    if (myDay.removeEvent("CHEM 30A LAB")) {
        std::cout << "Event 'CHEM 30A LAB' removed successfully." << std::endl;
    } else {
        std::cout << "Event not found." << std::endl;
    }
    myDay.displayDaySchedule();

    std::cout << "\n=== [After clearEvents()] ===" << std::endl;
    myDay.clearEvents();
    myDay.displayDaySchedule();
}


int main() {

    testTime();
    testEvent();
    testStudentEvent();
    testCollegeEvent();
    testDaySchedule();

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