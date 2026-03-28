#pragma once
#ifndef _ONLINESTUDENT_SERVICE_
#define _ONLINESTUDENT_SERVICE_

#include <list>
#include <vector>
#include "domain/dto/onlinestudent/OnlineStudentDTO.h"

class OnlineService
{
public:
	/**
	* 根据 ID 列表查询导出数据
	*/
	std::list<OnlineExportDTO::Wrapper> listByIds(const std::vector<std::string>& ids);
};

#endif