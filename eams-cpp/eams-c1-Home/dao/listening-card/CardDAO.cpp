#include "stdafx.h"
#include "CardDAO.h"
#include "CardMapper.h"

std::list<CardDO> CardDAO::queryAvailableCards() {
    // SELECT 字段顺序必须与 Mapper 中的列索引一致
	// 由于数据库中字段是固定的，所以直接写死字段列表，避免使用 SELECT * 导致的性能问题和潜在错误
    std::string sql = "SELECT id, course_id, title, quantity, remaining_quantity, "
        "lesson_count, expire_days, end_date, state, creator, editor, "
        "add_time, edit_time, deleted, org_id "
        "FROM course_trial "
        "WHERE state = 1 "
        "AND deleted = 0 "
        "AND end_date >= CURDATE() "
        "ORDER BY add_time DESC";

    return sqlSession->executeQuery<CardDO>(sql, CardMapper());
}
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

PtrCardRuleDO CardRuleDAO::queryCardUsageRules() {
    std::string sql = "SELECT id, setting_id, name, code, value, value_type, info, sort_num "
        "FROM setting_option "
        "WHERE code = 'course_trial_help' "
        "LIMIT 1";
    auto result = sqlSession->executeQuery<CardRuleDO>(sql, CardRuleMapper());
    if (!result.empty()) {
        return std::make_shared<CardRuleDO>(std::move(result.front()));
    }
	return nullptr;
}
