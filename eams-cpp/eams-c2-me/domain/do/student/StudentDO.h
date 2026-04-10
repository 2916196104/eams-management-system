#pragma once

#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_

#include "../DoInclude.h"
// 确保 uint64_t 类型可用
#include <cstdint>

class StudentDO : public BaseDO
{
    // bigint类：uint64_t
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
    // tinyint 全部改成 int
    MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
    MYSQL_SYNTHESIZE(int, asDefault, AsDefault);

    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
    MYSQL_SYNTHESIZE(string, name, Name);
    // int/tinyint 改成 int
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    MYSQL_SYNTHESIZE(int, stage, Stage);
    MYSQL_SYNTHESIZE(int, gender, Gender);

    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);
    MYSQL_SYNTHESIZE(uint64_t, joinWay, JoinWay);
    MYSQL_SYNTHESIZE(string, remark, Remark);
    MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
    MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
    MYSQL_SYNTHESIZE(string, addTime, AddTime);

    MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);

    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
    MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
    MYSQL_SYNTHESIZE(string, grade, Grade);
    MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
    MYSQL_SYNTHESIZE(uint64_t, wxAccessId, WxAccessId);
    // int 改成 int
    MYSQL_SYNTHESIZE(int, credit, Credit);

    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
    MYSQL_SYNTHESIZE(int, gradeId, GradeId);

public:
    StudentDO() : BaseDO("student")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD("user_id", "ull", userId);
        MYSQL_ADD_FIELD("family_rel", "i", familyRel);
        MYSQL_ADD_FIELD("as_default", "i", asDefault);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("stage", "i", stage);
        MYSQL_ADD_FIELD("gender", "i", gender);
        MYSQL_ADD_FIELD("birthday", "s", birthday);
        MYSQL_ADD_FIELD("head_img", "s", headImg);
        MYSQL_ADD_FIELD("join_way", "ull", joinWay);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
        MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("counselor", "ull", counselor);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        MYSQL_ADD_FIELD("editor", "ull", editor);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("idcard", "s", idcard);
        MYSQL_ADD_FIELD("redpoint_grade", "s", redpointGrade);
        MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpointEvaluate);
        MYSQL_ADD_FIELD("grade", "s", grade);
        MYSQL_ADD_FIELD("join_date", "s", joinDate);
        MYSQL_ADD_FIELD("wx_access_id", "ull", wxAccessId);
        MYSQL_ADD_FIELD("credit", "i", credit);
        MYSQL_ADD_FIELD("org_id", "ull", orgId);
        MYSQL_ADD_FIELD("grade_id", "i", gradeId);
    }
};

typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif
