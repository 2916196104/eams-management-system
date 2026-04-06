#pragma once
#ifndef COURSEDO_H_
#define COURSEDO_H_

#include "BaseDO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class CourseDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, courseId, CourseId);
    MYSQL_SYNTHESIZE(string, courseName, CourseName);
    MYSQL_SYNTHESIZE(int, subjectId, SubjectId);
    MYSQL_SYNTHESIZE(string, subjectName, SubjectName);
    MYSQL_SYNTHESIZE(string, lessonType, LessonType);
    MYSQL_SYNTHESIZE(int, courseNum, CourseNum);
    MYSQL_SYNTHESIZE(int, coursePrice, CoursePrice);
    MYSQL_SYNTHESIZE(int, expireMonths, ExpireMonths);
    MYSQL_SYNTHESIZE(string, startTime, StartTime);
    MYSQL_SYNTHESIZE(string, endTime, EndTime);
    MYSQL_SYNTHESIZE(string, tip, Tip);

public:
    CourseDO() : BaseDO("zo_eams")
    {
        MYSQL_ADD_FIELD_PK("id", "s", courseId);
        MYSQL_ADD_FIELD("name", "s", courseName);
        MYSQL_ADD_FIELD("subject_id", "i", subjectId);
        MYSQL_ADD_FIELD("subject_name", "s", subjectName);
        MYSQL_ADD_FIELD("lesson_type", "s", lessonType);
        MYSQL_ADD_FIELD("lesson_count", "i", courseNum);
        MYSQL_ADD_FIELD("price", "i", coursePrice);
        MYSQL_ADD_FIELD("expire_months", "i", expireMonths);
        MYSQL_ADD_FIELD("add_time", "s", startTime);
        MYSQL_ADD_FIELD("close_date", "s", endTime);
        MYSQL_ADD_FIELD("description", "s", tip);
    }
};

typedef std::shared_ptr<CourseDO> PtrCourseDO;
#include OATPP_CODEGEN_END(DTO)
#endif