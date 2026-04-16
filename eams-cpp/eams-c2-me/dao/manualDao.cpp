#include "dao/manualDao.h"
#include "../lib-mysql/include/SqlSession.h"
#include "../domain/do/manualDO.h"
#include "../lib-mysql/include/BaseDAO.h"

//查询说明列表信息的sql语句构建器
std::string manualDAO::queryListBuilder(
	const ListQuery::Wrapper& query,
	SqlParams& params
)
{
	std::stringstream sqlList;
	int offset = (query->pageIndex - 1) * query->pageSize;
	int size = query->pageSize;
	sqlList << "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "i", int, offset);
	SQLPARAMS_PUSH(params, "i", int, size);
	return sqlList.str();
}

//查询说明列表某一详细信息的sql语句构建器
std::string manualDAO::queryDetailBuilder(
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

/**
* 统计列表的记录数
* @return 记录总数
*/
uint64_t manualDAO::count()
{
	// 构建SQL
	string sql = "SELECT COUNT(*) FROM help ";

	// 执行查询并返回数值结果
	return sqlSession->executeQueryNumerical(sql);
}


/**
* 展示列表的记录
* query为查询条件
* @return 记录总数
*/
std::list<ManualDO> manualDAO::showList(const ListQuery::Wrapper& query)
{

	SqlParams params;
	// 1. 构建基础查询SQL
	string sql = "SELECT id, title ,add_time,edit_time FROM help ";

	// 2. 添加排序  优先按sort_num降序，最后按ID降序
	sql += " ORDER BY `sort_num` DESC, `id` ASC ";

	// 3. 添加分页限制  LIMIT 0, 5 表示：跳过0条，取5条
	sql += queryListBuilder(query, params);

	/*uint64_t offset = (query->pageIndex - 1) * query->pageSize;
	sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);*/

	// 4. 执行查询并映射结果
	return sqlSession->executeQuery<ManualDO>(sql, ListMapper(), params);
}



//主键查询（返回单条）：
PtrManualDO manualDAO::selectById(std::string id)
{
	string sql = "SELECT * FROM help WHERE `id` = ?";
	// executeQueryOne 返回单条记录，未找到时返回nullptr
	return sqlSession->executeQueryOne<PtrManualDO>
		(
			sql,
			PtrDetailMapper(), // 使用指针版本的Mapper
			"%s",
			id
		);
}