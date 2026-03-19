#pragma once

#include "BaseDAO.h"
#include "../domain/do/PointDO.h"
#include "../domain/query/PointQuery.h"

/**
 * 示例表数据库操作实现
 */

class PointDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    PointDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const PointQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据PointQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const PointQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const PointQuery::Wrapper& query);
	// 分页查询数据
	std::list<PointDO> selectWithPage(const PointQuery::Wrapper& query);
	// 通过姓名查询数据
	std::list<PointDO> selectByName(const string& name);
	// 通过ID查询数据
	std::shared_ptr<PointDO> selectById(std::string id);
};
 // !_SAMPLE_DAO_



