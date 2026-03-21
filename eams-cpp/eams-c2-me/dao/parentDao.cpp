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
	int offset = (query->pageIndex - 1) * query->pageSize;
	int size=query->pageSize;
	sqlList << "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "i", int, offset);
	SQLPARAMS_PUSH(params, "i", int, size);
	return sqlList.str();
}


std::string parentDAO::queryDetailBuilder(
	const DetailQuery::Wrapper& query,
	SqlParams& params
)
{
	std::stringstream sqlDetail;
	sqlDetail << " WHERE 1=1"; // 基础条件，方便后续拼接
	if (query->id) {
		sqlDetail << "AND id=?";
		SQLPARAMS_PUSH(params, "i", int, query->id.getValue(0));
	}
	return sqlDetail.str();
}


uint64_t parentDAO::count(const ListQuery::Wrapper& query)
{
	
	// 构建SQL
	string sql = "SELECT COUNT(*) FROM help ";
	
	// 执行查询并返回数值结果
	return sqlSession->executeQueryNumerical(sql);
	
}

std::list<ParentDO> parentDAO::showList(const ListQuery::Wrapper& query)
{
	
	SqlParams params;
	// 1. 构建基础查询SQL
	string sql = "SELECT id, title ,add_time,edit_time FROM help ";

	// 2. 添加排序
	sql += " ORDER BY `sort_num` DESC, `id` DESC ";
	// 优先按sort_num降序，最后按ID降序
	
	// 3. 添加分页限制 // LIMIT 0, 5 表示：跳过0条，取5条
	sql += queryListBuilder(query, params);

	/*uint64_t offset = (query->pageIndex - 1) * query->pageSize;
	sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);*/

	// 4. 执行查询并映射结果
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