#pragma once

#ifndef _STUDENTDAO_H_
#define _STUDENTDAO_H_

#include "BaseDAO.h"
#include "domain/do/Student/StudentDO.h"
#include "domain/dto/student/StudentDTO.h"
#include "domain/query/StudentQuery/StudentQuery.h"

class StudentDAO :public BaseDAO
{

public:
	// 获取数据条数
	uint64_t count(const StudentQuery::Wrapper& query);
	// 获取用户列表
	std::list<PtrStudentDO> selectAll(const StudentQuery::Wrapper& query);
	// 通过编号获取指定用户(没实现，暂留拓展)
	PtrStudentDO selectById(const string& id);
};


#endif
