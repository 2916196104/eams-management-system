#include "stdafx.h"
#include "exchangeDAO.h"
#include "exchangeMapper.h"

// 统计是否存在可兑换商品
uint64_t exchangeDAO::count1()
{
	string sql = "SELECT COUNT(*) FROM credit_mall WHERE deleted = 0";
	return sqlSession->executeQueryNumerical(sql);
}

// 统计当前用户是否已兑换过商品
uint64_t exchangeDAO::count2(const AcceptGoodsQuery::Wrapper& query)
{
	uint64_t studentId = query->studentId.getValue(0);

	std::string sql =
		"SELECT COUNT(*) "
		"FROM credit_exchange "
		"WHERE deleted = 0 AND student_id = ? ";
	// 添加参数
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);

	return sqlSession->executeQueryNumerical(sql, params);
}

// 查询所有可兑换商品
std::list<PtrGoodsDO> exchangeDAO::selectAllGoods(const PageQuery::Wrapper& query)
{
	string sql =
		"SELECT c.*, "
		"       o.name AS school_name, "
		"       m.storage AS storage "
		"FROM credit_mall c "
		"LEFT JOIN org o ON o.id = c.school_id AND o.deleted = 0 "
		"LEFT JOIN material m ON m.id = c.material_id AND m.deleted = 0 "
		"WHERE c.deleted = 0 ";
	SqlParams params;
	sql += " ORDER BY id DESC";
	sql += " LIMIT ?, ?";
	// 添加参数
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
	return sqlSession->executeQuery<PtrGoodsDO>(sql, PtrGoodsMapper(), params);
}

// 查询当前用户已兑换商品
std::list<PtrAcceptGoodsDO> exchangeDAO::selectAcceptGoods(const AcceptGoodsQuery::Wrapper& query)
{
	uint64_t studentId = query->studentId.getValue(0);

	std::string sql =
		"SELECT ce.*, "
		"cm.name AS credit_mall_name, "
		"cm.cover AS cover, "
		"stu.name AS student_name, "
		"o.name AS school_name, "
		"u.mobile AS mobile, "
		"sta.name AS verify_staff_name "
		"FROM credit_exchange ce "
		"LEFT JOIN credit_mall cm ON ce.credit_mall_id = cm.id "
		"LEFT JOIN student stu ON ce.student_id = stu.id "
		"LEFT JOIN org o ON ce.school_id = o.id "
		"LEFT JOIN user u ON ce.user_id = u.id "
		"LEFT JOIN staff sta ON ce.verify_staff = sta.id "
		"WHERE ce.deleted = 0 AND ce.student_id = ? "
		"ORDER BY ce.id DESC "
		"LIMIT ?, ? ";
	// 添加参数
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params, "ull", uint64_t,
		(query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));

	return sqlSession->executeQuery<PtrAcceptGoodsDO>(sql, PtrAcceptGoodsMapper(), params);
}

// 查询规则
PtrSettingDO exchangeDAO::selectById(uint64_t id) {
	std::string sql = "SELECT * FROM setting_option WHERE id = ?";
	return sqlSession->executeQueryOne<PtrSettingDO>(sql, PtrSettingMapper(), "%i", id);
}