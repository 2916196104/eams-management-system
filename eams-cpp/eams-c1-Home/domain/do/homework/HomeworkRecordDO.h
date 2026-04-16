#pragma once

#ifndef _HOMEWORK_RECORD_DO_H_
#define _HOMEWORK_RECORD_DO_H_

#include "../DoInclude.h"

/**
 * 作业记录表实体类
 */
class HomeworkRecordDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(uint64_t, id, id);
    //作业ID
    MYSQL_SYNTHESIZE(uint64_t, homeworkId, homework_id);
    // 学生ID
    MYSQL_SYNTHESIZE(uint64_t, studentId, student_id);
    // 提交时间
    MYSQL_SYNTHESIZE(string, addTime, add_time);
    // 作业内容
    MYSQL_SYNTHESIZE(string, content, content);
    // 分数
    MYSQL_SYNTHESIZE(int, score, score);
    // 评语
    MYSQL_SYNTHESIZE(string, comment, comment);
    // 评论时间
    MYSQL_SYNTHESIZE(string, commentTime, comment_time);
    // 评论老师ID
    MYSQL_SYNTHESIZE(uint64_t, commentTeacher, comment_teacher);
    // 图片附件
    MYSQL_SYNTHESIZE(string, images, images);

public:
    HomeworkRecordDO() : BaseDO("homework_record")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD("homework_id", "ull", homeworkId);
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("add_time", "dt", addTime);
        MYSQL_ADD_FIELD("content", "s", content);
        MYSQL_ADD_FIELD("score", "i", score);
        MYSQL_ADD_FIELD("comment", "s", comment);
        MYSQL_ADD_FIELD("comment_time", "dt", commentTime);
        MYSQL_ADD_FIELD("comment_teacher", "ull", commentTeacher);
        MYSQL_ADD_FIELD("images", "s", images);
    }
};

typedef std::shared_ptr<HomeworkRecordDO> PtrHomeworkRecordDO;

#endif