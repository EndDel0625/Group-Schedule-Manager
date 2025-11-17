//
// Created by 김영빈 on 11/4/25.
//

#ifndef FINAL_PROJECT_SYSTEMALGORITHM_H
#define FINAL_PROJECT_SYSTEMALGORITHM_H

#include "WeekSchedule.h"
#include "CollegeEvent.h"
#include "StudentEvent.h"
#include <vector>

class SystemAlgorithm {
    private:
        std::vector<WeekSchedule*> allSchedules;

        void distributeMultiDayEvents(WeekSchedule* schedule);
        void resolveConflicts(WeekSchedule* schedule);

    public:
        SystemAlgorithm() = default;

        void addStudentSchedule(WeekSchedule* schedule);
        std::vector<int> findCommonFreeSlots() const;
        void displayCommonFreeSlots() const;
};



#endif //FINAL_PROJECT_SYSTEMALGORITHM_H