cmake_minimum_required(VERSION 3.16)
project(Final_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 실행 파일 타깃 생성 (소스 목록에 모든 .cpp 추가)
add_executable(Final_Project
        src/Main.cpp
        src/Event.cpp
        src/MyTime.cpp
        src/StudentEvent.cpp
        src/CollegeEvent.cpp
        src/DaySchedule.cpp
        # 필요하면 아래에 다른 .cpp도 계속 추가
        # src/DaySchedule.cpp
        # src/WeekSchedule.cpp
        # src/CollegeEvent.cpp
)

# 헤더가 들어있는 include 폴더를 타깃에 알려주기
target_include_directories(Final_Project PRIVATE include)