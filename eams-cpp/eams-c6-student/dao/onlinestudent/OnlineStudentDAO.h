#pragma once
#ifndef _ONLINESTUDENT_DAO_
#define _ONLINESTUDENT_DAO_

#include "BaseDAO.h"
#include "OnlineStudentMapper.h"
#include <vector>
#include <string>
#include "domain/dto/onlinestudent/OnlineStudentDTO.h"

class OnlineExportDAO : public BaseDAO
{
public:
	std::list<PtrStudentDetail> selectByIds(const std::vector<std::string>& ids);
};

class OnlineImportDAO : public BaseDAO
{
public:
	// 导入学员数据
	int importStudents(const std::vector<OnlineAddDTO::Wrapper>& students);
};

class OnlineStudentDAO : public BaseDAO
{
public:
	// 修改学员顾问
	int updateCounselor(const std::vector<std::string>& studentIds, const std::string& counselorName, const std::string& counselorId);
};

#endif