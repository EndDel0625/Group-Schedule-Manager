cmake_minimum_required(VERSION 3.16)
project(Final_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Final_Project
        src/Main.cpp
        src/Event.cpp
        src/MyTime.cpp
        src/StudentEvent.cpp
        src/CollegeEvent.cpp
        src/DaySchedule.cpp
        src/WeekSchedule.cpp
        include/DayConverter.h
        src/DayConverter.cpp
        src/SystemAlgorithm.cpp
        src/FileInOut.cpp

)


target_include_directories(Final_Project PRIVATE include)