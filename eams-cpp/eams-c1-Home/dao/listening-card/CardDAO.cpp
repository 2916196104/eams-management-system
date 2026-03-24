#include "stdafx.h"
#include "CardDAO.h"
#include "CardMapper.h"

std::list<CardDO> CardDAO::queryAvailableCards() {
    // SELECT 字段顺序必须与 Mapper 中的列索引一致
	// 由于数据库中字段是固定的，所以直接写死字段列表，避免使用 SELECT * 导致的性能问题和潜在错误
    std::string sql =
        "SELECT ct.id, ct.course_id, c.name AS course_name, ct.title, ct.quantity, "
        "ct.lesson_count, ct.expire_days, ct.end_date, ct.state, ct.edit_time, "
        "s.name AS editor_name, IFNULL(rr.record_count, 0) AS record_count "
        "FROM course_trial ct "
        "LEFT JOIN course c ON ct.course_id = c.id "
        // 编辑者来自 staff 表
        "LEFT JOIN staff s ON ct.editor = s.id "
        // 统计领取记录，表为 course_trial_record，按 trial_id 聚合
        "LEFT JOIN (SELECT trial_id, COUNT(1) AS record_count FROM course_trial_record GROUP BY trial_id) rr ON rr.trial_id = ct.id "
        "WHERE ct.state = 1 "
        "AND ct.deleted = 0 "
        "AND ct.end_date >= CURDATE() "
        "ORDER BY ct.add_time DESC";
    /*
		sql 语句说明：
		select部分：查询试听卡表(course_trial)的基本信息，关联查询课程表(course)获取课程名称，关联查询员工表(staff)获取编辑者名称，`关联子查询`统计领取记录数。
    */
    return sqlSession->executeQuery<CardDO>(sql, CardMapper());
}

PtrCardRuleDO CardRuleDAO::queryCardUsageRules() {
    std::string sql = "SELECT id, setting_id, name, code, value, value_type, info, sort_num "
        "FROM setting_option "
        "WHERE code = 'course_trial_help' "
        "LIMIT 1";
    auto result = sqlSession->executeQuery<CardRuleDO>(sql, CardRuleMapper());
    if (!result.empty()) {
		return std::make_shared<CardRuleDO>(std::move(result.front())); // 使用移动语义，因为拷贝构造函数已经被基类BASEDO删除了
    }
	return nullptr;
}
