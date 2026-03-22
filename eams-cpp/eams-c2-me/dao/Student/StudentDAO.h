#pragma once

#ifndef _STUDENTDAO_H_
#define _STUDENTDAO_H_

#include "BaseDAO.h"
#include "domain/do/Student/StudentDO.h"
#include "domain/dto/student/StudentDTO.h"
#include "domain/query/Student/IdQuery.h"
class StudentDAO :public BaseDAO
{

public:

	//通过编号删除指定用户
	bool deleteById(const uint64_t & id);
};


#endif
