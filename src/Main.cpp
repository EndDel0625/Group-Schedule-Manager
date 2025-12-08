

#include <iostream>
#include <vector>
#include <string>

#include "DayConverter.h"
#include "MyTime.h"
#include "Event.h"
#include "StudentEvent.h"
#include "CollegeEvent.h"
#include "DaySchedule.h"
#include "WeekSchedule.h"
#include "SystemAlgorithm.h"
#include "FileInOut.h"


void testDayConverter() {
    std::cout << "\n=== [DayConverter Test] ===\n";
    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        std::cout << d << " -> " << dayToString(day) << "\n";
    }
}


void testMyTime() {
    std::cout << "\n=== [MyTime Test] ===\n";
    MyTime t1(2025, 11, 10, DayOfWeek::Monday, 9, 30);
    MyTime t2(2025, 11, 10, DayOfWeek::Monday, 12, 15);

    std::cout << "t1: ";
    t1.display();
    std::cout << "\nt2: ";
    t2.display();
    std::cout << "\nDifference (minutes): " << t1.diffMinutes(t2) << "\n";
}


void testEvent() {
    std::cout << "\n=== [Event Test] ===\n";

    MyTime s1(2025, 11, 10, DayOfWeek::Monday, 9, 0);
    MyTime e1(2025, 11, 10, DayOfWeek::Monday, 12, 0);
    MyTime s2(2025, 11, 10, DayOfWeek::Monday, 11, 0);
    MyTime e2(2025, 11, 10, DayOfWeek::Monday, 13, 0);

    Event ev1("Morning Session", s1, e1, "Base event 1");
    Event ev2("Overlap Session", s2, e2, "Base event 2");

    ev1.display();
    ev2.display();

    std::cout << "Overlaps? "
              << (ev1.overlapsWith(ev2) ? "Yes" : "No") << "\n";
}


void testStudentEvent() {
    std::cout << "\n=== [StudentEvent Test] ===\n";

    MyTime s(2025, 11, 10, DayOfWeek::Monday, 9, 30);
    MyTime e(2025, 11, 10, DayOfWeek::Monday, 12, 15);

    StudentEvent st("30088851", "CIS 25 LEC/LAB", s, e, 1, true, "Room 323");

    std::cout << "-- Before updates --\n";
    st.display();

    st.setPriority(5);
    st.setIsPrivate(false);
    st.updateNote("Changed to public, still in Room 323");

    std::cout << "\n-- After updates --\n";
    st.display();
}


void testCollegeEvent() {
    std::cout << "\n=== [CollegeEvent Test] ===\n";

    MyTime s(2025, 11, 11, DayOfWeek::Tuesday, 11, 30);
    MyTime e(2025, 11, 11, DayOfWeek::Tuesday, 13, 0);

    CollegeEvent ce("Spring Festival", s, e,
                    CollegeCategory::FESTIVAL, false, "Main Quad");

    std::cout << "-- Before updates --\n";
    ce.display();

    ce.setCategory(CollegeCategory::HOLIDAY);
    ce.setMandatory(true);
    ce.updateNote("Rescheduled as an official holiday");

    std::cout << "\n-- After updates --\n";
    ce.display();
}


void testDaySchedule() {
    std::cout << "\n=== [DaySchedule Test] ===\n";

    DaySchedule ds("30088851");

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

    std::cout << "-- Add 3 events --\n";
    ds.addEvent(ev1);
    ds.addEvent(ev2);
    ds.addEvent(ev3);
    ds.displayDaySchedule();

    std::cout << "\n-- Remove CHEM 30A --\n";
    ds.removeEvent("CHEM 30A");
    ds.displayDaySchedule();

    std::cout << "\n-- Free time slots (hour-based) --\n";
    std::vector<int> freeSlots = ds.findFreeSlots();
    for (int h : freeSlots) {
        std::cout << h << ":00 ~ " << h + 1 << ":00\n";
    }

    ds.clearEvents();
}


void testWeekScheduleInMemory() {
    std::cout << "\n=== [WeekSchedule In-Memory Test] ===\n";

    WeekSchedule week("S1");

    week.getDay(DayOfWeek::Monday)->addEvent(
        new StudentEvent("S1", "CIS 25",
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 9, 0),
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 11, 0),
                         2, false, "")
    );

    week.getDay(DayOfWeek::Wednesday)->addEvent(
        new StudentEvent("S1", "CHEM 30A",
                         MyTime(2025, 11, 12, DayOfWeek::Wednesday, 13, 0),
                         MyTime(2025, 11, 12, DayOfWeek::Wednesday, 15, 0),
                         3, false, "")
    );

    week.displayWeekSchedule();
}


WeekSchedule* buildSampleSchedule(const std::string& studentId) {
    WeekSchedule* w = new WeekSchedule(studentId);


    w->getDay(DayOfWeek::Monday)->addEvent(
        new StudentEvent(studentId, "CIS 25",
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 9, 0),
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 11, 0),
                         2, false, "Room 323")
    );


    w->getDay(DayOfWeek::Wednesday)->addEvent(
        new StudentEvent(studentId, "CHEM 30A",
                         MyTime(2025, 11, 12, DayOfWeek::Wednesday, 13, 0),
                         MyTime(2025, 11, 12, DayOfWeek::Wednesday, 15, 0),
                         3, false, "Lab")
    );


    w->getDay(DayOfWeek::Tuesday)->addEvent(
        new CollegeEvent("THANKSGIVING BREAK",
                         MyTime(2025, 11, 11, DayOfWeek::Tuesday, 0, 0),
                         MyTime(2025, 11, 13, DayOfWeek::Thursday, 23, 59),
                         CollegeCategory::VACATION, true, "No classes")
    );

    return w;
}


void testSystemAlgorithmInMemory() {
    std::cout << "\n=== [SystemAlgorithm In-Memory Test] ===\n";

    SystemAlgorithm system;
    WeekSchedule* w1 = buildSampleSchedule("S1");
    WeekSchedule* w2 = buildSampleSchedule("S2");


    w1->getDay(DayOfWeek::Monday)->addEvent(
        new CollegeEvent(
            "Spring Festival",
            MyTime(2025, 11, 10, DayOfWeek::Monday, 10, 0),
            MyTime(2025, 11, 10, DayOfWeek::Monday, 12, 0),
            CollegeCategory::FESTIVAL, true, "Opening ceremony")
    );
    w2->getDay(DayOfWeek::Monday)->addEvent(
        new StudentEvent("S2", "Part-time Job",
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 10, 30),
                         MyTime(2025, 11, 10, DayOfWeek::Monday, 12, 30),
                         3, false, "")
    );

    system.addStudentSchedule(w1);
    system.addStudentSchedule(w2);

    std::cout << "\n-- Week schedules after SystemAlgorithm setup --\n";
    w1->displayWeekSchedule();
    w2->displayWeekSchedule();

    std::cout << "\n-- Common free time (all students, all days, 07:00–22:00) --\n";
    system.displayCommonFreeSlots();

    delete w1;
    delete w2;
}


void testFileInOutSingle() {
    std::cout << "\n=== [FileInOut Single Student Test] ===\n";

    WeekSchedule* w = buildSampleSchedule("FILE_TEST");
    std::cout << "-- Original in-memory schedule --\n";
    w->displayWeekSchedule();

    saveScheduleToFile(w);

    delete w;

    WeekSchedule* loaded = loadScheduleFromFile("FILE_TEST");
    if (loaded) {
        std::cout << "\n-- Loaded schedule from file --\n";
        loaded->displayWeekSchedule();
        delete loaded;
    } else {
        std::cout << "\n[FileInOut] Failed to load schedule for FILE_TEST.\n";
    }
}

void testSystemAlgorithmFromFiles() {
    std::cout << "\n=== [SystemAlgorithm From Files Test] ===\n";

    WeekSchedule* w1 = buildSampleSchedule("F1");
    WeekSchedule* w2 = buildSampleSchedule("F2");

    w1->getDay(DayOfWeek::Friday)->addEvent(
        new StudentEvent("F1", "Work",
                         MyTime(2025, 11, 14, DayOfWeek::Friday, 9, 0),
                         MyTime(2025, 11, 14, DayOfWeek::Friday, 12, 0),
                         2, false, "")
    );
    w2->getDay(DayOfWeek::Friday)->addEvent(
        new StudentEvent("F2", "Club Meeting",
                         MyTime(2025, 11, 14, DayOfWeek::Friday, 15, 0),
                         MyTime(2025, 11, 14, DayOfWeek::Friday, 17, 0),
                         3, false, "")
    );

    saveScheduleToFile(w1);
    saveScheduleToFile(w2);

    delete w1;
    delete w2;

    std::vector<std::string> ids = {"F1", "F2"};
    SystemAlgorithm system;
    std::vector<WeekSchedule*> loaded;

    for (const auto& id : ids) {
        WeekSchedule* ws = loadScheduleFromFile(id);
        if (ws) {
            std::cout << "\n-- Loaded schedule for student " << id << " --\n";
            ws->displayWeekSchedule();
            system.addStudentSchedule(ws);
            loaded.push_back(ws);
        } else {
            std::cout << "[SystemAlgorithmFromFiles] Skipping student " << id
                      << " because schedule could not be loaded.\n";
        }
    }

    std::cout << "\n-- Common free time based on schedules loaded from files --\n";
    system.displayCommonFreeSlots();

    for (WeekSchedule* ws : loaded) {
        delete ws;
    }
}

int main() {
    // Basic class tests
    testDayConverter();
    testMyTime();
    testEvent();
    testStudentEvent();
    testCollegeEvent();
    testDaySchedule();
    testWeekScheduleInMemory();

    // Algorithm tests (in-memory & from file)
    testSystemAlgorithmInMemory();
    testFileInOutSingle();
    testSystemAlgorithmFromFiles();

    std::cout << "\n=== [All Tests Finished] ===\n";
    return 0;
}
