#include "GetCourseEvaluationDAO.h"
#include "GetCourseEvaluationMapper.h"

std::list<PtrEvaluationViewDO> GetCourseEvaluation::selectWithPage(const EvaluationQuery::Wrapper& query)
{	
	
	std::string sql = R"(
		SELECT 
			ls.`id` AS ID, 
			ls.`student_id` AS StudentID, 
			stu.`name` AS StudentName,
			ls.`teacher_id` AS TeacherID,
			stuff.`name` AS TeacherName,
			ls.`score` AS Score,
			ls.`evaluate_time` AS EvaluationTime,
			ls.`evaluation` AS Evaluation,
			ls.`sign_state` AS Sign
		FROM
			`lesson_student` AS ls
		JOIN 
			`student` AS stu
		ON	
			stu.`id` = ls.`student_id`
		JOIN
			`stuff` AS stuff
		ON 
			stuff.`id` = ls.`teacher_id`
		WHERE
			1=1
	)";

	SqlSession* sqlSession = getSqlSession();
	if (!sqlSession) {
		std::cerr << "[GetCourseEvaluationDAO::selectWithPage]: 获取数据库回话失败" << std::endl;
		return std::list<PtrEvaluationViewDO>();
	}
	// 构建查询条件
	SqlParams params;
	if (query->lesson_id) {
		sql += " AND ls.`lesson_id` = ?";
		SQLPARAMS_PUSH(params, "ll", uint64_t, query->lesson_id.getValue(1));
	}
	else {
		std::cerr << "[GetCourseEvaluationDAO::selectWithPage]: 缺少查询参数" << std::endl;
		return std::list<PtrEvaluationViewDO>();
	}
	// 构建排序语句
	sql += " ORDER BY ls.`evaluate_time` DESC";
	if (query->pageIndex || query->pageSize) {
		uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
		sql += " LIMIT ? OFFSET ?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
		SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	}
	else {
		std::cerr << "[GetCourseEvaluationDAO::selectWithPage]: 缺少分页参数" << std::endl;
		return std::list<PtrEvaluationViewDO>();
	}
	// 执行查询
	return sqlSession->executeQuery<PtrEvaluationViewDO>(sql, EvaluationViewMapper(), params);
}
