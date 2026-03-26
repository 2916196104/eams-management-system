#include "EvaluateDAO.h"


bool EvaluateDAO::queryById(const std::string& id) {		// 通过Id来看是否被评价过了，被评价过了就不能再次评价了
	std::string sql = R"(
		SELECT IF(
			(SELECT `score` FROM lesson_student WHERE `id` = ?) IS NULL,
			1,
			0 
		) AS is_null_result; )";
	int64_t checkScore = sqlSession->executeQueryNumerical(sql);
	return checkScore;
}