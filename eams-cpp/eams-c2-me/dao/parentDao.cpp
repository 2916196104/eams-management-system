#include "dao/parentDao.h"
#include "../lib-mysql/include/SqlSession.h"
#include "../domain/do/parentDO.h"
#include "../lib-mysql/include/BaseDAO.h"


std::string parentDAO::queryListBuilder(
	const ListQuery::Wrapper& query,
	SqlParams& params
)
{
	std::stringstream sqlList;
	sqlList << "SELECT id,title,add_time,edit_time FROM help"; // 基础条件，方便后续拼接
	sqlList << "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "i", int, query->pageIndex);
	SQLPARAMS_PUSH(params, "i", int, query->pageSize);
	return sqlList.str();

}
std::string parentDAO::queryDetailBuilder(
	const DetailQuery::Wrapper& query,
	SqlParams& params
)
{
	std::stringstream sqlDetail;
	sqlDetail << "SELECT * FROM help"; // 基础条件，方便后续拼接
	sqlDetail << "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "i", int, query->pageIndex);
	SQLPARAMS_PUSH(params, "i", int, query->pageSize);
	return sqlDetail.str();
}


uint64_t parentDAO::count(const ListQuery::Wrapper& query)
{
	SqlParams params;
	// 构建SQL
	string sql = "SELECT COUNT(*) FROM help ";
	sql += queryListBuilder(query, params);
	// 执行查询并返回数值结果
	return sqlSession->executeQueryNumerical(sql, params);
	//return 0;
}

std::list<ParentDO> parentDAO::selectWithList(const ListQuery::Wrapper& query)
{
	//return {};
	SqlParams params;
	// 1. 构建基础查询SQL
	string sql = "SELECT id, title ,add_time FROM help ";
	// 2. 添加WHERE条件
	sql += queryListBuilder(query, params);
	// 3. 添加排序
	sql += " ORDER BY IFNULL(`sort_num`) DESC, `id` DESC ";
	// 优先按sort_num降序，最后按ID降序
	// 4. 添加分页限制
	uint64_t offset = (query->pageIndex - 1) * query->pageSize;
	sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);
	// LIMIT 0, 10 表示：跳过0条，取10条
	// 5. 执行查询并映射结果
	return sqlSession->executeQuery<ParentDO>(sql, ListMapper(), params);
}



PtrParentDO parentDAO::selectById(std::string id)
{
	string sql = "SELECT * FROM help WHERE `id` = ?";
	// executeQueryOne 返回单条记录，未找到时返回nullptr
	return sqlSession->executeQueryOne<PtrParentDO>
		(
			sql,
			PtrDetailMapper(), // 使用指针版本的Mapper
			"%s",
			id
		);
}