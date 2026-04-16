#pragma once
#ifndef _REMARKDAO_H_
#define _REMARKDAO_H_

#include "BaseDAO.h"
#include "domain/do/SignAndRemark/RemarkDO.h"
#include "domain/dto/SignAndRemark/RemarkDTO.h"
#include "domain/query/SignAndRemark/RemarkQuery.h"

class RemarkDAO : public BaseDAO
{
public:
	//获取数据条数
	uint64_t count(const RemarkQuery::Wrapper& query);
	// 获取点评记录列表
	std::list<PtrRemarkViewDO> selectAll(const RemarkQuery::Wrapper& query);
};

#endif
