#include "HhDAO.h"
#include "HhMapper.h"

//std::string HhDAO::queryConditionBuilder(const CustomerQuery::Wrapper& query, SqlParams& params) {
//	return {};
//}

uint64_t HhDAO::countCustomer(const CustomerQuery::Wrapper& query, std::string creator_id) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM student AS s WHERE s.creator = ? ";
	SQLPARAMS_PUSH(params, "i", int, stoi(creator_id));
	return sqlSession->executeQueryNumerical(sql, params);
}

uint64_t HhDAO::countClassroom(const ClassroomQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM classroom";
	return sqlSession->executeQueryNumerical(sql, params);
}

// 接口一：分页查询客户数据
std::list<HhStudentViewDO> HhDAO::selectCustomerWithPage(const CustomerQuery::Wrapper& query, std::string creator_id) {
	SqlParams params;
	string sql = "SELECT s.id, s.name, u.mobile ";
	sql += " FROM student s INNER JOIN user u ON s.user_id = u.id ";
	// 查询条件
	sql += " WHERE s.creator = ? ";
	// 排序条件
	sql += " ORDER BY s.edit_time DESC ";
	// 分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	SQLPARAMS_PUSH(params, "i", int, stoi(creator_id));

	return sqlSession->executeQuery<HhStudentViewDO>(sql, HhStudentViewMapper1(), params);
}

// 接口二：通过学生ID查询学生详情
PtrHhStudentViewDO HhDAO::selectCustomerDetailWithId(std::string id) {
	SqlParams params;
	string sql = "SELECT s.id, s.name, u.mobile, s.gender, TIMESTAMPDIFF(YEAR, birthday, CURDATE()), s.birthday, s.stage, s.remark ";
	sql += " FROM student s INNER JOIN user u ON s.user_id = u.id ";
	sql += " WHERE s.id = ? ";
	sql += " ORDER BY s.edit_time DESC ";

	SQLPARAMS_PUSH(params, "i", int, stoi(id));

	return sqlSession->executeQueryOne<PtrHhStudentViewDO>(sql, HhStudentViewMapper2(), params);
}

// 接口三：通过学生ID查询学生课程
std::list<HhCourseViewDO> HhDAO::selectCourseWithId(std::string id) {
	SqlParams params;
	string sql = " SELECT c.id, c.name, CONCAT(s.count_lesson_complete, '/', c.lesson_count), DATE_FORMAT(DATE_ADD(c.add_time, INTERVAL c.expire_months MONTH), '%Y-%m-%d'), c.lesson_count - s.count_lesson_complete ";
	sql += " FROM course c INNER JOIN student_course s ";
	sql += " ON c.id = s.course_id ";
	sql += " WHERE s.student_id = ? ";

	SQLPARAMS_PUSH(params, "i", int, stoi(id));

	return sqlSession->executeQuery<HhCourseViewDO>(sql, HhCourseViewMapper(), params);
}
// 接口四：分页查询教室数据
std::list<ClassroomDO> HhDAO::selectClassroomWithPage(const ClassroomQuery::Wrapper& query) {
	SqlParams params;
	string sql = " SELECT c.id, c.name, c.address FROM classroom c ";
	if (query->name) {
		sql += " WHERE c.name = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	// 排序条件
	sql += " ORDER BY c.add_time DESC ";
	// 分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<ClassroomDO>(sql, HhClassroomMapper(), params);
}