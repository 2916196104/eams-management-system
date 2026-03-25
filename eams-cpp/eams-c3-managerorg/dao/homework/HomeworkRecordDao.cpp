
#include "stdafx.h"
#include "HomeworkRecordDAO.h"
#include "HomeworkRecordMapper.h"

std::string HomeworkRecordDAO::queryConditionBuilder(const GetHomeworkListQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->title) {

		sqlCondition << " AND `title`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->title.getValue(""));
	}
	if (query->class_id) {

		sqlCondition << " AND class_id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->class_id.getValue(""));
	}
	if (query->creator) {

		sqlCondition << " AND creator=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->creator.getValue(0));
	}
	return sqlCondition.str();
}

uint64_t HomeworkRecordDAO::count(const GetHomeworkListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM homework ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

//定义了分页查询
std::list<HomeworkDO> HomeworkRecordDAO::gethomeworklist(const GetHomeworkListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT title,class_id,creator FROM homework ";  
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<HomeworkDO>(sql, HomeworkMapper(), params);
	//return{};
}

//获取作业详情，点击会传id，传回班级，作业标题，作业内容
PtrHomeworkRecordDO HomeworkRecordDAO::gethomeworkdetail(std::string id)
{
	string sql = "SELECT class_id,title,content FROM homework WHERE `id`=?";
	return sqlSession->executeQueryOne<PtrHomeworkRecordDO>(sql, PtrHomeworkRecordMapper(), "%s", id);
	//return {};
}

//保存作业
//int savehomework(const SaveHomeworkDTO& dto) {
//	return {};
//}