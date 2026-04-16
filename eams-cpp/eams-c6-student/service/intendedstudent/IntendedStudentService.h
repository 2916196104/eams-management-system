#pragma once
#ifndef _INTENDEDSTUDENT_SERVICE_
#define _INTENDEDSTUDENT_SERVICE_

#include <list>
#include <vector>
#include "domain/dto/intendedstudent/IntendedStudentDTO.h"

class IntendedService
{
public:
	/**
	* 根据 ID 列表查询导出数据
	*/
	std::list<IntendedExportDTO::Wrapper> listByIds(const std::vector<std::string>& ids);
	/**
	* 保存数据
	*/
	bool importBatch(const oatpp::List<IntendedAddDTO::Wrapper>& datas);
};

#endif