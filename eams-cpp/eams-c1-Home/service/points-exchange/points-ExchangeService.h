#pragma once

/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/23
*/
#ifndef _EXCHANGE_SERVICE_H_
#define _EXCHANGE_SERVICE_H_
#include "stdafx.h"
#include "../../domain/dto/points-exchange/exchangeDTO.h"
#include "domain/query/points-exchange/exchangequery.h"
#include"domain/do/points-exchange/exchangeDo.h"
#include"dao/points-exchange/exchangeDAO.h"
#include"dao/points-exchange/GoodsDAO.h"
#include "../../dao/points-exchange/points-ExchangeDAO.h"
class ExchangeService
{
private:
	std::shared_ptr<GoodsDAO>m_goodsDao;
	std::shared_ptr<ExchangeDAO>m_exchangeDao;


public:

	// 兑换提交
	ExchangeResultDTO::Wrapper submitExchange(const ExchangeSubmitDTO::Wrapper& request, const std::int64_t & userid);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	GoodsDetailDTO::Wrapper getGoodsDetail(const int64_t& id);

};

#endif // !_EXCHANGE_SERVICE_H_