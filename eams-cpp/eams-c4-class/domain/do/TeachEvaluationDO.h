#pragma once
#ifndef TEACHEVALUATION_H
#define TEACHEVALUATION_H
#include "../DoInclude.h"

class TeachEvaluationDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(int, id, Id);
	// 课次id
	MYSQL_SYNTHESIZE(int, lessonId, LessonId);
	// 老师id
	MYSQL_SYNTHESIZE(int, teacherId, TeacherId);
	// 综合评分
	MYSQL_SYNTHESIZE(int, score1, Score1);
	// 课堂气氛
	MYSQL_SYNTHESIZE(int, score2, Score2);
	// 授课态度
	MYSQL_SYNTHESIZE(int, score3, Score3);
	// 教学效果
	MYSQL_SYNTHESIZE(int, score4, Score4);
	// 评语
	MYSQL_SYNTHESIZE(string, content, Content);
	// 评价时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 学生id
	MYSQL_SYNTHESIZE(int, studentId, StudentId);
	// 是否匿名
	MYSQL_SYNTHESIZE(int, anonymity, Anonymity);
	// 被评价老师所属组织ID
	MYSQL_SYNTHESIZE(int, orgId, OrgId);

public:
	TeachEvaluationDO() : BaseDO("teach_evaluation")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 课次id
		MYSQL_ADD_FIELD("lesson_id", "i", lessonId);
		// 老师id
		MYSQL_ADD_FIELD("teacher_id", "i", teacherId);
		// 综合评分
		MYSQL_ADD_FIELD("score1", "i", score1);
		// 课堂气氛
		MYSQL_ADD_FIELD("score2", "i", score2);
		// 授课态度
		MYSQL_ADD_FIELD("score3", "i", score3);
		// 教学效果
		MYSQL_ADD_FIELD("score4", "i", score4);
		// 评语
		MYSQL_ADD_FIELD("content", "s", content);
		// 评价时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 学生id
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		// 是否匿名
		MYSQL_ADD_FIELD("anonymity", "i", anonymity);
		// 被评价老师所属组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};




// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<TeachEvaluationDO> PtrTeachEvaluationDO;
#endif