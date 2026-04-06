#pragma once
#include "BaseDAO.h"
#include "../domain/do/GradeDO.h"
#include "../domain/query/GradeQuery.h"

/**
 * 示例表数据库操作实现
 */

class GradeDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    GradeDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const GradeQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据GradeQuery对象动态构建查询条件相关参数
	//************************************
	
public:

	// 分页查询数据
	std::list<GradeDO> selectWithPage();
};