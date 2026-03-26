#pragma once
#ifndef _EXCHANGESERVICE_H_
#define _EXCHANGESERVICE_H_ 

#include "domain/query/points-exchange/exchangequery.h"
#include "domain/dto/points-exchange/exchangeDTO.h"


class exchangeService
{
private:
	// 获取文件服务器地址
	inline string getDfsServerAddrssUrl();

public:
	// 获取积分礼品列表
	GoodsPageDTO::Wrapper listAllGoods(const PageQuery::Wrapper& query);
	// 获取兑换记录列表
	AcceptGoodsPageDTO::Wrapper listAcceptGoods(const AcceptGoodsQuery::Wrapper& query);
	// 获取积分兑换规则
	SettingDTO::Wrapper getSetting(UINT64 id);
};


#endif