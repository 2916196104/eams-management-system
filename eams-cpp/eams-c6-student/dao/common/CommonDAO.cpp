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
StudentDTO::Wrapper getStudentDetailById(uint64_t studentId) {
	string sql = "select "
		"";


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

	