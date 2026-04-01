#pragma once
#ifndef _STUDENTSERVICE_H_
#define _STUDENTSERVICE_H_

#include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/dto/student/StudentDTO.h"
#include "dao/student/StudentDAO.h"
#include <cstdint>

class StudentService
{
private:
	int calculateAge(const std::string& birthday);
	// 改回 int，匹配 StudentDO 类型
	std::string convertGender(int genderCode);
	std::string convertStage(int stageCode);

public:
	StudentPageDTO::Wrapper listAll(const StudentQuery::Wrapper& query);
};

#endif