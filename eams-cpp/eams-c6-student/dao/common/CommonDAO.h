#pragma once
#ifndef _COMMON_DAO_
#define _COMMON_DAO_
#include "BaseDAO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/do/common/CommonDO.h"
#include "../../domain/query/common/CommonQuery.h"
#include "../../domain/dto/common/CommonDTO.h"
class StudentDAO :public BaseDAO
{
public:
	void updateStudentHeadImg(uint64_t studentId, const std::string& headImg);
	StudentDTO::Wrapper getStudentDetailById(uint64_t studentId);
};
class RegistrationRecordDAO :public BaseDAO
{
public:
	uint64_t count(uint64_t studentId);
	// 涓嶄娇鐢?DO锛歋QL JOIN 缁撴灉鐩存帴鏄犲皠鎴?DTO
	std::list<RegistrationDTO::Wrapper> selectRegistrationRecordWithPage(const RegistrationPageQuery::Wrapper& query);

};

/**
 * 班级列表数据访问对象
 */
class getClassListDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const getClassListQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const getClassListQuery::Wrapper& query);
	// 分页查询数据
	std::list<getClassListDO> selectWithPage(const getClassListQuery::Wrapper& query);
	std::list<PtrgetClassListDO> selectWithPagePtr(const getClassListQuery::Wrapper& query);
};


/**
 * 课程统计数据访问对象
 */
class getCourseStatisticsDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const getCourseStatisticsQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const getCourseStatisticsQuery::Wrapper& query);
	// 分页查询数据
	std::list<getCourseStatisticsDO> selectWithPage(const getCourseStatisticsQuery::Wrapper& query);
	std::list<PtrgetCourseStatisticsDO> selectWithPagePtr(const getCourseStatisticsQuery::Wrapper& query);
};


/**
 * 课程统计数据访问对象
 */
class JoinclassDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const JoinclassQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const JoinclassQuery::Wrapper& query);
	// 分页查询数据
	std::list<JoinclassDO> selectWithPage(const JoinclassQuery::Wrapper& query);
	std::list<PtrJoinclassDO> selectWithPagePtr(const JoinclassQuery::Wrapper& query);
};
/**
 * 学生课程数据访问对象
 */
class StudentCourseDAO : public BaseDAO {
public:
	PtrStudentCourseDO selectByIds(
		uint64_t studentId,
		uint64_t courseId,
		uint64_t subjectId
	);
	int updatePayStatus(uint64_t id, double paidAmount, int payOff);
private:

};
class RefundDAO :public BaseDAO {
public:
	PtrRefundDO selectByIds(uint64_t student_course_id);
private:
};

class ContactRecordDAO : public BaseDAO {
public:
	// 删除跟进记录（修改deleted字段为1）
	int deleteContactRecord(uint64_t recordId);
};

#endif 

