#include "stdafx.h"
#include "CommonDAO.h"
#include "CommonMapper.h"
void StudentDAO::updateStudentHeadImg(uint64_t studentId, const std::string& headImg)
{
	string sql = "update student set head_img=? where id=?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, headImg);
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	sqlSession->executeUpdate(sql, params);
}
StudentDTO::Wrapper StudentDAO::getStudentDetailById(uint64_t studentId) {
	string sql = "select stu.head_img,stu.name,u.mobile, "
		"coalesce(sum(sc.count_lesson_total - sc.count_lesson_complete), 0) as cll,"
		"stu.credit,stu.stage,stu.gender,stu.birthday,stu.birthday,stu.idcard,u.name,"
		"stu.family_rel,stu.grade,stu.join_date,stu.add_time,stu.remark,"
		"sum(sc.count_lesson_complete) "
		"from student stu "
		"left join user u on stu.user_id=u.id "
		"left join student_course sc on stu.id=sc.student_id "
		"where stu.id=? "
		"GROUP BY stu.id, stu.head_img, stu.name, u.mobile, stu.credit, "
		"stu.stage, stu.gender, stu.birthday, stu.idcard, u.name, "
		"stu.family_rel, stu.grade, stu.join_date, stu.add_time, stu.remark";
	;
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	auto resultSet = sqlSession->executeQueryOne<StudentDTO::Wrapper>(sql, StudentDetailMapper(), params);
	return resultSet;

}
uint64_t RegistrationRecordDAO::count(uint64_t studentId) {
	string sql = "select count(id) from student_course ";
	SqlParams params;
	sql += "where student_id=?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	return sqlSession->executeQueryNumerical(sql, params);
}
std::list<RegistrationDTO::Wrapper> RegistrationRecordDAO::selectRegistrationRecordWithPage(const RegistrationPageQuery::Wrapper& query) {
	SqlParams params;
	uint64_t studentId = query->id;
	string sql = "select sc.add_time,c.name,sub.name,sc.count_lesson_total,sc.unit_price,"
		"sc.course_amount,sc.discount_amount,sc.paid_amount,sc.amount-sc.paid_amount,"
		"sc.start_date,sc.expire_date,ref.refund_amount,ref.refund_amount/sc.unit_price,"
		"ref.remark,ref.verify_state "
		"from student_course sc "
		"left join course c on sc.course_id=c.id "
		"left join subject sub on sc.subject_id=sub.id "
		"left join refund ref on sc.id=ref.student_course_id "
		"where sc.student_id=?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<RegistrationDTO::Wrapper>(sql, RegistrationRecordMapper(), params);
}

//班级列表
uint64_t getClassListDAO::count(const getClassListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM class_list ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
//班级列表
std::list<getClassListDO> getClassListDAO::selectWithPage(const getClassListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id, class_name, subject, classroom, student_count, max_student_count FROM class_list ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, id DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<getClassListDO>(sql, getClassListMapper(), params);
}
//班级列表
std::list<PtrgetClassListDO> getClassListDAO::selectWithPagePtr(const getClassListQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id, class_name, subject, classroom, student_count, max_student_count FROM class_list ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, id DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<PtrgetClassListDO>(sql, PtrgetClassListMapper(), params);
}
//班级列表
std::string getClassListDAO::queryConditionBuilder(const getClassListQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";

	if (query->id) {
		sqlCondition << " AND id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	}
	if (query->className) {
		sqlCondition << " AND class_name=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->className.getValue(""));
	}
	if (query->subject) {
		sqlCondition << " AND subject=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->subject.getValue(""));
	}
	if (query->classroom) {
		sqlCondition << " AND classroom=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->classroom.getValue(""));
	}
	if (query->studentCount) {
		sqlCondition << " AND student_count=?";
		SQLPARAMS_PUSH(params, "i", int, query->studentCount.getValue(0));
	}
	if (query->maxStudentCount) {
		sqlCondition << " AND max_student_count=?";
		SQLPARAMS_PUSH(params, "i", int, query->maxStudentCount.getValue(0));
	}

	return sqlCondition.str();
}


//课程统计
uint64_t getCourseStatisticsDAO::count(const getCourseStatisticsQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM course_statistics ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
//课程统计
std::list<getCourseStatisticsDO> getCourseStatisticsDAO::selectWithPage(const getCourseStatisticsQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT course, total_hours, remaining_hours, attended_hours, expire_date, cancel_priority FROM course_statistics ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, course DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<getCourseStatisticsDO>(sql, getCourseStatisticsMapper(), params);
}
//课程统计
std::list<PtrgetCourseStatisticsDO> getCourseStatisticsDAO::selectWithPagePtr(const getCourseStatisticsQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT course, total_hours, remaining_hours, attended_hours, expire_date, cancel_priority FROM course_statistics ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, course DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<PtrgetCourseStatisticsDO>(sql, PtrgetCourseStatisticsMapper(), params);
}
//课程统计
std::string getCourseStatisticsDAO::queryConditionBuilder(const getCourseStatisticsQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";

	if (query->course) {
		sqlCondition << " AND course=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->course.getValue(""));
	}
	if (query->totalHours) {
		sqlCondition << " AND total_hours=?";
		SQLPARAMS_PUSH(params, "i", int, query->totalHours.getValue(0));
	}
	if (query->remainingHours) {
		sqlCondition << " AND remaining_hours=?";
		SQLPARAMS_PUSH(params, "i", int, query->remainingHours.getValue(0));
	}
	if (query->attendedHours) {
		sqlCondition << " AND attended_hours=?";
		SQLPARAMS_PUSH(params, "i", int, query->attendedHours.getValue(0));
	}
	if (query->expireDate) {
		sqlCondition << " AND expire_date=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->expireDate.getValue(""));
	}
	if (query->cancelPriority) {
		sqlCondition << " AND cancel_priority=?";
		SQLPARAMS_PUSH(params, "i", int, query->cancelPriority.getValue(0));
	}

	return sqlCondition.str();
}



uint64_t JoinclassDAO::count(const JoinclassQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM join_class ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<JoinclassDO> JoinclassDAO::selectWithPage(const JoinclassQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT class_name, school FROM join_class ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, class_name DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<JoinclassDO>(sql, JoinclassMapper(), params);
}

std::list<PtrJoinclassDO> JoinclassDAO::selectWithPagePtr(const JoinclassQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT class_name, school FROM join_class ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(update_time, create_time) DESC, class_name DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<PtrJoinclassDO>(sql, PtrJoinclassMapper(), params);
}

std::string JoinclassDAO::queryConditionBuilder(const JoinclassQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";

	if (query->className) {
		sqlCondition << " AND class_name=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->className.getValue(""));
	}
	if (query->school) {
		sqlCondition << " AND school=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->school.getValue(""));
	}

	return sqlCondition.str();
}
PtrStudentCourseDO StudentCourseDAO::selectByIds(
	const uint64_t studentId,
	const uint64_t courseId,
	const uint64_t subjectId
) {
	string sql = "SELECT * FROM student_course WHERE student_id=" + std::to_string(studentId) +
		" AND course_id=" + std::to_string(courseId) +
		" AND subject_id=" + std::to_string(subjectId) +
		" AND deleted=0";
	return getSqlSession()->executeQueryOne<PtrStudentCourseDO>(sql, PtrStudentCourseMapper(), "");

}
int StudentCourseDAO::updatePayStatus(uint64_t id, double paidAmount, int payOff) {
	std::string sql = "UPDATE student_course SET paid_amount=?, pay_off=? WHERE id=?";
	SqlParams params;
	params.push_back(SqlParam("paid_amount", std::make_shared<double>(paidAmount)));
	params.push_back(SqlParam("pay_off", std::make_shared<int>(payOff)));
	params.push_back(SqlParam("id", std::make_shared<uint64_t>(id)));
	return getSqlSession()->executeUpdate(sql, params);
}
PtrRefundDO RefundDAO::selectByIds(uint64_t student_course_id) {
	string sql = "SELECT * FROM refund WHERE student_course_id=" + std::to_string(student_course_id);
	return getSqlSession()->executeQueryOne<PtrRefundDO>(sql, PtrRefundMapper(), "");

}

// 删除跟进记录的实现
int ContactRecordDAO::deleteContactRecord(uint64_t recordId) {
	string sql = "UPDATE contact_record SET deleted=1 WHERE id=?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, recordId);
	return sqlSession->executeUpdate(sql, params);
}