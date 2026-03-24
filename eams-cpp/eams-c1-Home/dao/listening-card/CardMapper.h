#pragma once

#ifndef _CARD_MAPPER_H_
#define _CARD_MAPPER_H_

#include "Mapper.h"
#include "domain/do/listening-card/cardDO.h"

/**
 * 试听卡表字段匹配映射 - 返回普通对象
 */
class CardMapper : public Mapper<CardDO>
{
public:
    CardDO mapper(ResultSet* resultSet) const override
    {
        CardDO data;
        // 列索引必须与 SELECT 语句中的字段顺序一致
        data.setId(resultSet->getUInt64(1));           // id
        data.setCourseId(resultSet->getUInt64(2));     // course_id
        data.setTitle(resultSet->getString(3));        // title
        data.setQuantity(resultSet->getInt(4));        // quantity
        data.setRemainingQuantity(resultSet->getInt(5)); // remaining_quantity
        data.setLessonCount(resultSet->getInt(6));     // lesson_count
        data.setExpireDays(resultSet->getInt(7));      // expire_days
        data.setEndDate(resultSet->getString(8));      // end_date
        data.setState(resultSet->getInt(9) != 0);      // state (tinyint -> bool)
        data.setCreator(resultSet->getUInt64(10));     // creator
        data.setEditor(resultSet->getUInt64(11));      // editor
        data.setAddTime(resultSet->getString(12));     // add_time
        data.setEditTime(resultSet->getString(13));    // edit_time
        data.setDeleted(resultSet->getInt(14) != 0);   // deleted (tinyint -> bool)
        data.setOrgId(resultSet->getUInt64(15));       // org_id
        return data;
    }
};

/**
 * 试听卡表字段匹配映射 - 返回智能指针对象
 */
class PtrCardMapper : public Mapper<PtrCardDO>
{
public:
    PtrCardDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<CardDO>();
        data->setId(resultSet->getUInt64(1));
        data->setCourseId(resultSet->getUInt64(2));
        data->setTitle(resultSet->getString(3));
        data->setQuantity(resultSet->getInt(4));
        data->setRemainingQuantity(resultSet->getInt(5));
        data->setLessonCount(resultSet->getInt(6));
        data->setExpireDays(resultSet->getInt(7));
        data->setEndDate(resultSet->getString(8));
        data->setState(resultSet->getInt(9) != 0);
        data->setCreator(resultSet->getUInt64(10));
        data->setEditor(resultSet->getUInt64(11));
        data->setAddTime(resultSet->getString(12));
        data->setEditTime(resultSet->getString(13));
        data->setDeleted(resultSet->getInt(14) != 0);
        data->setOrgId(resultSet->getUInt64(15));
        return data;
    }
};


/*
	试听卡规则表字段匹配映射 - 返回普通对象
    /*
    CREATE TABLE `setting_option` (
      `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT '主键',
      `setting_id` bigint NOT NULL COMMENT '组id',
      `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
      `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '码',
      `value` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '值',
      `value_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT 'str' COMMENT '值数据类型',
      `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '说明',
      `sort_num` int DEFAULT '0' COMMENT '排序',
      PRIMARY KEY (`id`) USING BTREE,
      UNIQUE KEY `code` (`code`) USING BTREE
    ) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='系统设置表';
*/
/*
[
    {
        "id": 39,
        "settingId": 1,
        "name": "体验卡使用规则说明",
        "code": "course_trial_help",
        "value": "1. 每人每课程限领1张体验卡\n2. 体验卡有效期以领取后计算\n3. 体验卡仅限首次体验用户使用\n4. 需提前24小时预约课程\n5. 取消预约请至少提前2小时\n6. 体验课后当天报名可享受9折优惠",
        "valueType": "str",
        "info": null,
        "sortNum": 0
    }
]
*/

class CardRuleMapper : public Mapper<CardRuleDO>
{
public:
    CardRuleDO mapper(ResultSet* resultSet) const override
    {
        CardRuleDO data;
        data.setId(resultSet->getUInt64(1));          // id
        data.setSettingId(resultSet->getUInt64(2));   // setting_id
        data.setName(resultSet->getString(3));        // name
        data.setCode(resultSet->getString(4));        // code
        data.setValue(resultSet->getString(5));       // value
        data.setValueType(resultSet->getString(6));   // value_type
        data.setInfo(resultSet->getString(7));        // info
        data.setSortNum(resultSet->getInt(8));        // sort_num
        return data;
    }
};

// 试听卡规则表字段匹配映射 - 返回智能指针对象
class PtrCardRuleMapper : public Mapper<PtrCardRuleDO>
{
    PtrCardRuleDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<CardRuleDO>();
        data->setId(resultSet->getUInt64(1));
        data->setSettingId(resultSet->getUInt64(2));
        data->setName(resultSet->getString(3));
        data->setCode(resultSet->getString(4));
        data->setValue(resultSet->getString(5));
        data->setValueType(resultSet->getString(6));
        data->setInfo(resultSet->getString(7));
        data->setSortNum(resultSet->getInt(8));
        return data;
    }
};

#endif // !_CARD_MAPPER_H_