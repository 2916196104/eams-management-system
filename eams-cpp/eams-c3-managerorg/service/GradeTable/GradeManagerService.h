#pragma once
#ifndef _GRADE_MANAGER_SERVICE_H_
#define _GRADE_MANAGER_SERVICE_H_

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeManageDTO.h"
#include "domain/query/GradeTable/GradeManageQuery.h"

/**
 * 成绩管理服务实现
 */
class GradeManagerService
{
public:
	// 分页查询成绩列表
	GradeManagePageDTO::Wrapper listAll(const GradeManageQuery::Wrapper& query);
	// 保存成绩（新增/修改）
	uint64_t saveScore(const GradeManageDTO::Wrapper& dto, const PayloadDTO& payload);
	
	// 批量删除成绩
	bool removeScore(const oatpp::List<oatpp::String>& ids);
};

#endif // !_GRADE_MANAGER_SERVICE_H_
