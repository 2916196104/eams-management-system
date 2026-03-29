#pragma once

#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_

#include "../DoInclude.h"
// 确保 uint64_t 类型可用
#include <cstdint>

/**
 * 学生数据库实体类
 * 类型调整说明（基于 SqlHelper.h 宏定义）：
 * - 原 string（映射 bigint 等数字字段）→ uint64_t，类型标识用 "ull"
 * - 原 int（映射 tinyint 字段）→ char，类型标识用 "i"（框架无单独 "c"，用 "i" 兼容）
 * - 字符串/日期类字段（name/birthday/remark 等）保留 string，类型标识 "s"
 */
class StudentDO : public BaseDO
{
    // ===================== 数据库字段定义 =====================
    // 主键：学生ID（bigint UNSIGNED → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 家长ID（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
    // 家庭关系（tinyint → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, familyRel, FamilyRel);
    // 家长默认查看的学员（tinyint(1) → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, asDefault, AsDefault);
    // 所属分校（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
    // 姓名（varchar(20) → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, name, Name);
    // 逻辑删除（int → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, deleted, Deleted);
    // 阶段状态（tinyint → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, stage, Stage);
    // 性别（tinyint → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, gender, Gender);
    // 生日（date → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    // 头像（varchar(255) → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);
    // 加入方式（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, joinWay, JoinWay);
    // 备注（varchar(255) → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 结业日期（date → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
    // 结业原因（varchar(255) → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
    // 加入时间（datetime → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 顾问（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
    // 创建者（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 编辑时间（datetime → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 身份证号（varchar(30) → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    // 红点标记成绩最后查看时间（datetime → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
    // 红点标记点评最后查看时间（datetime → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
    // 入学年份（year → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, grade, Grade);
    // 入学日期（date → string，标识 "s"）
    MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
    // 微信登录记录ID（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, wxAccessId, WxAccessId);
    // 学生积分（int → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, credit, Credit);
    // 创建者所属组织ID（bigint → uint64_t，标识 "ull"）
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
    // 年级ID（int → char，标识 "i"）
    MYSQL_SYNTHESIZE(char, gradeId, GradeId);

public:
    /**
     * 构造函数：指定表名 + 注册表字段
     */
    StudentDO() : BaseDO("student")
    {
        // ===================== 注册数据库字段（类型标识严格匹配 SqlHelper.h）=====================
        // 主键：id（标识 "ull"）
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        // 普通字段
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

// 智能指针类型定义
typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif