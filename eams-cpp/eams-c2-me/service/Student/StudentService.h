#pragma once

#ifndef _STUDENTSERVICE_H_
#define _STUDENTSERVICE_H_

#include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/dto/student/StudentDTO.h"
#include "dao/student/StudentDAO.h"

class StudentService
{
private:
	//计算年龄(因为数据库只有birthday)
	int calculateAge(const std::string& birthday);
	//计算性别(因为数据库是tinyint 响应要求是string)
	std::string convertGender(int genderCode);
	//计算阶段(因为数据库是tinyint 响应要求是string)
	std::string convertStage(int stageCode);

public:
	//业务方法，查询学生列表，封装分页DTO
	StudentPageDTO::Wrapper listAll(const StudentQuery::Wrapper& query);

	 
};


#endif