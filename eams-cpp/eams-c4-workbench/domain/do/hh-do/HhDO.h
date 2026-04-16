#pragma once
#ifndef _HH_DO_
#define _HH_DO_

#include "../StudentDO.h"
#include "../CourseDO.h"

class HhStudentViewDO : public StudentDO {
	// 电话号码
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 年龄
	MYSQL_SYNTHESIZE(int, age, Age);
};

class HhCourseViewDO : public CourseDO {
	// 学习进度
	MYSQL_SYNTHESIZE(string, progress, Progress);
	// 有效期
	MYSQL_SYNTHESIZE(string, deadline, DeadLine);
	// 剩余次数
	MYSQL_SYNTHESIZE(int, rest_times, RestTimes);
};

typedef std::shared_ptr<HhStudentViewDO> PtrHhStudentViewDO;
typedef std::shared_ptr<HhCourseViewDO> PtrHhCourseViewDO;


#endif