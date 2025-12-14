## Section 1: Project Summary

- **What is your project? (1–2 sentences)**  
  My project is a console program called **Group Schedule Manager**. It manages weekly schedules for many students and finds common free time for meetings.

- **What features did you implement?**
    - Add, delete, and load students
    - Add, edit, and delete student events
    - Manage college events (holiday, professor day off, festival, vacation) in a separate file
    - Save and load student schedules and college events from text files
    - Show a weekly calendar (Mon–Sun, 07:00–23:00)
    - Find common free time by course name or by a list of student IDs

- **What does this project do well?**  
  It combines student schedules with college events, shows them as a weekly calendar, and finds shared free hours between several students.


## Section 2: Remaining Work

- **Planned features not implemented**
    - Repeating events (for example, “every Wednesday 10:00–11:00”)
    - Better user input interface
    - Search / sort functions, like “show only one day” or “show only one course”

- **Bugs or issues that still exist**
    - Not enough input checking (wrong times, wrong menu numbers, bad file format)
    - If a save file is broken, the program only prints an error and does not fix it
    - Uses many raw pointers; memory handling works but is not very safe

- **What is needed to call the project “finished”?**
    - Strong input validation and error handling
    - Repeating events and more viewing options
    - More testing and some code cleanup


## Section 3: Time Estimates for Remaining Items

1. **Input checking and error handling**
    - Time: about 3–4 hours
    - Includes: check all user input, handle bad files, better error messages
    - Priority: must have

2. **Repeating events**
    - Time: about 4–6 hours
    - Includes: new fields for repeat, file format change, update calendar and meeting finder
    - Priority: medium

3. **Search / sort views (by day or by course)**
    - Time: about 3–4 hours
    - Includes: filter events by day, course, and sort by start time
    - Priority: nice to have

4. **Refactor and small tests**
    - Time: about 4–5 hours
    - Includes: remove duplicate code, add small test cases
    - Priority: medium


## Section 4: What I Learned

- **C++ concepts I learned or improved**  
  I practiced classes, inheritance, virtual functions, `enum class`, vectors, file I/O, and `dynamic_cast`. I also learned how to split code into many `.h` and `.cpp` files.

- **Hardest part of the project**  
  The hardest part was connecting all classes (WeekSchedule, DaySchedule, SystemAlgorithm, FileInOut) and keeping the data correct when saving and loading from files.

- **What I would do differently next time**  
  I would start with a smaller design, test each part earlier, and think more about memory ownership and pointers from the beginning.

- **What I am most proud of**  
  I am proud that the program can show a weekly calendar, handle both student and college events, and find common free time for meetings.

- **How my understanding of data structures changed**  
  I now see why vectors and maps are useful for schedules. I also learned that when I use vectors of pointers, I must plan clearly who creates and deletes each object.


## Section 5: Time Log (estimate)

- **Planning and design:** about 6 hours
- **Implementation (coding):** about 30 hours
- **Testing and debugging:** about 8 hours
- **Documentation (comments, write-up):** about 3 hours

**Total:** about **47 hours**
