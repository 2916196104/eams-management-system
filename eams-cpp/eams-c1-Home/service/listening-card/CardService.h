#pragma once
#ifndef _CARD_SERVICE_
#define _CARD_SERVICE_

#include "domain/vo/listening-card/CardVO.h"
#include "domain/query/listening-card/CardQuery.h"
#include "domain/dto/listening-card/CardDTO.h"
/**
 * 获取所有试听卡服务实现
 */
class CardService
{
public:
	// 查询可领取的试听卡列表（返回 DTO 列表的 shared_ptr）
	oatpp::List<cardDTO::Wrapper> getAvailableCardList();
	// 获取试听卡使用规则
	cardRuleDTO::Wrapper getCardUsageRules();
};

#endif // !_CARD_SERVICE_

