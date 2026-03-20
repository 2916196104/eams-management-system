#pragma once

#include "domain/do/DoInclude.h"

class GradeRecordDO : public BaseDO
{
public:
    GradeRecordDO() : BaseDO("grade_record")
    {
        MYSQL_ADD_FIELD_PK("id", "bi", id);
        MYSQL_ADD_FIELD("grade_id", "bi", grade_id);
        MYSQL_ADD_FIELD("student_id", "bi", student_id);
        MYSQL_ADD_FIELD("score", "i", score);
        MYSQL_ADD_FIELD("add_time", "s", add_time);
        MYSQL_ADD_FIELD("creator", "bi", creator);
    }

private:
    MYSQL_SYNTHESIZE(int64_t, id, Id);
    MYSQL_SYNTHESIZE(int64_t, grade_id, GradeId);
    MYSQL_SYNTHESIZE(int64_t, student_id, StudentId);
    MYSQL_SYNTHESIZE(int8_t, score, Score);
    MYSQL_SYNTHESIZE(string, add_time, AddTime);
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);
};

typedef shared_ptr<GradeRecordDO> PtrGradeRecordDO;