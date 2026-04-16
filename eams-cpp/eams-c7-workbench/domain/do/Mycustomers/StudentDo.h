#pragma once
#ifndef _STUDENT_DO_
#define _STUDENT_DO_

#include "../DoInclude.h"
#include "../lib-mysql/include/SqlHelper.h"

/**
 * 学生表对应的数据库实体类
 * 数据库表：student
 */
class StudentDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 家长id
    MYSQL_SYNTHESIZE(uint64_t, user_id, UserId);
    // 家庭关系
    MYSQL_SYNTHESIZE(int32_t, family_rel, FamilyRel);
    // 家长默认查看的学员
    MYSQL_SYNTHESIZE(int32_t, as_default, AsDefault);
    // 所属分校
    MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
    // 姓名
    MYSQL_SYNTHESIZE(string, name, Name);
    // 逻辑删除 0未删除 1已删除
    MYSQL_SYNTHESIZE(int32_t, deleted, Deleted);
    // 阶段状态0意向学员
    MYSQL_SYNTHESIZE(int32_t, stage, Stage);
    // 性别
    MYSQL_SYNTHESIZE(int32_t, gender, Gender);
    // 生日
    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    // 头像
    MYSQL_SYNTHESIZE(string, head_img, HeadImg);
    // 加入方式
    MYSQL_SYNTHESIZE(uint64_t, join_way, JoinWay);
    // 备注
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 结业日期
    MYSQL_SYNTHESIZE(string, graduation_date, GraduationDate);
    // 结业原因
    MYSQL_SYNTHESIZE(string, graduation_reason, GraduationReason);
    // 加入时间
    MYSQL_SYNTHESIZE(string, add_time, AddTime);
    // 顾问
    MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
    // 创建者
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, edit_time, EditTime);
    // 身份证号
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    // 红点标记成绩最后查看时间
    MYSQL_SYNTHESIZE(string, redpoint_grade, RedpointGrade);
    // 红点标记点评最后查看时间
    MYSQL_SYNTHESIZE(string, redpoint_evaluate, RedpointEvaluate);
    // 入学年份
    MYSQL_SYNTHESIZE(int32_t, grade, Grade);
    // 入学日期
    MYSQL_SYNTHESIZE(string, join_date, JoinDate);
    // 微信登录记录id
    MYSQL_SYNTHESIZE(uint64_t, wx_access_id, WxAccessId);
    // 学生积分
    MYSQL_SYNTHESIZE(int32_t, credit, Credit);
    // 创建者所属组织ID
    MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
    // 年级ID
    MYSQL_SYNTHESIZE(int32_t, grade_id, GradeId);

    MYSQL_SYNTHESIZE(string, mobile, Mobile);

    MYSQL_SYNTHESIZE(int32_t, age, Age);

public:
    StudentDO() : BaseDO("student")
    {
        // 注册主键
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        // 注册所有数据库字段
        MYSQL_ADD_FIELD("user_id", "ull", user_id);
        MYSQL_ADD_FIELD("family_rel", "int", family_rel);
        MYSQL_ADD_FIELD("as_default", "int", as_default);
        MYSQL_ADD_FIELD("school_id", "ull", school_id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("deleted", "int", deleted);
        MYSQL_ADD_FIELD("stage", "int", stage);
        MYSQL_ADD_FIELD("gender", "int", gender);
        MYSQL_ADD_FIELD("birthday", "s", birthday);
        MYSQL_ADD_FIELD("head_img", "s", head_img);
        MYSQL_ADD_FIELD("join_way", "ull", join_way);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("graduation_date", "s", graduation_date);
        MYSQL_ADD_FIELD("graduation_reason", "s", graduation_reason);
        MYSQL_ADD_FIELD("add_time", "s", add_time);
        MYSQL_ADD_FIELD("counselor", "ull", counselor);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        MYSQL_ADD_FIELD("editor", "ull", editor);
        MYSQL_ADD_FIELD("edit_time", "s", edit_time);
        MYSQL_ADD_FIELD("idcard", "s", idcard);
        MYSQL_ADD_FIELD("redpoint_grade", "s", redpoint_grade);
        MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpoint_evaluate);
        MYSQL_ADD_FIELD("grade", "int", grade);
        MYSQL_ADD_FIELD("join_date", "s", join_date);
        MYSQL_ADD_FIELD("wx_access_id", "ull", wx_access_id);
        MYSQL_ADD_FIELD("credit", "int", credit);
        MYSQL_ADD_FIELD("org_id", "ull", org_id);
        MYSQL_ADD_FIELD("grade_id", "int", grade_id);

        MYSQL_ADD_FIELD("mobile", "s", mobile);
        MYSQL_ADD_FIELD("age", "int", age);
    }
};

typedef shared_ptr<StudentDO> PtrStudentDO;
#endif // _STUDENT_DO_