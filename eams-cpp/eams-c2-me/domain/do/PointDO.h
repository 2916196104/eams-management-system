#pragma once

#ifndef _MYPOINTDO_H_
#define _MYPOINTDO_H_

#include "DoInclude.h"
//#include "file/FileDO.h"

/**
 * 测试用户数据实体
 */
class PointDO : public BaseDO
{
    // ========== 数据库字段定义（智能指针+get/set方法） ==========
    // 主键ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, id, Id);
    // 学生ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, studentId, StudentId);
    // 用户ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, userId, UserId);
    // 本次变动学分 (INT → int，类型占位符i)
    MYSQL_SYNTHESIZE(int, credit, Credit);
    // 变动后剩余学分 (INT → int，类型占位符i)
    MYSQL_SYNTHESIZE(int, currentCredit, CurrentCredit);
    // 变动类型 (TINYINT → int，类型占位符i，1=增加/0=减少)
    MYSQL_SYNTHESIZE(int, changeType, ChangeType);
    // 变动时间 (BIGINT时间戳 → long long，类型占位符ll；若为DATETIME则用dt)
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 变动备注/原因 (VARCHAR → string，类型占位符s)
    MYSQL_SYNTHESIZE(std::string, remark, Remark);
    // 来源ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, sourceId, SourceId);
    // 操作员工ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, staffId, StaffId);
    // 学校ID (BIGINT → long long，类型占位符ll)
    MYSQL_SYNTHESIZE(long long, schoolId, SchoolId);

public:
    /**
     * 构造函数
     * 参数：数据库表名（替换为实际表名）
     */
    PointDO() : BaseDO("student_credit_log")
    {
        // ========== 绑定数据库字段与DO成员变量 ==========
        // 主键字段（id）
        MYSQL_ADD_FIELD_PK("id", "ll", id);
        // 普通字段
        MYSQL_ADD_FIELD("student_id", "ll", studentId);   // 数据库字段名：student_id
        MYSQL_ADD_FIELD("user_id", "ll", userId);         // 数据库字段名：user_id
        MYSQL_ADD_FIELD("credit", "i", credit);           // 数据库字段名：credit
        MYSQL_ADD_FIELD("current_credit", "i", currentCredit); // 数据库字段名：current_credit
        MYSQL_ADD_FIELD("change_type", "i", changeType);  // 数据库字段名：change_type
        MYSQL_ADD_FIELD("add_time", "ll", addTime);       // 数据库字段名：add_time
        MYSQL_ADD_FIELD("remark", "s", remark);           // 数据库字段名：remark
        MYSQL_ADD_FIELD("source_id", "ll", sourceId);     // 数据库字段名：source_id
        MYSQL_ADD_FIELD("staff_id", "ll", staffId);       // 数据库字段名：staff_id
        MYSQL_ADD_FIELD("school_id", "ll", schoolId);     // 数据库字段名：school_id
    }
};



#endif 









