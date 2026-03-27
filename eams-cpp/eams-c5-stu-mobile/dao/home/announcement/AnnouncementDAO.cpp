#include "stdafx.h"
#include "AnnouncementDAO.h"
#include "AnnouncementMapper.h"


inline std::string AnnouncementDAO::queryConditionBuilder(const AnnouncementQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	return sqlCondition.str();
}

uint64_t AnnouncementDAO ::count(const AnnouncementQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM advertisement ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}
std::list<AnnouncementDO> AnnouncementDAO::selectWithPage(const AnnouncementQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,title,type,content,add_time,edit_time,editor,cover FROM advertisement ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<AnnouncementDO>(sql, AnnouncementMapper(), params);

}
AnnouncementDO AnnouncementDAO::selectone(const AnnouncementQuery::Wrapper& query)
{
	SqlParams params;
	// 1. 基础查询：公告表 + 目标字段
	string sql = "SELECT id,title,type,content,add_time,edit_time,editor,cover FROM advertisement ";
	// 2. 固定条件：type=1 + 软删除过滤（deleted=0）
	sql += " WHERE 1=1 AND type = 1 AND deleted = 0 ";
	// 3. 排序：按编辑时间/添加时间降序（取最新的），ID降序兜底
	sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";
	// 4. 只取第一条
	sql += " LIMIT 1";

	return sqlSession->executeQueryOne<AnnouncementDO>(sql, AnnouncementMapper(), params);
}