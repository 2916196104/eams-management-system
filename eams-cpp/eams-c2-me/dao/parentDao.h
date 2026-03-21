#pragma once
#include "../include/BaseDAO.h"
#include "domain/query/PageQuery.h"
#include "domain/do/parentDO.h"
#include "domain/mapper/parentMapper.h"
class parentDAO : public BaseDAO {
private:
	// 私有辅助方法：构建查询条件
	std::string queryListBuilder(
		const ListQuery::Wrapper& query,
		SqlParams& params
	);
	std::string queryDetailBuilder(
		const DetailQuery::Wrapper& query,
		SqlParams& params
	);

public:
	// 查询方法
	uint64_t count(const ListQuery::Wrapper& query);
	std::list<ParentDO> selectWithList(const ListQuery::Wrapper& query);
	PtrParentDO selectById(std::string id);
};