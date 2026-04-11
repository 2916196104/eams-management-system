#include"stdafx.h"
#include"EnrollmentDAO.h"
#include"EnrollmentMapper.h"

/***
* 保存报名信息需求函数实现
 * 根据课程ID查询课程信息
 * @param id 课程ID
 * @return 课程信息
 */
PtrCourseDO EnrollmentDAO::selectCourseById(std::string id)
{
	string sql = "SELECT id,subject_id,name,price,discount,lesson_count,lesson_type ,expire_months,unit_price FROM course WHERE id = ? AND state= 1";
	return sqlSession->executeQueryOne<PtrCourseDO>(sql,PtrCourseMapper(),"s",id);
}

PtrStudentDO EnrollmentDAO::selectStudentById(std::string id)
{
	string sql = "SELECT id ,name FROM student WHERE id = ? AND deleted= 0";

	return sqlSession->executeQueryOne<PtrStudentDO>(sql, PtrStudentMapper(), "s", id);
}
bool EnrollmentDAO::countByStudentAndCourse(int studentId, int courseId)
{
	string sql = "SELECT count(*) FROM student_course WHERE student_id = ? AND course_id = ? AND deleted=0";
	return sqlSession->executeQueryNumerical(sql, "ii", studentId, courseId) > 0;
}
/**
 * 查询报名记录列表需求函数实现
 * @param query 报名记录查询对象
 * @return 报名记录列表数量
 */
std::string EnrollmentDAO::queryConditonBuilder(const EnrolledQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1 ";
	if (query->CourseName)
	{
		sqlCondition << " AND student_name = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->CourseName.getValue(""));
	}
	if (query->StudentName)
	{
		sqlCondition<< " AND course_name = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->StudentName.getValue(""));
	}
	if (query->StartDate)
	{
		sqlCondition<<" AND start_date = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->StartDate.getValue(""));
	}
	if (query->ExpireDate)
	{
		sqlCondition<<" AND expire_date = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->ExpireDate.getValue(""));
	}
	if (query->Amount)
	{
		sqlCondition<< " AND amount = ?";
		SQLPARAMS_PUSH(params, "d", double, query->Amount.getValue(0));
	}
	return sqlCondition.str();
}

//查询报名记录列表数量
uint64_t EnrollmentDAO::countByQuery(const EnrolledQuery::Wrapper& query)
{
	SqlParams sqlParams;
	string sql = "SELECT count(*) FROM enrolled_record ";
	sql += queryConditonBuilder(query, sqlParams);
	return sqlSession->executeQueryNumerical(sql, sqlParams);
}

//分页查询报名记录列表

std::list<EnrolledRecordDO> EnrollmentDAO::selectEnrolledRecordListByQuery(const EnrolledQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT student_name,course_name,start_date,expire_date,amount FROM enrolled_record ";
	sql += queryConditonBuilder(query, params);
	sql += " ORDER BY id DESC";
	sql += " LIMIT "+ std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	
	return sqlSession->executeQuery<EnrolledRecordDO>(sql, EnrolledRecordMapper(), params);
}

PtrEnrolledRecordDetailDO EnrollmentDAO::selectDetailById(int id)
{
	string sql = "SELECT student_name,course_name,subject_name,start_date,expire_date,course_amount,discount_amount,paid_amount,owe_amount,submit_time,remark,total_lessons,completed_lessons,remaining_lessons,refund_info FROM enrolled_record_detail WHERE id = ?";
	return sqlSession->executeQueryOne<PtrEnrolledRecordDetailDO>(sql, PtrEnrolledRecordDetailMapper(), "i", id);
}