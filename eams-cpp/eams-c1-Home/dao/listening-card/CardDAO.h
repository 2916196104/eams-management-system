#pragma once

#ifndef _CARD_DAO_H_
#define _CARD_DAO_H_
#include "BaseDAO.h"
#include "domain/do/listening-card/cardDO.h"

class CardDAO : BaseDAO{
public:
    /**
     * 查询所有可领取的试听卡
     * 条件：启用状态(state=1)、未删除(deleted=0)、未过期(end_date >= CURDATE())
     * 排序：按添加时间倒序(add_time DESC)
     */
    std::list<CardDO> queryAvailableCards();
};

#endif // !_CARD_DAO_H_