#pragma once
#include "../include/BaseDAO.h"
#include "domain/query/PageQuery.h"
#include "domain/do/manualDO.h"
#include "domain/mapper/manualMapper.h"
class manualDAO : public BaseDAO {
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
	std::list<ManualDO> showList(const ListQuery::Wrapper& query);
	PtrManualDO selectById(std::string id);
};
