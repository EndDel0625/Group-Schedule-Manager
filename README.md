# Group Schedule Manager

## Overview
This program is a C++ console app for managing weekly schedules.  
It stores each student’s weekly schedule, applies college events, and finds common free time for meetings.

---

## Features

### Event System
- **Event**  
  Base class with title, time range, and note.
- **StudentEvent**  
  Personal events for one student.  
  Has priority (1–5) and a private flag.
- **CollegeEvent**  
  School events: holidays, professor day off, festivals, vacations.  
  Saved in a separate file and applied to many students.

### Schedule System
- **DaySchedule**  
  Holds all events for one weekday.  
  Can check if a time slot (hour) is free or busy.
- **WeekSchedule**  
  Has 7 `DaySchedule` objects (Mon–Sun) for one student.  
  Uses a student ID as the key.

### System Algorithm
- Collects multiple `WeekSchedule` objects.
- Expands multi-day college events across several days.
- Detects conflicts between events.
- Finds common free hours (07:00–23:00) where all selected students are free.

### File I/O
- `schedule_<studentId>.txt`  
  Saves and loads one student’s weekly schedule.
- `students.txt`  
  Stores the list of existing student IDs.
- `college_events.txt`  
  Saves and loads all `CollegeEvent` data.
- Prints simple error messages when files are missing or broken.

### Menus (main.cpp)
1. **Student Management**
  - Add new student
  - Manage existing student
  - Delete student and their schedule file
  - Inside student menu:
    - Show weekly calendar (Mon–Sun, 07–23, `X` = busy, `.` = free)
    - Add / edit / delete student events

2. **College Event Management**
  - Show weekly college calendar
  - Add / edit / delete college events
  - Save to `college_events.txt`

3. **Meeting Finder**
  - Find by course name (uses students who take that course)
  - Find by a list of student IDs (checks if IDs exist)
  - Shows each candidate’s calendar
  - Prints shared free hours for all selected students

---

## Building
Use a C++11 (or later) compiler.  
All `.h` files are in `include/`, `.cpp` files are in `src/`.


## Running
After building, run it from the terminal.  
A simple menu will show up to add schedules, create events, and find the best time for everyone.

## Usage
Each person can enter their own classes or events with times, and the program shows when everyone is free to meet.


## Author
Joseph Kim - CIS 25 Final Project
