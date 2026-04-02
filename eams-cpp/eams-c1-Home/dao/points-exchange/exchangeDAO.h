#pragma once
#ifndef _EXCHANGEDAO_H_
#define _EXCHANGEDAO_H_ 

#include "BaseDAO.h"
#include "domain/do/points-exchange/exchangeDo.h"
#include "domain/dto/points-exchange/exchangeDTO.h"
#include "domain/query/points-exchange/exchangequery.h"

class exchangeDAO : public BaseDAO
{
public:
	// 统计是否存在可兑换商品
	uint64_t count1();
	// 查询所有商品
	std::list<PtrGoodsDO> selectAllGoods(const PageQuery::Wrapper& query);
	// 统计当前用户是否已兑换过商品
	uint64_t count2(const AcceptGoodsQuery::Wrapper& query);
	// 查询当前用户已获得商品
	std::list<PtrAcceptGoodsDO> selectAcceptGoods(const AcceptGoodsQuery::Wrapper& query);
	// 查询规则
	PtrSettingDO selectById(uint64_t id);
};


#endif