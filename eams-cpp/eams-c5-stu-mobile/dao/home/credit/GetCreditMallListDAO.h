#pragma once
#ifndef _GET_CREDIT_MALL_LIST_DAO_H_
#define _GET_CREDIT_MALL_LIST_DAO_H_
#include "BaseDAO.h"
#include "domain/do/home/credit/GetCreditMallListDO.h"
#include "domain/dto/home/credit/GetCreditMallListDTO.h"
#include "domain/query/home/credit/GetCreditMallListQuery.h"

/**
* 获取积分商品的数据操作类
*/
class CreditMallListDAO : public BaseDAO
{
public:
	// 获取数据条数
	uint64_t count(const CreditMallListQuery::Wrapper& query);
	// 获取积分商品列表
	std::list<PtrCreditMallListDO> selectAll(const CreditMallListQuery::Wrapper& query);
	// 通过商品ID获得商品详细信息
	//PtrCreditMallDO selectDetail(const int& id);


};

#endif // !_GET_CREDIT_MALL_LIST_DAO_H_
