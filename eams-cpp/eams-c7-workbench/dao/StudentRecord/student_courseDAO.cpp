#include "stdafx.h"
#include"student_courseDAO.h"
#include"student_courseMapper.h"
#define deBug 1
// 统计数据条数
uint64_t StudentCourseDAO::count(const StudentQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM student_course ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}
// 分页查询CourseProgress数据
std::list<CourseProgressViewDO> StudentCourseDAO::selectWithPageCourseProgress(const StudentQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT course.name ,course.state,student_course.count_lesson_total,student_course.count_lesson_complete FROM student_course LEFT JOIN course ON student_course.course_id=course.id";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	//sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	int64_t pageIndex = query->pageIndex.getValue(1); // 默认第1页
	int64_t pageSize = query->pageSize.getValue(10);  // 默认每页10条
	if (pageIndex < 1) pageIndex = 1; // 防止pageIndex=0
	if (pageSize < 1 || pageSize > 100) pageSize = 10; // 限制pageSize范围
	sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

	// 执行查询
	return sqlSession->executeQuery<CourseProgressViewDO>(sql, CourseProgressMapper(), params);
}

// 分页查询CourseRecordViewDO数据
std::list<CourseRecordViewDO> StudentCourseDAO::selectWithPageCourseRecord(const StudentQuery::Wrapper& query) {
	try {
		SqlParams params;
		string sql = "SELECT course.name ,course.state,student_course.count_lesson_total,student_course.count_lesson_complete FROM student_course LEFT JOIN course ON student_course.course_id=course.id";
		// 构建查询条件
		sql += queryConditionBuilder(query, params);
		// 构建排序语句
		//sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
		// 构建分页条件
		int64_t pageIndex = query->pageIndex.getValue(1); // 默认第1页
		int64_t pageSize = query->pageSize.getValue(10);  // 默认每页10条
		if (pageIndex < 1) pageIndex = 1; // 防止pageIndex=0
		if (pageSize < 1 || pageSize > 100) pageSize = 10; // 限制pageSize范围
		sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

		// 执行查询
		return sqlSession->executeQuery<CourseRecordViewDO>(sql, CourseRecordMapper(), params);
	}
	catch (const sql::InvalidArgumentException& e) {
		std::cerr << "MySQLMySQL canshu error  " << e.what() << std::endl;
		return {};
	}
	catch (const std::exception& e) {
		std::cerr << "common error  " << e.what() << std::endl;
		return {};
	}
	
}

// 分页查询StudentSignUp数据
std::list<StudentSignUpViewDO> StudentCourseDAO::selectWithPageStudentSighnUP(const StudentQuery::Wrapper& query) {
	try {
		SqlParams params;
		string sql = "SELECT course.name ,course.add_time,student_course.count_lesson_total,student_course.paid_amount FROM student_course LEFT JOIN course ON student_course.course_id=course.id";

		// 构建查询条件
		sql += queryConditionBuilder(query, params);
		// 构建排序语句
		//sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
		// 构建分页条件
		int64_t pageIndex = query->pageIndex.getValue(1); // 默认第1页
		int64_t pageSize = query->pageSize.getValue(10);  // 默认每页10条
		if (pageIndex < 1) pageIndex = 1; // 防止pageIndex=0
		if (pageSize < 1 || pageSize > 100) pageSize = 10; // 限制pageSize范围
		sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

		/*#if deBug
			OATPP_LOGD("StudentCourseDAO", "执行SQL: %s", sql.c_str());
		#endif // deBug*/

		// 执行查询
		return sqlSession->executeQuery<StudentSignUpViewDO>(sql, StudentSighnUPMapper(), params);
	}
	catch (const sql::InvalidArgumentException& e) {
		std::cerr << "MySQL canshu error " << e.what() << std::endl;
		return {};
	}
	catch (const std::exception& e) {
		std::cerr << "common error " << e.what() << std::endl;
		return {};
	}

}

inline std::string StudentCourseDAO::queryConditionBuilder(const StudentQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->id) {
		sqlCondition << " AND student_course.student_id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	}
	/*if (query->name) {
		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}*/

	return sqlCondition.str();
}
