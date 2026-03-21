#pragma once
#include "../include/BaseDAO.h"
#include "domain/query/PageQuery.h"
#include "domain/do/parentDO.h"
#include "domain/mapper/parentMapper.h"
class parentDAO : public BaseDAO {
private:
	// 私有辅助方法：构建查询条件
	
	//查询说明列表信息的sql语句构建器
	std::string queryListBuilder(
		const ListQuery::Wrapper& query,
		SqlParams& params
	);

	//查询说明列表某一详细信息的sql语句构建器
	std::string queryDetailBuilder(
		const DetailQuery::Wrapper& query,
		SqlParams& params
	);

public:
	// 查询方法
	uint64_t count();
	std::list<ParentDO> showList(const ListQuery::Wrapper& query);
	PtrParentDO selectById(std::string id);
};