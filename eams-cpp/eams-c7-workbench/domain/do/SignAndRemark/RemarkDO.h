#pragma once
#ifndef _REMARKDO_H_
#define _REMARKDO_H_

#include "../DoInclude.h"

class RemarkDO : public BaseDO
{
	//主键字段
	MYSQL_SYNTHESIZE(int, id, Id);
	//学生id
	//MYSQL_SYNTHESIZE(int, stu_id, Stu_id);
	//老师评语
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//课堂评分
	MYSQL_SYNTHESIZE(int, score, Score);
	//评价时间
	MYSQL_SYNTHESIZE(string, remark_time, Remark_time);
	//评价老师id
	//MYSQL_SYNTHESIZE(int, remark_teacher, Remark_teacher);

	RemarkDO() :BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		//MYSQL_ADD_FIELD("student_id", "i", stu_id);
		MYSQL_ADD_FIELD("evaluation", "s", remark);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("evalute_time", "s", remark_time);
		//MYSQL_ADD_FIELD("evalute_teacher", "i", remark_teacher);
	}
};

//定义一个点名记录实体的智能指针
typedef std::shared_ptr<RemarkDO> PtrRemarkDO;

class RemarkViewDO :public RemarkDO
{
	//学生姓名
	MYSQL_SYNTHESIZE(string, stu_name, Stu_name);
	//老师姓名
	MYSQL_SYNTHESIZE(string, teacher_name, Teacher_name);
};

typedef std::shared_ptr<RemarkViewDO> PtrRemarkViewDO;

#endif // !_REMARKDO_H_
