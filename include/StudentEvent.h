//
// Created by 김영빈 on 10/17/25.
//

#ifndef FINAL_PROJECT_STUDENT_H
#define FINAL_PROJECT_STUDENT_H

#include "Event.h"

class StudentEvent : public Event {
private:
    std::string id;
    int priority;
    bool isPrivate;

public:
    StudentEvent(std::string id, const std::string &title, const MyTime &start, const MyTime &end,
    int p = 3, bool priv = false, const std::string &note = "");

    std::string getId() const;
    int getPriority() const;
    bool getIsPrivate() const;

    void setPriority(int p);
    void setIsPrivate(bool priv);

    void display() const override;

};

#endif //FINAL_PROJECT_STUDENT_H