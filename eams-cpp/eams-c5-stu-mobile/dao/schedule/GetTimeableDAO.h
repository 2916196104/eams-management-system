#pragma once
#ifndef _TIMEABLE_DAO_
#define _TIMEABLE_DAO_
#include "BaseDAO.h"
#include "../../domain/do/schedule/GetTimeableDO.h"
#include "../../domain/query/schedule/GetTimeableQuery.h"

/**
 * 示例表数据库操作实现
 */
class GetTimeableDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const GetTimeableQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const GetTimeableQuery::Wrapper& query);
	// 分页查询数据
	std::list<GetTimeableDO> selectWithPage(const GetTimeableQuery::Wrapper& query);
	//// 通过姓名查询数据
	//std::list<GetTimeableDO> selectByName(const string& name);
	//// 通过ID查询数据
	//PtrGetTimeableDO selectById(std::string id);
};
#endif // !_TIMEABLE_DAO_