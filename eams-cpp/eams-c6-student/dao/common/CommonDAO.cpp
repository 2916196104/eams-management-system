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
	auto resultSet = sqlSession->executeQueryOne<StudentDTO::Wrapper>(sql,StudentDetailMapper(), params);
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

	