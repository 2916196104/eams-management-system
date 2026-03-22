#pragma once
#ifndef _TIMEABLE_DO_
#define _TIMEABLE_DO_
#include "../DoInclude.h"

/**
 * 示例数据库实体类
 */
//还需要改数据库的表
 class GetTimeableDO : public BaseDO
{
    // ========== 字段定义（完全对齐 SampleDO 风格，驼峰命名+MYSQL_SYNTHESIZE） ==========
    // 课程ID（整型，对应 lesson.id）
    MYSQL_SYNTHESIZE(int, id, Id);
    // 课程标题
    MYSQL_SYNTHESIZE(string, title, Title);
    // 课程序号（字符串，对应 lesson.sn）
    MYSQL_SYNTHESIZE(string, sn, Sn);
    // 上课日期
    MYSQL_SYNTHESIZE(string, date, Date);
    // 开始时间
    MYSQL_SYNTHESIZE(string, start_time, Start_time);
    // 结束时间
    MYSQL_SYNTHESIZE(string, end_time, End_time);
    // 教师ID
    MYSQL_SYNTHESIZE(int, teacher_id, Teacher_id);
    // 排课计划ID
    MYSQL_SYNTHESIZE(int, schedule_id, Schedule_id);
    // 教师姓名（关联 staff.name）
    MYSQL_SYNTHESIZE(string, teacher_name, TeacherName);
    // 签到状态（关联 lesson_student.sign_state）
    MYSQL_SYNTHESIZE(int, sign_state, SignState);

public:
    GetTimeableDO() : BaseDO("sample")  // 表名和 SampleDO 一致为 "sample"
    {
        // ========== 数据库映射（顺序严格对齐 SQL 查询列，完全匹配 SampleDO 写法） ==========
        MYSQL_ADD_FIELD_PK("id", "i", id);                // 主键：lesson.id（整型）
        MYSQL_ADD_FIELD("title", "s", title);             // 课程标题
        MYSQL_ADD_FIELD("sn", "s", sn);                   // 课程序号
        MYSQL_ADD_FIELD("date", "s", date);               // 上课日期
        MYSQL_ADD_FIELD("start_time", "s", start_time);   // 开始时间
        MYSQL_ADD_FIELD("end_time", "s", end_time);       // 结束时间
        MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);   // 教师ID
        MYSQL_ADD_FIELD("schedule_id", "i", schedule_id); // 排课计划ID
        MYSQL_ADD_FIELD("teacher_name", "s", teacher_name); // 教师姓名
        MYSQL_ADD_FIELD("sign_state", "i", sign_state);   // 签到状态
    }
};

//class GetTimeableDO : public BaseDO
//{
//    // ========== 1. 字段定义（类型严格对齐数据库） ==========
//    // lesson.id 是整型 → 用 int；如果是字符串主键才用 string
//    MYSQL_SYNTHESIZE(int, id, Id);
//    MYSQL_SYNTHESIZE(std::string, title, Title);
//    // lesson.sn 数据库里是字符串 → 改 string（如果是数字也可保留 int）
//    MYSQL_SYNTHESIZE(std::string, sn, Sn);
//    MYSQL_SYNTHESIZE(std::string, date, Date);
//    MYSQL_SYNTHESIZE(std::string, start_time, Start_time);
//    MYSQL_SYNTHESIZE(std::string, end_time, End_time);
//    MYSQL_SYNTHESIZE(int, teacher_id, Teacher_id);
//    MYSQL_SYNTHESIZE(int, schedule_id, Schedule_id);
//    // 注意：DO 里是 teacher_name（驼峰），SQL 里要对应 AS teacher_name
//    MYSQL_SYNTHESIZE(std::string, teacher_name, TeacherName);
//    MYSQL_SYNTHESIZE(int, sign_state, SignState);
//
//public:
//    GetTimeableDO() : BaseDO("sample")
//    {
//        // ========== 2. 映射顺序严格对齐 SQL 查询列 ==========
//        // SQL列顺序：id → title → sn → date → start_time → end_time → teacher_id → schedule_id → teacher_name → sign_state
//        MYSQL_ADD_FIELD_PK("id", "i", id);                // 对应 lesson.id（int）
//        MYSQL_ADD_FIELD("title", "s", title);             // 对应 lesson.title
//        MYSQL_ADD_FIELD("sn", "s", sn);                   // 对应 lesson.sn（字符串）
//        MYSQL_ADD_FIELD("date", "s", date);               // 对应 lesson.date
//        MYSQL_ADD_FIELD("start_time", "s", start_time);   // 对应 lesson.start_time
//        MYSQL_ADD_FIELD("end_time", "s", end_time);       // 对应 lesson.end_time
//        MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);   // 对应 lesson_teacher.teacher_id
//        MYSQL_ADD_FIELD("schedule_id", "i", schedule_id); // 对应 lesson.schedule_id
//        MYSQL_ADD_FIELD("teacher_name", "s", teacher_name); // 对应 staff.name AS teacher_name
//        MYSQL_ADD_FIELD("sign_state", "i", sign_state);   // 对应 lesson_student.sign_state
//    }
//};

//// 1. 注册主键字段（id是主键）
//MYSQL_ADD_FIELD_PK("id", "s", id);

//// 2. 注册普通字符串类型字段（标记 "s"）
//MYSQL_ADD_FIELD("title", "s", title);          // 课程标题
//MYSQL_ADD_FIELD("date", "s", date);            // 上课日期
//MYSQL_ADD_FIELD("start_time", "s", start_time);// 开始时间
//MYSQL_ADD_FIELD("end_time", "s", end_time);    // 结束时间
//MYSQL_ADD_FIELD("add_time", "s", add_time);    // 添加时间
//MYSQL_ADD_FIELD("edit_time", "s", edit_time);  // 修改时间
//MYSQL_ADD_FIELD("close_time", "s", close_time);// 结课时间

//// 3. 注册整型字段（标记 "i"）
//MYSQL_ADD_FIELD("sn", "i", sn);                // 课节数
//MYSQL_ADD_FIELD("course_id", "i", course_id);  // 课程id
//MYSQL_ADD_FIELD("schedule_id", "i", schedule_id);// 编排计划id
//MYSQL_ADD_FIELD("class_id", "i", class_id);    // 班级id
//MYSQL_ADD_FIELD("room_id", "i", room_id);      // 教室id
//MYSQL_ADD_FIELD("creator", "i", creator);      // 创建人
//MYSQL_ADD_FIELD("editor", "i", editor);        // 编辑人
//MYSQL_ADD_FIELD("deleted", "i", deleted);      // 删除标记
//MYSQL_ADD_FIELD("dec_count", "i", dec_count);  // 应扣课次数
//MYSQL_ADD_FIELD("close_operator", "i", close_operator);// 结课人
//MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);// 主讲人
//MYSQL_ADD_FIELD("bookable", "i", bookable);    // 是否开放预约
//MYSQL_ADD_FIELD("school_id", "i", school_id);  // 老师所属学校ID
//MYSQL_ADD_FIELD("org_id", "i", org_id);        // 创建者所属组织ID
// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GetTimeableDO> PtrGetTimeableDO;
#endif // !_TIMEABLE_DO_