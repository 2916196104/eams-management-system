/*
 @Author: abinng
 @Date: 2026/03/23 11:38:08
 @File: ReviewDO.h
*/
#pragma once

#ifndef _REVIEWDO_H_
#define _REVIEWDO_H_

/**
 * 课时学员表数据模型
 */
class LessonStudentDO : public BaseDO {
	// 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 课程id
    MYSQL_SYNTHESIZE(uint64_t, lessonId, LessonId)
	// 评语老师
    MYSQL_SYNTHESIZE(uint64_t, evaluateTeacher, EvaluateTeacher);
    // 老师评语
    MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
    // 老师评分
    MYSQL_SYNTHESIZE(int8_t, score, Score);
    // 评价时间
    MYSQL_SYNTHESIZE(string, evaluateTime, EvaluateTime);

public:
    LessonStudentDO() : BaseDO("lesson_student")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("lesson_id", "ull", lessonId, false);
        MYSQL_ADD_FIELD_NULLABLE("evaluate_teacher", "ull", evaluateTeacher, true);
        MYSQL_ADD_FIELD_NULLABLE("evaluation", "s", evaluation, true);
        MYSQL_ADD_FIELD_NULLABLE("score", "c", score, true);
        MYSQL_ADD_FIELD_NULLABLE("evaluate_time", "s", evaluateTime, true);
    }
};

// 给LessonStudentDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

/**
 * 点评记录视图对象，关联一些外表的字段
 */
class ReviewViewDO : public LessonStudentDO {
    MYSQL_SYNTHESIZE(string, lessonTitle, LessonTitle); // 关联lesson表的title字段
};

// 给ReviewViewDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ReviewViewDO> PtrReviewViewDO;

#endif //!_REVIEWDO_H_