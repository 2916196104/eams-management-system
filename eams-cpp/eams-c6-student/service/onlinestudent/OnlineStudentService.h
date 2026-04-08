#pragma once
#ifndef _ONLINESTUDENT_SERVICE_
#define _ONLINESTUDENT_SERVICE_

#include <list>
#include <vector>
#include <string>
#include "../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "domain/dto/onlinestudent/OnlineStudentDTO.h"
#include "domain/dto/common/CommonDTO.h"

class OnlineService
{
public:
	/**
	* 根据 ID 列表查询导出数据
	*/
	std::list<OnlineExportDTO::Wrapper> listByIds(const std::vector<std::string>& ids);
	
	/**
	* 导入学员数据
	*/
	StringJsonVO::Wrapper importExcel(const oatpp::String& excelData, const PayloadDTO& payload);
	
	/**
	* 修改学员顾问
	*/
	StringJsonVO::Wrapper modifyCounselor(const ModifyCounselorDTO::Wrapper& dto);
};

#endif