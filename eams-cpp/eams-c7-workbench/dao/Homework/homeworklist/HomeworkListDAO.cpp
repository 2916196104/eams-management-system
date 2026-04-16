

#include "stdafx.h"
#include "HomeworkListMapper.h"
#include "HomeworkListDAO.h"

inline std::string HomeworkListDAO::queryConditionBuilder(const HomeworkListQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	return sqlCondition.str();
}

std::list<HomeworkListViewDO> HomeworkListDAO::selectWithPage(const HomeworkListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
		h.`title` AS title,
		c.`name` AS class_name,
		cr.`name` AS course_name,
		COUNT(hr.`homework_id`) AS number
	FROM
    homework h
    INNER JOIN class c ON h.`class_id` = c.`id`
    INNER JOIN course cr ON c.`course_id` = cr.`id`
    LEFT JOIN homework_record hr ON h.`id` = hr.`homework_id`
	GROUP BY
    	h.`title`,
		c.`name`,
		cr.`name`
	ORDER BY
		c.`name`, 
		h.`title`
	)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<HomeworkListViewDO>(sql, HomeworkListViewMapper(), params);
}

uint64_t HomeworkListDAO::count(const HomeworkListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT COUNT(*)
	FROM (
		SELECT
		h.`title` AS title,
		c.`name` AS class_name,
		cr.`name` AS course_name,
		COUNT(hr.`homework_id`) AS number
		FROM
		homework h
		INNER JOIN class c ON h.`class_id` = c.`id`
		INNER JOIN course cr ON c.`course_id` = cr.`id`
		LEFT JOIN homework_record hr ON h.`id` = hr.`homework_id`
		GROUP BY
    		h.`title`,
			c.`name`,
			cr.`name`
		ORDER BY
			c.`name`, h.`title`
	) AS t
	)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}