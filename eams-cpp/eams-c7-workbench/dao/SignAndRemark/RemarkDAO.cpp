#include "stdafx.h"
#include "RemarkDAO.h"
#include "RemarkMapper.h"

uint64_t RemarkDAO::count(const RemarkQuery::Wrapper& query)
{
	string sql = "SELECT count(id) FROM lesson_student ls";
	SqlParams params;
	// 检查 Payload 是否为空
	if (!query->getPayload()) {
		throw std::invalid_argument("Payload is null");
	}

	// 获取并验证 teacher_id
	uint64_t t_id = 0;
	try {
		t_id = std::stoull(query->getPayload()->getId());
	}
	catch (const std::invalid_argument& e) {
		throw std::invalid_argument("Invalid teacher_id format: " + query->getPayload()->getId());
	}
	catch (const std::out_of_range& e) {
		throw std::out_of_range("Teacher_id out of range: " + query->getPayload()->getId());
	}

	if (t_id <= 0) {
		throw std::invalid_argument("teacher_id must be greater than 0");
	}

	// 构建 WHERE 条件
	sql += " WHERE ls.evaluate_teacher = ? ";
	SQLPARAMS_PUSH(params, "ull", uint64_t, t_id);

	// 执行查询并返回结果
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrRemarkViewDO>RemarkDAO::selectAll(const RemarkQuery::Wrapper& query)
{
	string sql = R"(SELECT 
		ls.id AS lesson_student_id,
		ls.evaluate_time,
		ls.evaluation,
		ls.score,
		s.name AS student_name,
		st.name AS teacher_name
	FROM 
		lesson_student ls
	INNER JOIN 
		student s 
		ON ls.student_id = s.id
	INNER JOIN 
		staff st 
		ON ls.evaluate_teacher = st.id)";
	SqlParams params;
	// 检查 Payload 是否为空
	if (!query->getPayload()) {
		throw std::invalid_argument("Payload is null");
	}

	// 获取并验证 teacher_id
	uint64_t t_id = 0;
	try {
		t_id = std::stoull(query->getPayload()->getId());
	}
	catch (const std::invalid_argument& e) {
		throw std::invalid_argument("Invalid teacher_id format: " + query->getPayload()->getId());
	}
	catch (const std::out_of_range& e) {
		throw std::out_of_range("Teacher_id out of range: " + query->getPayload()->getId());
	}

	if (t_id <= 0) {
		throw std::invalid_argument("teacher_id must be greater than 0");
	}

	// 构建 WHERE 条件
	sql += " WHERE ls.evaluate_teacher = ? ";
	SQLPARAMS_PUSH(params, "ull", uint64_t, t_id);

	// 验证分页参数
	uint64_t pageIndex = query->pageIndex.getValue(1);
	uint64_t pageSize = query->pageSize.getValue(10);

	if (pageIndex <= 0 || pageSize <= 0) {
		throw std::invalid_argument("pageIndex and pageSize must be greater than 0");
	}

	// 构建 LIMIT 子句
	sql += " LIMIT ?, ?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (pageIndex - 1) * pageSize);
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

	// 执行查询并返回结果
	return sqlSession->executeQuery<PtrRemarkViewDO>(sql, RemarkMapper(), params);
}
