#pragma once
#ifndef _MONTHLYDATADO_H_
#define _MONTHLYDATADO_H_
#include "../DoInclude.h"

class MonthlyDataViewDO : public BaseDO
{
	////编号
	//MYSQL_SYNTHESIZE(double, id, Id);
	//本月点名人次
	MYSQL_SYNTHESIZE(double, rollcall_count, Rollcall_count);
	//本月课次数
	MYSQL_SYNTHESIZE(double, lesson_count, Lesson_count);
	//本月新增学员
	MYSQL_SYNTHESIZE(double, student_count, Student_count);
	//月报名金额
	MYSQL_SYNTHESIZE(double, course_count, Course_count);
public:
	MonthlyDataViewDO() :BaseDO(std::string("")) {}
};
typedef std::shared_ptr<MonthlyDataViewDO> MonthlyDataViewDOPtr;


#endif

