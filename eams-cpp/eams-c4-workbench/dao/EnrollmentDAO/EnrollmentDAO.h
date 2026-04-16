#pragma once
#ifndef ENROLLMENT_DAO_
#define ENROLLMENT_DAO_
#include"BaseDAO.h"
#include"../../domain/do/StudentCourseDO.h"
#include"../../domain/do/StudentDO.h"
#include"../../domain/do/CourseDO.h"
#include"../../domain/do/ViewDO/EnrolledRecordDO.h"
#include"../../domain/query/EnrollmentQuery/EnrolledRecordQuery.h"
class EnrollmentDAO : public BaseDAO
{
private:

	inline std::string queryConditonBuilder(const EnrolledQuery::Wrapper& query, SqlParams& params);
	
public:

	//-----保存报名信息------
	//根据学生ID查询学生信息
	PtrStudentDO selectStudentById(std::string id);
	//根据课程ID查询课程信息
	PtrCourseDO selectCourseById(std:: string id);
	//根据学生ID和课程ID查询报名记录数量,如果数量大于0，说明已经报名过了
	bool countByStudentAndCourse(int studentId, int courseId);

	//------获取报名记录列表------
	//查询报名记录列表数量
	uint64_t countByQuery(const EnrolledQuery::Wrapper& query);
	//分页查询报名记录列表
	std::list<EnrolledRecordDO> selectEnrolledRecordListByQuery(const EnrolledQuery::Wrapper& query);
	//根据报名记录ID查询报名记录详情
	PtrEnrolledRecordDetailDO selectDetailById(int id);
	
};

#endif // !ENROLLMENT_DAO_