#include "stdafx.h"
#include "GetCreditMallListDAO.h"
#include "GetCreditMallListMapper.h"

uint64_t CreditMallListDAO::count(const CreditMallListQuery::Wrapper& query)
{
	//string test = query->name;
	//std::cout << test << std::endl;
	string sql = "SELECT count(id) FROM credit_mall ";
	SqlParams params;
	if (query->name)
	{
		sql += "WHERE name LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrCreditMallListDO> CreditMallListDAO::selectAll(const CreditMallListQuery::Wrapper& query)
{
	string sql = "SELECT id, category_name, name, credit, sale_num, cover, content FROM credit_mall ";// coveÕÕÆ¬µØÖ·
	SqlParams params;
	if (query->name)
	{
		sql += "WHERE name LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	sql += "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
	return sqlSession->executeQuery<PtrCreditMallListDO>(sql, CreditMallListMapper(), params);
}

//PtrCreditMallDO CreditMallDAO::selectDetail(const int& id)
//{
//	string sql = "SELECT id, category_name, name, credit, sale_num, cover, content FROM credit_mall WHERE id = ? ";// coveÕÕÆ¬µØÖ·
//	return sqlSession->executeQueryOne<PtrCreditMallDO>(sql, CreditMallMapper(), "i", id);
//}
