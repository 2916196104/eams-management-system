#pragma once






#ifndef _LESSONCOMMENT_DO_
#define _LESSONCOMMENT_DO_
#include "../../DoInclude.h"



class LessonCommentDO : public BaseDO
{
    // 主键 ID
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 课程id
    MYSQL_SYNTHESIZE(uint64_t, lessonId, LessonId);
    // 班级id (为空表示调课生)
    MYSQL_SYNTHESIZE(int, classId, ClassId);
    // 学员id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 实扣课次
    MYSQL_SYNTHESIZE(int, decLessonCount, DecLessonCount);
    // 应扣课次
    MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
    // 点名的老师
    MYSQL_SYNTHESIZE(uint64_t, teacherId, TeacherId);
    // 签到时间
    MYSQL_SYNTHESIZE(string, signTime, SignTime);
    // 签到方式
    MYSQL_SYNTHESIZE(int, signType, SignType);
    // 签到结果
    MYSQL_SYNTHESIZE(int, signState, SignState);
    // 老师评分
    MYSQL_SYNTHESIZE(int, score, Score);
    // 老师评语
    MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
    // 评语时间
    MYSQL_SYNTHESIZE(string, evaluateTime, EvaluateTime);
    // 评语老师id
    MYSQL_SYNTHESIZE(uint64_t, evaluateTeacherId, EvaluateTeacherId);
    // 评语老师
    MYSQL_SYNTHESIZE(string, evaluateTeacher, EvaluateTeacher);
    // 实际消费课程
    MYSQL_SYNTHESIZE(uint64_t, consumeCourseId, ConsumeCourseId);
    // 消费课程与学生关联表ID
    MYSQL_SYNTHESIZE(uint64_t, consumeStudentCourseId, ConsumeStudentCourseId);
    // 学生的顾问
    MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
    // 加入时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 上课老师所属组织ID
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
public:
    LessonCommentDO() : BaseDO("lesson_student")
    {
       
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        MYSQL_ADD_FIELD("lesson_id", "ull", lessonId);
        MYSQL_ADD_FIELD("class_id", "i", classId);
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("dec_lesson_count", "i", decLessonCount);
        MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
        MYSQL_ADD_FIELD("teacher_id", "ull", teacherId);
        MYSQL_ADD_FIELD("sign_time", "s", signTime);
        MYSQL_ADD_FIELD("sign_type", "i", signType);
        MYSQL_ADD_FIELD("sign_state", "i", signState);
        MYSQL_ADD_FIELD("score", "i", score);
        MYSQL_ADD_FIELD("evaluation", "s", evaluation);
        MYSQL_ADD_FIELD("evaluate_time", "s", evaluateTime);
        MYSQL_ADD_FIELD("evaluate_teacher_id", "ull", evaluateTeacherId);
        MYSQL_ADD_FIELD("evaluate_teacher", "s", evaluateTeacher);
        MYSQL_ADD_FIELD("consume_course_id", "ull", consumeCourseId);
        MYSQL_ADD_FIELD("consume_student_course_id", "ull", consumeStudentCourseId);
        MYSQL_ADD_FIELD("counselor", "ull", counselor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("org_id", "ull", orgId);
    }
};
typedef std::shared_ptr<LessonCommentDO> PtrLessonCommentDO;


#endif