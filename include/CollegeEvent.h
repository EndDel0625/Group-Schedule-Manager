//
// Created by 김영빈 on 10/17/25.
//

#ifndef FINAL_PROJECT_COLLEGEEVENT_H
#define FINAL_PROJECT_COLLEGEEVENT_H

#include "Event.h"

enum class CollegeCategory {
    HOLIDAY,
    PROFESSOR_DAYOFF,
    FESTIVAL,
    VACATION,
    UNKNOWN
};

class CollegeEvent : public Event {
    private:
    CollegeCategory category;
    bool isMandatory;

    public:
    CollegeEvent(const std::string &title, const MyTime &start, const MyTime &end,
                 CollegeCategory cat = CollegeCategory::UNKNOWN, bool mandatory = true,
                 const std::string &note = "");

    void setCategory(CollegeCategory cat);
    void setMandatory(bool mand);

    CollegeCategory getCategory() const;
    bool getIsMandatory() const;

    void display() const override;

};

#endif //FINAL_PROJECT_COLLEGEEVENT_H