#pragma once
#ifndef _GET_CREDIT_MALL_LIST_SERVICE_H_
#define _GET_CREDIT_MALL_LIST_SERVICE_H_

#include "domain/query/home/credit/GetCreditMallListQuery.h"
#include "domain/dto/home/credit/GetCreditMallListDTO.h"

/**
 * 获取积分商品业务逻辑类
 */
class CreditMallListService
{
private:
	// 获取文件服务器地址
	//inline string getDfsServerAddrssUrl();
public:
	// 查询所有积分商品
	CreditMallListPageDTO::Wrapper listAll(const CreditMallListQuery::Wrapper& query);
	// 查询单个积分商品详细
	//CreditMallDetailDTO::Wrapper getCreditMallDetail(const oatpp::Int32& id);
};



#endif // !_GET_CREDIT_MALL_LIST_SERVICE_H_