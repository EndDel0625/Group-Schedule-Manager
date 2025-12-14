    //
    // Created by 김영빈 on 12/7/25.
    //

#include "FileInOut.h"
#include "StudentEvent.h"
#include "CollegeEvent.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

    static void leftTrim(std::string& s) {
        while (!s.empty() && (s[0] == ' ' || s[0] == '\t')) {
            s.erase(s.begin());
        }
    }

    static std::string makeFilename(const std::string& studentId) {
        return "schedule_" + studentId + ".txt";
    }

    void saveScheduleToFile(const WeekSchedule* week) {
        if (!week) return;

            std::string filename = makeFilename(week->getStudentId());
            std::ofstream ofs(filename);
            if (!ofs) {
                std::cerr << "[FileInOut][SAVE] Could not open schedule file for student ID: "
                << week->getStudentId() << " (filename: " << filename << ")" << std::endl
                << "            -> This student's schedule will NOT be saved and" << std::endl
                << "               may be excluded from any file-based common free time calculation." << std::endl;
            return;
        }

        ofs << "STUDENT_ID " << week->getStudentId() << std::endl;


        for (int d = 0; d < 7; ++d) {
            DayOfWeek day = static_cast<DayOfWeek>(d);
            DaySchedule* ds = const_cast<WeekSchedule*>(week)->getDay(day);
            if (!ds) continue;

            const auto& evs = ds->getEvents();
            for (Event* ev : evs) {
                ofs << "EVENT_BEGIN" <<std::endl;

                auto* se = dynamic_cast<StudentEvent*>(ev);
                auto* ce = dynamic_cast<CollegeEvent*>(ev);

                if (se) {
                    ofs << "TYPE STUDENT" << std::endl;
                } else if (ce) {
                    ofs << "TYPE COLLEGE" << std::endl;
                } else {
                    ofs << "TYPE BASE" << std::endl;
                }

                ofs << "TITLE " << ev->getTitle() << std::endl;
                ofs << "NOTE "  << ev->getNote()  << std::endl;

                const MyTime s = ev->getStartTime();
                const MyTime e = ev->getEndTime();

                ofs << "DAY_OF_WEEK " << static_cast<int>(s.getDayOfWeek()) << std::endl;
                ofs << "DATE " << s.getYear() << " " << s.getMonth() << " " << s.getDay() << std::endl;
                ofs << "TIME " << s.getHour() << " " << s.getMinute() << " "
                          << e.getHour() << " " << e.getMinute() << std::endl;

                if (se) {
                    ofs << "STUDENT_INFO " << se->getId() << " "
                    << se->getPriority() << " "
                    << (se->getIsPrivate() ? 1 : 0) << std::endl;
                } else if (ce) {
                    ofs << "COLLEGE_INFO " << static_cast<int>(ce->getCategory()) << " "
                    << (ce->getIsMandatory() ? 1 : 0) << std::endl;
                }

                ofs << "EVENT_END" <<std::endl;
            }
        }
        std::cout << "[FileInOut][SAVE] Saved schedule for student ID: "
              << week->getStudentId()
              << " (filename: " << filename << ")" <<std::endl;
    }


    WeekSchedule* loadScheduleFromFile(const std::string& studentId) {
        std::string filename = makeFilename(studentId);
        std::ifstream ifs(filename);
        if (!ifs) {
            std::cerr
            << "[FileInOut][LOAD] Could not open schedule file for student ID: " << studentId
            << " (filename: " << filename << ")\n" << " -> This student will be excluded from common free time calculation." <<std::endl;
        return nullptr;
        }

        std::string token;
        std::string fileStudentId;


        if (!(ifs >> token) || token != "STUDENT_ID") {
            std::cerr
                << "[FileInOut][LOAD] Invalid file format: missing STUDENT_ID header." << " (filename: " << filename << ")\n"
                << "            -> This file will be ignored and the student\n"
                << "               will be excluded from common free time calculation." <<std::endl;
        return nullptr;
        }
        ifs >> fileStudentId;

        if (fileStudentId != studentId) {
            std::cerr << "[FileInOut][LOAD] Warning: student ID in file (" << fileStudentId << ") does not match requested ID ("
            << studentId << ").\n" << "            -> The schedule will be loaded using the ID from the file ("
            << fileStudentId << ") and included in the common free time calculation." << std::endl;
        }

        WeekSchedule* week = new WeekSchedule(fileStudentId);


        while (ifs >> token) {
            if (token != "EVENT_BEGIN") {
                continue;
            }


            std::string typeLabel, typeValue;
            ifs >> typeLabel >> typeValue;


            std::string titleLabel;
            ifs >> titleLabel;
            std::string title;
            std::getline(ifs, title);
            leftTrim(title);


            std::string noteLabel;
            ifs >> noteLabel;
            std::string note;
            std::getline(ifs, note);
            leftTrim(note);


            std::string dowLabel;
            int dowInt = 0;
            ifs >> dowLabel >> dowInt;


            std::string dateLabel;
            int y, m, d;
            ifs >> dateLabel >> y >> m >> d;


            std::string timeLabel;
            int sh, sm, eh, em;
            ifs >> timeLabel >> sh >> sm >> eh >> em;

            DayOfWeek dow = static_cast<DayOfWeek>(dowInt);
            MyTime start(y, m, d, dow, sh, sm);
            MyTime end  (y, m, d, dow, eh, em);

            Event* newEvent = nullptr;

            if (typeValue == "STUDENT") {
                std::string siLabel, sid;
                int priority, privInt;
                ifs >> siLabel >> sid >> priority >> privInt;
                bool isPrivate = (privInt != 0);
                newEvent = new StudentEvent(sid, title, start, end,
                                        priority, isPrivate, note);
            } else if (typeValue == "COLLEGE") {
                std::string ciLabel;
                int catInt, mandInt;
                ifs >> ciLabel >> catInt >> mandInt;
                CollegeCategory cat = static_cast<CollegeCategory>(catInt);
                bool mandatory = (mandInt != 0);
                newEvent = new CollegeEvent(title, start, end, cat, mandatory, note);
            } else {

                newEvent = new Event(title, start, end, note);
            }


            std::string endToken;
            ifs >> endToken;

            if (newEvent) {
                week->getDay(dow)->addEvent(newEvent);
            }
        }

        std::cout << "[FileInOut][LOAD] Loaded schedule for student ID: " << fileStudentId << " (filename: " << filename << ")" << std::endl;
        return week;

    }

void saveCollegeEventsToFile(const std::vector<CollegeEvent*>& events,
                             const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "[FileInOut][COLLEGE_SAVE] Could not open college event file: "
                  << filename << std::endl;
        return;
    }

    for (CollegeEvent* ce : events) {
        if (!ce) continue;

        MyTime s = ce->getStartTime();
        MyTime e = ce->getEndTime();

        ofs << "COLLEGE_EVENT "
            << static_cast<int>(s.getDayOfWeek()) << " "
            << s.getYear() << " " << s.getMonth() << " " << s.getDay() << " "
            << s.getHour() << " " << s.getMinute() << " "
            << e.getHour() << " " << e.getMinute() << " "
            << static_cast<int>(ce->getCategory()) << " "
            << (ce->getIsMandatory() ? 1 : 0)
            << std::endl;

        ofs << ce->getTitle() << std::endl;
        ofs << ce->getNote()  << std::endl;
    }

    std::cout << "[FileInOut][COLLEGE_SAVE] Saved " << events.size() << " college event(s) to "
              << filename << std::endl;
}

std::vector<CollegeEvent*> loadCollegeEventsFromFile(const std::string& filename) {
    std::vector<CollegeEvent*> result;

    std::ifstream ifs(filename);
    if (!ifs) {
        return result;
    }

    std::string tag;
    while (ifs >> tag) {
        if (tag != "COLLEGE_EVENT") {
            std::string dummy;
            std::getline(ifs, dummy);
            continue;
        }

        int dowInt, year, month, day, sh, sm, eh, em, catInt, mandInt;
        ifs >> dowInt >> year >> month >> day
            >> sh >> sm >> eh >> em
            >> catInt >> mandInt;
        std::string dummy;
        std::getline(ifs, dummy);

        std::string title;
        std::getline(ifs, title);
        std::string note;
        std::getline(ifs, note);

        DayOfWeek dow = static_cast<DayOfWeek>(dowInt);
        MyTime start(year, month, day, dow, sh, sm);
        MyTime end  (year, month, day, dow, eh, em);

        CollegeCategory cat = static_cast<CollegeCategory>(catInt);
        bool mandatory = (mandInt != 0);

        CollegeEvent* ce = new CollegeEvent(
            title, start, end, cat, mandatory, note
        );
        result.push_back(ce);
    }

    std::cout << "[FileInOut][COLLEGE_LOAD] Loaded " << result.size() << " college event(s) from "
              << filename << std::endl;

    return result;
}
