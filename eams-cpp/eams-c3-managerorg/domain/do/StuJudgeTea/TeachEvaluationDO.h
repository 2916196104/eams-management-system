#pragma once
#ifndef _STUJUDGETEA_DO_
#define _STUJUDGETEA_DO_
#include "../DoInclude.h"

/**
 * 课程数据库实体类
 */
class LessonDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, title, Title);
public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("title", "s", title);
	}
};

// 给StuJudgeTeaDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonDO> PtrLessonDO;

/**
 * 职员数据库实体类
 */
class OrgDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
public:
	OrgDO() : BaseDO("org")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
	}
};

// 给StuJudgeTeaDO智能指针设定一个别名方便使用
typedef std::shared_ptr<OrgDO> PtrOrgDO;


/**
 * 职员数据库实体类
 */
class UserDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
public:
	UserDO() : BaseDO("user")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
	}
};

// 给StuJudgeTeaDO智能指针设定一个别名方便使用
typedef std::shared_ptr<UserDO> PtrUserDO;


/**
 * 职员数据库实体类
 */
class StaffDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
public:
	StaffDO() : BaseDO("staff")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
	}
};

// 给StuJudgeTeaDO智能指针设定一个别名方便使用
typedef std::shared_ptr<StaffDO> PtrStaffDO;


/**
 * 学教评数据库实体类
 */
class StuJudgeTeaDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程编号
	MYSQL_SYNTHESIZE(uint64_t, lesson_id, LessonId);
	// 老师编号
	MYSQL_SYNTHESIZE(uint64_t, teacher_id, TeacherId);
	// 第一项评分
	MYSQL_SYNTHESIZE(uint32_t, score1, Score1);
	// 第二项评分
	MYSQL_SYNTHESIZE(uint32_t, score2, Score2);
	// 第三项评分
	MYSQL_SYNTHESIZE(uint32_t, score3, Score3);
	// 第四项评分
	MYSQL_SYNTHESIZE(uint32_t, score4, Score4);
	// 评价内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 评价时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 学生编号
	MYSQL_SYNTHESIZE(uint64_t, student_id, StudentId);
	// 是否匿名
	MYSQL_SYNTHESIZE(int, anonymity, Anonymity);
	// 老师所属组织编号
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);

	// 关联一个文件实体，存储头像文件信息
	CC_SYNTHESIZE(PtrStaffDO, staff, Staff);
	CC_SYNTHESIZE(PtrLessonDO, lesson, Lesson);
	CC_SYNTHESIZE(PtrOrgDO, org, Org);
	CC_SYNTHESIZE(PtrUserDO, user, User);
public:
	StuJudgeTeaDO() : BaseDO("teach_evaluation")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("lesson_id", "ull", lesson_id);
		MYSQL_ADD_FIELD("teacher_id", "ull", teacher_id);
		MYSQL_ADD_FIELD("score1", "ui", score1);
		MYSQL_ADD_FIELD("score2", "ui", score2);
		MYSQL_ADD_FIELD("score3", "ui", score3);
		MYSQL_ADD_FIELD("score4", "ui", score4);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("student_id", "ull", student_id);
		MYSQL_ADD_FIELD("anonymity", "i", anonymity);
		MYSQL_ADD_FIELD("org_id", "ull", org_id);
	}
};

// 给StuJudgeTeaDO智能指针设定一个别名方便使用
typedef std::shared_ptr<StuJudgeTeaDO> PtrStuJudgeTeaDO;
#endif // !_STUJUDGETEA_DO_