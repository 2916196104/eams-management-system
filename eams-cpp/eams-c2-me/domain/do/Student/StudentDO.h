#pragma once

#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_

#include "../DoInclude.h"
// 确保 uint64_t 类型可用
#include <cstdint>

class StudentDO : public BaseDO
{
    // ===================== 数据库字段定义（使用MYSQL_SYNTHESIZE宏）=====================
    // 宏说明：MYSQL_SYNTHESIZE(字段类型, 变量名, 方法名后缀)
    // 自动生成：protected级别的成员变量 + public的getXXX()/setXXX()方法

    // 主键：学生ID（对应表字段id，bigint UNSIGNED）
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 家长ID（对应表字段user_id，bigint）
    MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
    // 家庭关系（对应表字段family_rel，tinyint）
    MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
    // 家长默认查看的学员（对应表字段as_default，tinyint(1)）
    MYSQL_SYNTHESIZE(int, asDefault, AsDefault);
    // 所属分校（对应表字段school_id，bigint）
    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
    // 姓名（对应表字段name，varchar(20)）
    MYSQL_SYNTHESIZE(string, name, Name);
    // 逻辑删除（对应表字段deleted，int）
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 阶段状态（0=意向学员，对应表字段stage，tinyint）
    MYSQL_SYNTHESIZE(int, stage, Stage);
    // 性别（对应表字段gender，tinyint）
    MYSQL_SYNTHESIZE(int, gender, Gender);
    // 生日（对应表字段birthday，date）
    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    // 头像（对应表字段head_img，varchar(255)）
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);
    // 加入方式（对应表字段join_way，bigint）
    MYSQL_SYNTHESIZE(uint64_t, joinWay, JoinWay);
    // 备注（对应表字段remark，varchar(255)）
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 结业日期（对应表字段graduation_date，date）
    MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
    // 结业原因（对应表字段graduation_reason，varchar(255)）
    MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
    // 加入时间（对应表字段add_time，datetime）
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 顾问（对应表字段counselor，bigint）
    MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
    // 创建者（对应表字段creator，bigint）
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人（对应表字段editor，bigint）
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 编辑时间（对应表字段edit_time，datetime）
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 身份证号（对应表字段idcard，varchar(30)）
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    // 红点标记成绩最后查看时间（对应表字段redpoint_grade，datetime）
    MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
    // 红点标记点评最后查看时间（对应表字段redpoint_evaluate，datetime）
    MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
    // 入学年份（对应表字段grade，year）
    MYSQL_SYNTHESIZE(string, grade, Grade);
    // 入学日期（对应表字段join_date，date）
    MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
    // 微信登录记录ID（对应表字段wx_access_id，bigint）
    MYSQL_SYNTHESIZE(uint64_t, wxAccessId, WxAccessId);
    // 学生积分（对应表字段credit，int）
    MYSQL_SYNTHESIZE(int, credit, Credit);
    // 创建者所属组织ID（对应表字段org_id，bigint）
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
    // 年级ID（对应表字段grade_id，int）
    MYSQL_SYNTHESIZE(int, gradeId, GradeId);

public:
    /**
     * 构造函数
     * 作用：1. 指定当前DO对应的数据库表名 2. 注册表字段（主键+普通字段）
     * BaseDO("student")：表示当前DO对应数据库的`student`表
     */
    StudentDO() : BaseDO("student")
    {
        // ===================== 注册数据库字段（供框架自动生成SQL）=====================
        // 宏说明：
        // MYSQL_ADD_FIELD_PK(数据库列名, 类型标识, 成员变量名)：注册主键字段
        // MYSQL_ADD_FIELD(数据库列名, 类型标识, 成员变量名)：注册普通字段
        // 类型标识："l"=uint64_t(无符号长整型)，"i"=int，"s"=string

        // 注册主键：id（数据库列名id，类型标识l，成员变量id）
        MYSQL_ADD_FIELD_PK("id", "l", id);
        // 注册普通字段：按数据库列名逐个注册
        MYSQL_ADD_FIELD("user_id", "l", userId);
        MYSQL_ADD_FIELD("family_rel", "i", familyRel);
        MYSQL_ADD_FIELD("as_default", "i", asDefault);
        MYSQL_ADD_FIELD("school_id", "l", schoolId);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("stage", "i", stage);
        MYSQL_ADD_FIELD("gender", "i", gender);
        MYSQL_ADD_FIELD("birthday", "s", birthday);
        MYSQL_ADD_FIELD("head_img", "s", headImg);
        MYSQL_ADD_FIELD("join_way", "l", joinWay);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
        MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("counselor", "l", counselor);
        MYSQL_ADD_FIELD("creator", "l", creator);
        MYSQL_ADD_FIELD("editor", "l", editor);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("idcard", "s", idcard);
        MYSQL_ADD_FIELD("redpoint_grade", "s", redpointGrade);
        MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpointEvaluate);
        MYSQL_ADD_FIELD("grade", "s", grade);
        MYSQL_ADD_FIELD("join_date", "s", joinDate);
        MYSQL_ADD_FIELD("wx_access_id", "l", wxAccessId);
        MYSQL_ADD_FIELD("credit", "i", credit);
        MYSQL_ADD_FIELD("org_id", "l", orgId);
        MYSQL_ADD_FIELD("grade_id", "i", gradeId);
    }
};

/**
 * 定义智能指针类型（简化指针使用，自动管理内存，避免内存泄漏）
 * 使用方式：PtrStudentDO studentDO = std::make_shared<StudentDO>();
 */
typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif // !_STUDENT_DO_H_