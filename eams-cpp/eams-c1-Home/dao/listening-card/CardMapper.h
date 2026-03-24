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
        // 列索引必须与 SELECT 语句中的字段顺序一致
        CardDO data;
        data.setId(resultSet->getUInt64(1));           // ct.id
        data.setCourseId(resultSet->getUInt64(2));     // ct.course_id
        data.setCourseName(resultSet->getString(3));   // c.name AS course_name
        data.setTitle(resultSet->getString(4));        // ct.title
        data.setQuantity(resultSet->getInt(5));        // ct.quantity
        data.setLessonCount(resultSet->getInt(6));     // ct.lesson_count
        data.setExpireDays(resultSet->getInt(7));      // ct.expire_days
        data.setEndDate(resultSet->getString(8));      // ct.end_date
        data.setState(resultSet->getInt(9) != 0);      // ct.state
        data.setEditTime(resultSet->getString(10));    // ct.edit_time
        // editorName 可能为 NULL -> getString 返回 empty 或可处理为 null 的实现
        data.setEditorName(resultSet->getString(11));  // s.name AS editor_name
        data.setRecordCount(resultSet->getInt(12));    // rr.record_count
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
        data->setCourseName(resultSet->getString(3));
        data->setTitle(resultSet->getString(4));
        data->setQuantity(resultSet->getInt(5));
        data->setLessonCount(resultSet->getInt(6));
        data->setExpireDays(resultSet->getInt(7));
        data->setEndDate(resultSet->getString(8));
        data->setState(resultSet->getInt(9) != 0);
        data->setEditTime(resultSet->getString(10));
        data->setEditorName(resultSet->getString(11));
        data->setRecordCount(resultSet->getInt(12));
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