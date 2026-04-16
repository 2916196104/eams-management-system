#pragma once

#ifndef _HOMEWORKDTO_XXYJ_H_
#define _HOMEWORKDTO_XXYJ_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 布置作业表单数据（对应 homework 表）
 */
class AssignHomeworkFormDTO : public oatpp::DTO
{
    DTO_INIT(AssignHomeworkFormDTO, DTO);

    // 班级ID
    API_DTO_FIELD_REQUIRE(Int64, classId, ZH_WORDS_GETTER("homework.field.class-id"), true);

    // 作业标题
    API_DTO_FIELD_REQUIRE(String, title, ZH_WORDS_GETTER("homework.field.title"), true);

    // 作业内容
    API_DTO_FIELD_REQUIRE(String, content, ZH_WORDS_GETTER("homework.field.content"), true);

    // 附件图片ID
    API_DTO_FIELD_DEFAULT(String, images, ZH_WORDS_GETTER("homework.field.images"));
};

/**
 * 布置作业完整请求DTO
 */
class AssignHomeworkDTO : public AssignHomeworkFormDTO
{
    DTO_INIT(AssignHomeworkDTO, AssignHomeworkFormDTO);
};

/**
 * 点评作业表单数据（对应 homework_record 表）
 */
class ReviewHomeworkFormDTO : public oatpp::DTO
{
    DTO_INIT(ReviewHomeworkFormDTO, DTO);

    // 作业提交记录ID
    API_DTO_FIELD_REQUIRE(Int64, recordId, ZH_WORDS_GETTER("homework.field.record-id"), true);

    // 打分
    API_DTO_FIELD_REQUIRE(Int32, score, ZH_WORDS_GETTER("homework.field.score"), true);

    // 评语
    API_DTO_FIELD_DEFAULT(String, comment, ZH_WORDS_GETTER("homework.field.comment"));
};

/**
 * 点评作业完整请求DTO
 */
class ReviewHomeworkDTO : public ReviewHomeworkFormDTO
{
    DTO_INIT(ReviewHomeworkDTO, ReviewHomeworkFormDTO);
    // 点评老师ID可以从token获取
};

/**
 * 作业提交记录DTO
 */
class HomeworkRecordDTO : public oatpp::DTO
{
    DTO_INIT(HomeworkRecordDTO, DTO);

    API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("homework.field.record-id"));
    API_DTO_FIELD_DEFAULT(Int64, studentId, ZH_WORDS_GETTER("homework.field.student-id"));
    API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("homework.field.student-name"));
    API_DTO_FIELD_DEFAULT(String, studentNo, ZH_WORDS_GETTER("homework.field.student-no"));
    API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("homework.field.content"));
    API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("homework.field.add-time"));
    API_DTO_FIELD_DEFAULT(Int32, score, ZH_WORDS_GETTER("homework.field.score"));
    API_DTO_FIELD_DEFAULT(String, comment, ZH_WORDS_GETTER("homework.field.comment"));
    API_DTO_FIELD_DEFAULT(String, commentTime, ZH_WORDS_GETTER("homework.field.comment-time"));
    API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("homework.field.teacher-name"));
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("homework.field.status"));
};

/**
 * 作业详情DTO（返回给前端）
 */
class HomeworkDetailDTO : public oatpp::DTO
{
    DTO_INIT(HomeworkDetailDTO, DTO);

    // 作业基本信息
    API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("homework.field.id"));
    API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("homework.field.title"));
    API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("homework.field.content"));
    API_DTO_FIELD_DEFAULT(Int64, classId, ZH_WORDS_GETTER("homework.field.class-id"));
    API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("homework.field.class-name"));
    API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("homework.field.teacher-name"));
    API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("homework.field.add-time"));

    // 提交记录列表
    API_DTO_FIELD_DEFAULT(Vector<oatpp::Object<HomeworkRecordDTO>>, records, ZH_WORDS_GETTER("homework.field.records"));

    // 统计信息
    API_DTO_FIELD_DEFAULT(Int32, totalStudents, ZH_WORDS_GETTER("homework.field.total-students"));
    API_DTO_FIELD_DEFAULT(Int32, submittedCount, ZH_WORDS_GETTER("homework.field.submitted"));
    API_DTO_FIELD_DEFAULT(Int32, reviewedCount, ZH_WORDS_GETTER("homework.field.reviewed"));
};

/**
 * 作业提交记录列表DTO
 */
class HomeworkRecordListDTO : public oatpp::DTO
{
    DTO_INIT(HomeworkRecordListDTO, DTO);

    API_DTO_FIELD_DEFAULT(Int64, homeworkId, ZH_WORDS_GETTER("homework.field.id"));
    API_DTO_FIELD_DEFAULT(Vector<oatpp::Object<HomeworkRecordDTO>>, list, ZH_WORDS_GETTER("homework.field.list"));
};

/**
 * 点评结果DTO
 */
class ReviewResultDTO : public oatpp::DTO
{
    DTO_INIT(ReviewResultDTO, DTO);

    API_DTO_FIELD_DEFAULT(Boolean, success, ZH_WORDS_GETTER("homework.field.success"));
    API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("homework.field.message"));
    API_DTO_FIELD_DEFAULT(Int64, recordId, ZH_WORDS_GETTER("homework.field.record-id"));

};
#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKDTO_XXYJ_H_