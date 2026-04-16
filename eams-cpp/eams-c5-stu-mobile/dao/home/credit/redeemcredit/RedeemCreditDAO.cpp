#include "stdafx.h"
#include "RedeemCreditDAO.h"
#include "RedeemCreditMapper.h"

PtrStudentCreditDO StudentCreditDAO::selectByStudentId(uint64_t student_id)
{
	std::string sql = "SELECT credit FROM student WHERE `id` = ?";
	//std::cout << student_id << std::endl;
	return sqlSession->executeQueryOne<PtrStudentCreditDO>(sql, PtrStudentCreditMapper(), "%ull", student_id);
}
bool StudentCreditDAO::updateCredit(uint64_t id,int credit)
{
	std::string sql="UPDATE student SET credit = ? WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%i%ull", credit, id);
}

PtrCreditMallDO CreditMallDAO::selectByCreditMallId(uint64_t credit_id)
{
	std::string sql = "SELECT material_id,credit,state,name FROM credit_mall WHERE id = ?";
	return sqlSession->executeQueryOne<PtrCreditMallDO>(sql, PtrCreditMallMapper(), "%ull", credit_id);
}



bool MaterialDAO::updateNum(uint64_t id, int consume_num)
{
	std::string sql = "UPDATE material SET storage=storage-? WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%i%ull",consume_num,id);
}

PtrMaterialDO MaterialDAO::selectByMaterialId(uint64_t material_id)
{
	std::string sql = "SELECT school_id FROM material WHERE `id` = ?";
	return sqlSession->executeQueryOne<PtrMaterialDO>(sql, PtrMaterialMapper(), "%ull", material_id);
}