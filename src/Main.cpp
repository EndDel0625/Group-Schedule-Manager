
/*
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
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <limits>

#include "SystemAlgorithm.h"
#include "StudentEvent.h"
#include "CollegeEvent.h"
#include "DaySchedule.h"
#include "FileInOut.h"

static const std::string STUDENT_LIST_FILE = "students.txt";

bool fileExists(const std::string& filename) {
    std::ifstream ifs(filename.c_str());
    return static_cast<bool>(ifs);
}

std::vector<std::string> loadAllStudentIds() {
    std::vector<std::string> ids;
    std::ifstream ifs(STUDENT_LIST_FILE.c_str());

    if (!ifs) {
        return ids;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            ids.push_back(line);
        }
    }

    return ids;
}

bool studentIdExists(const std::string& id) {
    std::vector<std::string> ids = loadAllStudentIds();

    std::vector<std::string>::iterator it =
        std::find(ids.begin(), ids.end(), id);

    return it != ids.end();
}

void addStudentId(const std::string& id) {
    if (studentIdExists(id)) {
        return;
    }

    std::ofstream ofs(STUDENT_LIST_FILE.c_str(), std::ios::app);
    if (!ofs) {
        return;
    }

    ofs << id << "\n";
}

void removeStudentId(const std::string& id) {
    std::vector<std::string> ids = loadAllStudentIds();

    ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());

    std::ofstream ofs(STUDENT_LIST_FILE.c_str());
    if (!ofs) {
        return;
    }

    for (std::size_t i = 0; i < ids.size(); ++i) {
        ofs << ids[i] << "\n";
    }
}

void clearCinLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

DayOfWeek inputDayOfWeek() {
    int d;
    std::cout << "Select day (1=Mon ... 7=Sun): ";
    std::cin >> d;

    if (d < 1) {
        d = 1;
    }
    if (d > 7) {
        d = 7;
    }

    return static_cast<DayOfWeek>(d - 1);
}

void inputDateTimeRange(DayOfWeek& dow, MyTime& start, MyTime& end) {
    int year;
    int month;
    int day;

    int sh;
    int sm;
    int eh;
    int em;

    dow = inputDayOfWeek();

    std::cout << "Year Month Day (e.g. 2025 11 10): ";
    std::cin >> year >> month >> day;

    std::cout << "Start time (hour minute, 24h, e.g. 9 0): ";
    std::cin >> sh >> sm;

    std::cout << "End time (hour minute, 24h, e.g. 11 0): ";
    std::cin >> eh >> em;

    start = MyTime(year, month, day, dow, sh, sm);
    end   = MyTime(year, month, day, dow, eh, em);
}

bool studentTakesCourse(WeekSchedule* week, const std::string& courseTitle) {
    if (week == nullptr) {
        return false;
    }

    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = week->getDay(day);

        if (ds == nullptr) {
            continue;
        }

        const std::vector<Event*>& evs = ds->getEvents();
        for (std::size_t i = 0; i < evs.size(); ++i) {
            StudentEvent* se = dynamic_cast<StudentEvent*>(evs[i]);
            if (se == nullptr) {
                continue;
            }
            if (se->getTitle() == courseTitle) {
                return true;
            }
        }
    }

    return false;
}

void attachCollegeEventsToWeek(WeekSchedule* week,
                               const std::vector<CollegeEvent*>& collegeEvents) {
    if (week == nullptr) {
        return;
    }

    for (std::size_t idx = 0; idx < collegeEvents.size(); ++idx) {
        CollegeEvent* ce = collegeEvents[idx];
        if (ce == nullptr) {
            continue;
        }

        if (ce->getCategory() == CollegeCategory::PROFESSOR_DAYOFF) {
            std::string courseTitle = ce->getTitle();
            if (!studentTakesCourse(week, courseTitle)) {
                continue;
            }
        }

        MyTime s = ce->getStartTime();
        MyTime e = ce->getEndTime();
        DayOfWeek dow = s.getDayOfWeek();

        DaySchedule* ds = week->getDay(dow);
        if (ds == nullptr) {
            continue;
        }

        CollegeEvent* cloned = new CollegeEvent(
            ce->getTitle(),
            s,
            e,
            ce->getCategory(),
            ce->getIsMandatory(),
            ce->getNote()
        );

        ds->addEvent(cloned);
    }
}

void printWeekCalendar(const WeekSchedule* week) {
    if (week == nullptr) {
        return;
    }

    const int startHour = 7;
    const int endHour   = 23;

    const char* dayNames[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

    std::cout << "\n" << std::setw(6) << " ";
    for (int d = 0; d < 7; ++d) {
        std::cout << "|" << std::setw(5) << dayNames[d] << " ";
    }
    std::cout << "|\n";

    for (int h = startHour; h <= endHour; ++h) {
        std::cout << std::setfill('0') << std::setw(2) << h << ":00 ";
        std::cout << std::setfill(' ');

        for (int d = 0; d < 7; ++d) {
            DayOfWeek day = static_cast<DayOfWeek>(d);
            DaySchedule* ds =
                const_cast<WeekSchedule*>(week)->getDay(day);

            bool busy = false;
            if (ds != nullptr) {
                busy = !(ds->isSlotFree(h));
            }

            const char* cell;
            if (busy) {
                cell = "X";
            } else {
                cell = ".";
            }

            std::cout << "|" << std::setw(5) << cell << " ";
        }
        std::cout << "|\n";
    }
}

void addStudentEventToWeek(WeekSchedule* week) {
    if (week == nullptr) {
        return;
    }

    clearCinLine();

    std::string title;
    std::cout << "Event title: ";
    std::getline(std::cin, title);

    std::string note;
    std::cout << "Note (one line, can be empty): ";
    std::getline(std::cin, note);

    DayOfWeek dow;
    MyTime start;
    MyTime end;
    inputDateTimeRange(dow, start, end);

    int priority;
    std::cout << "Priority (1-5, default 3): ";
    std::cin >> priority;
    if (priority < 1) {
        priority = 1;
    }
    if (priority > 5) {
        priority = 5;
    }

    int privInt;
    std::cout << "Private? (0 = no, 1 = yes): ";
    std::cin >> privInt;
    bool isPrivate = (privInt != 0);

    StudentEvent* se = new StudentEvent(
        week->getStudentId(),
        title,
        start,
        end,
        priority,
        isPrivate,
        note
    );

    DaySchedule* ds = week->getDay(dow);
    if (ds != nullptr) {
        ds->addEvent(se);
    } else {
        delete se;
    }
}

StudentEvent* chooseStudentEvent(WeekSchedule* week) {
    if (week == nullptr) {
        return nullptr;
    }

    std::vector<StudentEvent*> list;

    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = week->getDay(day);
        if (ds == nullptr) {
            continue;
        }

        std::vector<Event*>& evs = ds->getEvents();
        for (std::size_t i = 0; i < evs.size(); ++i) {
            StudentEvent* se = dynamic_cast<StudentEvent*>(evs[i]);
            if (se != nullptr) {
                list.push_back(se);
            }
        }
    }

    if (list.empty()) {
        std::cout << "No student events.\n";
        return nullptr;
    }

    std::cout << "\nStudent events:\n";
    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << (i + 1) << ") ";
        list[i]->display();
    }

    std::cout << "Select event number (0 = cancel): ";
    std::size_t idx;
    std::cin >> idx;

    if (idx == 0 || idx > list.size()) {
        return nullptr;
    }

    return list[idx - 1];
}

void editStudentEventInWeek(WeekSchedule* week) {
    StudentEvent* se = chooseStudentEvent(week);
    if (se == nullptr) {
        return;
    }

    while (true) {
        std::cout << "\nEditing event:\n";
        se->display();
        std::cout << "1. Change title\n";
        std::cout << "2. Change time (same day)\n";
        std::cout << "3. Change note\n";
        std::cout << "4. Change priority\n";
        std::cout << "5. Toggle private\n";
        std::cout << "0. Done\n";

        int ch;
        std::cin >> ch;

        if (ch == 0) {
            break;
        }

        clearCinLine();

        if (ch == 1) {
            std::string title;
            std::cout << "New title: ";
            std::getline(std::cin, title);
            se->updateTitle(title);
        } else if (ch == 2) {
            MyTime s = se->getStartTime();
            MyTime e = se->getEndTime();

            int sh;
            int sm;
            int eh;
            int em;

            std::cout << "New start time (hour minute): ";
            std::cin >> sh >> sm;
            std::cout << "New end time (hour minute): ";
            std::cin >> eh >> em;

            MyTime newStart(
                s.getYear(), s.getMonth(), s.getDay(),
                s.getDayOfWeek(), sh, sm
            );
            MyTime newEnd(
                e.getYear(), e.getMonth(), e.getDay(),
                e.getDayOfWeek(), eh, em
            );

            se->updateTime(newStart, newEnd);
        } else if (ch == 3) {
            std::string note;
            std::cout << "New note: ";
            std::getline(std::cin, note);
            se->updateNote(note);
        } else if (ch == 4) {
            int p;
            std::cout << "New priority (1-5): ";
            std::cin >> p;
            se->setPriority(p);
        } else if (ch == 5) {
            bool nowPrivate = !se->getIsPrivate();
            se->setIsPrivate(nowPrivate);
        }
    }
}

void deleteStudentEventFromWeek(WeekSchedule* week) {
    StudentEvent* target = chooseStudentEvent(week);
    if (target == nullptr) {
        return;
    }

    bool removed = false;

    for (int d = 0; d < 7 && !removed; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        DaySchedule* ds = week->getDay(day);
        if (ds == nullptr) {
            continue;
        }
        if (ds->removeEventByPointer(target)) {
            removed = true;
        }
    }

    if (removed) {
        std::cout << "Event deleted.\n";
    } else {
        std::cout << "Failed to delete event.\n";
    }
}

void addNewStudentFlow() {
    std::string id;
    std::cout << "New student ID: ";
    std::cin >> id;

    if (studentIdExists(id)) {
        std::cout << "Student ID already exists.\n";
        return;
    }

    WeekSchedule* w = new WeekSchedule(id);
    saveScheduleToFile(w);
    addStudentId(id);
    delete w;

    std::cout << "Student created.\n";
}

void manageExistingStudentFlow() {
    std::string id;
    std::cout << "Student ID: ";
    std::cin >> id;

    if (!studentIdExists(id)) {
        std::cout << "Student ID does not exist.\n";
        return;
    }

    WeekSchedule* w = loadScheduleFromFile(id);
    if (w == nullptr) {
        std::cout << "Could not load schedule for this student.\n";
        return;
    }

    std::vector<CollegeEvent*> collegeEvents =
        loadCollegeEventsFromFile("college_events.txt");

    attachCollegeEventsToWeek(w, collegeEvents);

    while (true) {
        std::cout << "\n=== Manage Student " << id << " ===\n";
        std::cout << "1. Show weekly schedule (calendar)\n";
        std::cout << "2. Add event\n";
        std::cout << "3. Edit event\n";
        std::cout << "4. Delete event\n";
        std::cout << "0. Save and return\n";

        int ch;
        std::cin >> ch;
        if (ch == 0) {
            break;
        }

        switch (ch) {
            case 1:
                printWeekCalendar(w);
                break;
            case 2:
                addStudentEventToWeek(w);
                break;
            case 3:
                editStudentEventInWeek(w);
                break;
            case 4:
                deleteStudentEventFromWeek(w);
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }

    saveScheduleToFile(w);

    for (std::size_t i = 0; i < collegeEvents.size(); ++i) {
        delete collegeEvents[i];
    }
    delete w;
}

void deleteStudentFlow() {
    std::string id;
    std::cout << "Student ID to delete: ";
    std::cin >> id;

    if (!studentIdExists(id)) {
        std::cout << "Student ID does not exist.\n";
        return;
    }

    std::string filename = "schedule_" + id + ".txt";
    if (fileExists(filename)) {
        std::remove(filename.c_str());
    }

    removeStudentId(id);
    std::cout << "Student deleted.\n";
}

void runStudentMenu() {
    while (true) {
        std::cout << "\n=== Student Management ===\n";
        std::cout << "1. Add new student\n";
        std::cout << "2. Manage existing student\n";
        std::cout << "3. Delete student\n";
        std::cout << "0. Back\n";

        int ch;
        std::cin >> ch;

        if (ch == 0) {
            break;
        }

        if (ch == 1) {
            addNewStudentFlow();
        } else if (ch == 2) {
            manageExistingStudentFlow();
        } else if (ch == 3) {
            deleteStudentFlow();
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

CollegeCategory inputCollegeCategory() {
    std::cout << "Category: 1=HOLIDAY, 2=PROFESSOR_DAYOFF, 3=FESTIVAL, 4=VACATION, 5=UNKNOWN: ";
    int c;
    std::cin >> c;

    if (c == 1) {
        return CollegeCategory::HOLIDAY;
    } else if (c == 2) {
        return CollegeCategory::PROFESSOR_DAYOFF;
    } else if (c == 3) {
        return CollegeCategory::FESTIVAL;
    } else if (c == 4) {
        return CollegeCategory::VACATION;
    } else {
        return CollegeCategory::UNKNOWN;
    }
}

void showCollegeCalendar(const std::vector<CollegeEvent*>& events) {
    WeekSchedule* w = new WeekSchedule("COLLEGE");

    for (std::size_t i = 0; i < events.size(); ++i) {
        CollegeEvent* ce = events[i];
        if (ce == nullptr) {
            continue;
        }

        MyTime s = ce->getStartTime();
        MyTime e = ce->getEndTime();
        DayOfWeek dow = s.getDayOfWeek();

        CollegeEvent* clone = new CollegeEvent(
            ce->getTitle(),
            s,
            e,
            ce->getCategory(),
            ce->getIsMandatory(),
            ce->getNote()
        );

        DaySchedule* ds = w->getDay(dow);
        if (ds != nullptr) {
            ds->addEvent(clone);
        } else {
            delete clone;
        }
    }

    printWeekCalendar(w);
    delete w;
}

void addCollegeEvent(std::vector<CollegeEvent*>& events) {
    clearCinLine();

    std::string title;
    std::cout << "College event title: ";
    std::getline(std::cin, title);

    std::string note;
    std::cout << "Note: ";
    std::getline(std::cin, note);

    DayOfWeek dow;
    MyTime start;
    MyTime end;
    inputDateTimeRange(dow, start, end);

    CollegeCategory cat = inputCollegeCategory();

    int mandInt;
    std::cout << "Mandatory? (0=no, 1=yes): ";
    std::cin >> mandInt;
    bool mand = (mandInt != 0);

    CollegeEvent* ce = new CollegeEvent(
        title,
        start,
        end,
        cat,
        mand,
        note
    );

    events.push_back(ce);
}

CollegeEvent* chooseCollegeEvent(std::vector<CollegeEvent*>& events) {
    if (events.empty()) {
        std::cout << "No college events.\n";
        return nullptr;
    }

    std::cout << "\nCollege events:\n";
    for (std::size_t i = 0; i < events.size(); ++i) {
        std::cout << (i + 1) << ") ";
        events[i]->display();
    }

    std::cout << "Select event number (0 = cancel): ";
    std::size_t idx;
    std::cin >> idx;

    if (idx == 0 || idx > events.size()) {
        return nullptr;
    }

    return events[idx - 1];
}

void editCollegeEvent(std::vector<CollegeEvent*>& events) {
    CollegeEvent* ce = chooseCollegeEvent(events);
    if (ce == nullptr) {
        return;
    }

    while (true) {
        std::cout << "\nEditing college event:\n";
        ce->display();
        std::cout << "1. Change title\n";
        std::cout << "2. Change time (same day)\n";
        std::cout << "3. Change note\n";
        std::cout << "4. Change category\n";
        std::cout << "5. Toggle mandatory\n";
        std::cout << "0. Done\n";

        int ch;
        std::cin >> ch;

        if (ch == 0) {
            break;
        }

        clearCinLine();

        if (ch == 1) {
            std::string title;
            std::cout << "New title: ";
            std::getline(std::cin, title);
            ce->updateTitle(title);
        } else if (ch == 2) {
            MyTime s = ce->getStartTime();
            MyTime e = ce->getEndTime();

            int sh;
            int sm;
            int eh;
            int em;

            std::cout << "New start time (hour minute): ";
            std::cin >> sh >> sm;
            std::cout << "New end time (hour minute): ";
            std::cin >> eh >> em;

            MyTime newStart(
                s.getYear(), s.getMonth(), s.getDay(),
                s.getDayOfWeek(), sh, sm
            );
            MyTime newEnd(
                e.getYear(), e.getMonth(), e.getDay(),
                e.getDayOfWeek(), eh, em
            );

            ce->updateTime(newStart, newEnd);
        } else if (ch == 3) {
            std::string note;
            std::cout << "New note: ";
            std::getline(std::cin, note);
            ce->updateNote(note);
        } else if (ch == 4) {
            CollegeCategory cat = inputCollegeCategory();
            ce->setCategory(cat);
        } else if (ch == 5) {
            bool nowMandatory = !ce->getIsMandatory();
            ce->setMandatory(nowMandatory);
        }
    }
}

void deleteCollegeEvent(std::vector<CollegeEvent*>& events) {
    if (events.empty()) {
        std::cout << "No college events.\n";
        return;
    }

    std::cout << "\nCollege events:\n";
    for (std::size_t i = 0; i < events.size(); ++i) {
        std::cout << (i + 1) << ") ";
        events[i]->display();
    }

    std::cout << "Select event number to delete (0 = cancel): ";
    std::size_t idx;
    std::cin >> idx;

    if (idx == 0 || idx > events.size()) {
        return;
    }

    delete events[idx - 1];
    events.erase(events.begin() + (idx - 1));

    std::cout << "College event deleted.\n";
}

void runCollegeEventMenu() {
    std::vector<CollegeEvent*> events =
        loadCollegeEventsFromFile("college_events.txt");

    while (true) {
        std::cout << "\n=== College Event Management ===\n";
        std::cout << "1. Show weekly college calendar\n";
        std::cout << "2. Add college event\n";
        std::cout << "3. Edit college event\n";
        std::cout << "4. Delete college event\n";
        std::cout << "0. Save and back\n";

        int ch;
        std::cin >> ch;

        if (ch == 0) {
            break;
        }

        if (ch == 1) {
            showCollegeCalendar(events);
        } else if (ch == 2) {
            addCollegeEvent(events);
        } else if (ch == 3) {
            editCollegeEvent(events);
        } else if (ch == 4) {
            deleteCollegeEvent(events);
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    saveCollegeEventsToFile(events, "college_events.txt");

    for (std::size_t i = 0; i < events.size(); ++i) {
        delete events[i];
    }
}

void findMeetingByCourse() {
    clearCinLine();

    std::string course;
    std::cout << "Course title: ";
    std::getline(std::cin, course);

    std::vector<std::string> ids = loadAllStudentIds();
    if (ids.empty()) {
        std::cout << "No students registered.\n";
        return;
    }

    std::vector<CollegeEvent*> collegeEvents =
        loadCollegeEventsFromFile("college_events.txt");

    SystemAlgorithm system;
    std::vector<WeekSchedule*> meetings;

    for (std::size_t i = 0; i < ids.size(); ++i) {
        WeekSchedule* w = loadScheduleFromFile(ids[i]);
        if (w == nullptr) {
            continue;
        }

        attachCollegeEventsToWeek(w, collegeEvents);

        if (studentTakesCourse(w, course)) {
            system.addStudentSchedule(w);
            meetings.push_back(w);
        } else {
            delete w;
        }
    }

    if (meetings.empty()) {
        std::cout << "No students found for this course.\n";
    } else {
        std::cout << "\n=== Meeting candidates for course '" << course << "' ===\n";
        for (std::size_t i = 0; i < meetings.size(); ++i) {
            printWeekCalendar(meetings[i]);
            std::cout << "-------------------------\n";
        }
        system.displayCommonFreeSlots();
    }

    for (std::size_t i = 0; i < meetings.size(); ++i) {
        delete meetings[i];
    }
    for (std::size_t i = 0; i < collegeEvents.size(); ++i) {
        delete collegeEvents[i];
    }
}

void findMeetingByStudentIds() {
    int n;
    std::cout << "Number of students: ";
    std::cin >> n;

    if (n <= 0) {
        return;
    }

    std::vector<std::string> ids;
    ids.reserve(static_cast<std::size_t>(n));

    for (int i = 0; i < n; ++i) {
        std::string id;
        std::cout << "Student ID #" << (i + 1) << ": ";
        std::cin >> id;

        if (!studentIdExists(id)) {
            std::cout << "ID " << id << " does not exist. Try again.\n";
            --i;
            continue;
        }

        ids.push_back(id);
    }

    std::vector<CollegeEvent*> collegeEvents =
        loadCollegeEventsFromFile("college_events.txt");

    SystemAlgorithm system;
    std::vector<WeekSchedule*> meetings;

    for (std::size_t i = 0; i < ids.size(); ++i) {
        WeekSchedule* w = loadScheduleFromFile(ids[i]);
        if (w == nullptr) {
            continue;
        }

        attachCollegeEventsToWeek(w, collegeEvents);
        system.addStudentSchedule(w);
        meetings.push_back(w);
    }

    if (meetings.empty()) {
        std::cout << "No valid students.\n";
    } else {
        std::cout << "\n=== Meeting candidates (selected students) ===\n";
        for (std::size_t i = 0; i < meetings.size(); ++i) {
            printWeekCalendar(meetings[i]);
            std::cout << "-------------------------\n";
        }
        system.displayCommonFreeSlots();
    }

    for (std::size_t i = 0; i < meetings.size(); ++i) {
        delete meetings[i];
    }
    for (std::size_t i = 0; i < collegeEvents.size(); ++i) {
        delete collegeEvents[i];
    }
}

void runMeetingFinderMenu() {
    while (true) {
        std::cout << "\n=== Meeting Finder ===\n";
        std::cout << "1. Find meeting by course name\n";
        std::cout << "2. Find meeting by student IDs\n";
        std::cout << "0. Back\n";

        int ch;
        std::cin >> ch;

        if (ch == 0) {
            break;
        }

        if (ch == 1) {
            findMeetingByCourse();
        } else if (ch == 2) {
            findMeetingByStudentIds();
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

int main() {
    while (true) {
        std::cout << "\n=== Group Schedule Manager ===\n";
        std::cout << "1. Student Management\n";
        std::cout << "2. College Event Management\n";
        std::cout << "3. Meeting Finder\n";
        std::cout << "0. Exit\n";
        std::cout << "Select: ";

        int choice;
        std::cin >> choice;

        if (!std::cin) {
            break;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            runStudentMenu();
        } else if (choice == 2) {
            runCollegeEventMenu();
        } else if (choice == 3) {
            runMeetingFinderMenu();
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Program finished.\n";
    return 0;
}
