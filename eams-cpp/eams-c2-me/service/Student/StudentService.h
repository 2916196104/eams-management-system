#pragma once
#ifndef _STUDENTSERVICE_H_
#define _STUDENTSERVICE_H_

#include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/dto/student/StudentDTO.h"
#include "dao/student/StudentDAO.h"
#include <cstdint>  // 新增类型头文件

class StudentService
{
private:
	// 计算年龄
	int calculateAge(const std::string& birthday);
	// 【修改】int -> char，匹配DO的char类型
	std::string convertGender(char genderCode);
	// 【修改】int -> char，匹配DO的char类型
	std::string convertStage(char stageCode);

public:
	// 查询学生列表
	StudentPageDTO::Wrapper listAll(const StudentQuery::Wrapper& query);
};

#endif