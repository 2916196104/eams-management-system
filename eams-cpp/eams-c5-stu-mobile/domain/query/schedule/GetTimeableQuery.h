#pragma once

#ifndef _TIMEABLE_QUERY
#define _TIMEABLE_QUERY
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
// 类名从 ClassQuery 改为 ClassStudentQuery，继承关系不变
class GetTimeableQuery : public PageQuery
{
    DTO_INIT(GetTimeableQuery, PageQuery);  // 初始化宏同步替换类名
    //DTO_FIELD(Int32, student_id);            // 字段名保持不变（与数据库字段对应）
    //DTO_FIELD_INFO(student_id) {
    //    info->description = "";
    //}
    //对应数据库字段
    // 1. 学生ID（bigint unsigned → Int64）
    DTO_FIELD(Int64, student_id);
    DTO_FIELD_INFO(student_id) {
        info->description = ZH_WORDS_GETTER("Timeable.field.id");
    }
    DTO_FIELD(String, date);
    DTO_FIELD_INFO(date) {
        info->description = ZH_WORDS_GETTER("Timeable.field.data");
    }
};

//// 2. 所属课程ID（bigint → Int64，NOT NULL）
//DTO_FIELD(Int64, course_id);
//DTO_FIELD_INFO(course_id) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.course_id");
//}
////3.章节标题(varchar(255))
//DTO_FIELD(String, title);
//DTO_FIELD_INFO(title) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.title");
//}
////4.计划课时数(int)
//DTO_FIELD(Int64, lesson_count);
//DTO_FIELD_INFO(lesson_count) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.lesson_count");
//}
////5.创建人(bigint → Int64，NOT NULL)
//DTO_FIELD(String, creator);
//DTO_FIELD_INFO(creator) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.creato");
//}
////6.编辑者(bigint → Int64，NOT NULL)
//DTO_FIELD(String, editor);
//DTO_FIELD_INFO(editor) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.editor");
//}
////7.添加时间（datetime → String）
//DTO_FIELD(String, add_time);
//DTO_FIELD_INFO(add_time) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.add_time");
//}
////8..修改时间（datetime → String）
//DTO_FIELD(String, edit_time);
//DTO_FIELD_INFO(edit_time) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.edit_time");
//}
////9.删除标记（tinyint(1) → Boolean，DEFAULT '0'）
//DTO_FIELD(String, deleted);
//DTO_FIELD_INFO(deleted) {
//    info->description = ZH_WORDS_GETTER("Timeable.field.deleted");

//}
#include OATPP_CODEGEN_END(DTO)
#endif // !_TIMEABLE_QUERY