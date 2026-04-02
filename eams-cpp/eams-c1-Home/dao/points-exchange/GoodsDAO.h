// dao/points-exchange/GoodsDAO.h
#pragma once

/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/23
*/
#ifndef _GOODS_DAO_H_
#define _GOODS_DAO_H_

#include "domain/GlobalInclude.h"
#include "../../domain/do/points-exchange/exchangeDo.h"
#include "BaseDAO.h"

/**
 * 积分礼品数据访问层
 * 对应 credit_mall 表
 */
class GoodsDAO : public  BaseDAO
{
private:
    
public:
    GoodsDAO();
    
    
    /**
     * 根据ID查询礼品详情
     * @param id 礼品ID
     * @return 礼品DO对象
     */
     PtrGoodsDetailDO selectById(const int64_t& id);

    /**
     * 增加浏览次数
     * @param id 礼品ID
     * @return 影响行数
     */
    int incrementViewNum(const int64_t& id);

    /**
     * 扣减库存
     * @param id 礼品ID
     * @param num 扣减数量
     * @return 影响行数
     */
    int updateStorage(const int64_t& id, const int64_t& num);

    /**
     * 增加销量
     * @param id 礼品ID
     * @param num 增加数量
     * @return 影响行数
     */
    int updateSaleNum(const int64_t& id, const int64_t& num);

   
};

#endif // !_GOODS_DAO_H_