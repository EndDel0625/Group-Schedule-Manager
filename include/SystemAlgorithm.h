//
// Created by 김영빈 on 11/4/25.
//

#ifndef FINAL_PROJECT_SYSTEMALGORITHM_H
#define FINAL_PROJECT_SYSTEMALGORITHM_H

#include <vector>
#include "WeekSchedule.h"

class SystemAlgorithm {
    private:
        std::vector<WeekSchedule*> allSchedules;

    public:
        SystemAlgorithm() = default;
        ~SystemAlgorithm() = default;

        void addStudentSchedule(WeekSchedule* schedule);
        void findCommonFreeSlots() const;
        void displayCommonFreeSlots() const;
};



#endif //FINAL_PROJECT_SYSTEMALGORITHM_H