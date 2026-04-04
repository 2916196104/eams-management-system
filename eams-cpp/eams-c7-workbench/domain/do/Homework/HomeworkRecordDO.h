#pragma once

#ifndef _HOMEWORK_RECORD_DO_H_
#define _HOMEWORK_RECORD_DO_H_

#include "../DoInclude.h"

/**
 * 作业提交记录表数据对象（对应 homework_record 表）
 */
class HomeworkRecordDO : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 所属作业ID
    MYSQL_SYNTHESIZE(uint64_t, homeworkId, HomeworkId);
    // 学生ID
    MYSQL_SYNTHESIZE(int64_t, studentId, StudentId);
    // 提交时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 提交内容
    MYSQL_SYNTHESIZE(string, content, Content);
    // 点评分数
    MYSQL_SYNTHESIZE(int32_t, score, Score);
    // 评语
    MYSQL_SYNTHESIZE(string, comment, Comment);
    // 点评时间
    MYSQL_SYNTHESIZE(string, commentTime, CommentTime);
    // 点评老师ID
    MYSQL_SYNTHESIZE(int64_t, commentTeacher, CommentTeacher);
    // 附件图片ID（逗号分隔）
    MYSQL_SYNTHESIZE(string, images, Images);

public:
    HomeworkRecordDO() : BaseDO("homework_record")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);
        MYSQL_ADD_FIELD("homework_id", "i", homeworkId);
        MYSQL_ADD_FIELD("student_id", "i", studentId);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("content", "s", content);
        MYSQL_ADD_FIELD("score", "i", score);
        MYSQL_ADD_FIELD("comment", "s", comment);
        MYSQL_ADD_FIELD("comment_time", "s", commentTime);
        MYSQL_ADD_FIELD("comment_teacher", "i", commentTeacher);
        MYSQL_ADD_FIELD("images", "s", images);
    }
};

typedef std::shared_ptr<HomeworkRecordDO> PtrHomeworkRecordDO;

#endif // _HOMEWORK_RECORD_DO_H_