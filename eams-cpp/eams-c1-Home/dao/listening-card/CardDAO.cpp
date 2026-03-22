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