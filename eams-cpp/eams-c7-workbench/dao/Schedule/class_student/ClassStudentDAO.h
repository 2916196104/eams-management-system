#pragma once
#ifndef _CLASS_STUDENT_DAO_H_
#define _CLASS_STUDENT_DAO_H_
#include "BaseDAO.h"
#include "domain/do/Schedule/class_student/ClassStudentDO.h"
#include <list>

class ClassStudentDAO : public BaseDAO
{
public:
	std::list<int64_t> selectStudentIdsByClassId(int64_t classId);
	//获取班级学生人数
	int getStudentCountByClassId(int64_t classId);
};

#endif
