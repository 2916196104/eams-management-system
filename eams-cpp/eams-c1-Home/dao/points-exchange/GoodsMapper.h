// mapper/points-exchange/GoodsMapper.h
#pragma once

/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/23
*/
#ifndef _GOODS_MAPPER_H_
#define _GOODS_MAPPER_H_

#include "domain/GlobalInclude.h"
#include "../../domain/do/points-exchange/exchangeDo.h"
#include <memory>

/**
 * 礼品映射器 - 负责将 ResultSet 转化为 GoodsDetailDO 对象
 */
class GoodsMapper {
public:
    /**
     * 映射单条详细记录
     * @param result 结果集
     * @return GoodsDetailDO 智能指针
     */
    static PtrGoodsDetailDO mapper(ResultSet* result )
    {
        
        
        // 创建 DO 对象
        PtrGoodsDetailDO goods = std::make_shared<GoodsDO>();
        
        // 按照数据库字段映射
       
        goods->setId(std::stoull(result->getString("id")));
        goods->setDeleted(result->getInt("deleted"));
        goods->setSchoolId(std::stol(result->getString("school_id")));
        goods->setAddTime(result->getString("add_time"));
        goods->setEditTime(result->getString("edit_time"));
        goods->setCreator(std::stol(result->getString("creator")));
        goods->setEditor(std::stol(result->getString("editor")));
        goods->setMaterialId(std::stol(result->getString("material_id")));
        goods->setCategoryId(std::stol(result->getString("category_id")));
        goods->setCategoryName(result->getString("category_name"));
        goods->setName(result->getString("name"));
        goods->setCredit(std::stol(result->getString("credit")));        // 改为 getString
        goods->setSaleNum(result->getInt64("sale_num"));
        goods->setViewNum(result->getInt64("view_num"));
        goods->setCover(result->getString("cover"));
        goods->setContent(result->getString("content"));
        goods->setState(result->getInt("state"));
        goods->setOrgId(std::stol(result->getString("org_id")));
        return goods;
    }
};

#endif // !_GOODS_MAPPER_H_