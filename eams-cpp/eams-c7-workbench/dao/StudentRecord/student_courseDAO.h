#ifndef _STUDENT_COURSE_DAO_
#define _STUDENT_COURSE_DAO_
#include "BaseDAO.h"
#include "../../domain/do/StudentRecord/student_course/student_coursedo.h"
#include "../../domain/query/StudentRecord/studentinformation.h"
#include "../../domain/do/StudentRecord/view/student_courseviewdo.h"
/**
 * 学生课程表数据库操作实现
 */
class StudentCourseDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const StudentQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const StudentQuery::Wrapper& query);
	// 分页查询 获取课程名称，报名时间，购买课程数，费用 数据
	std::list<CourseProgressViewDO> selectWithPageCourseProgress(const StudentQuery::Wrapper& query);
	// 分页查询 获取课程名称，课程状态，课程总数，已完成数，未完成数 数据(需要连course表）
	std::list<StudentSignUpViewDO> selectWithPageStudentSighnUP(const StudentQuery::Wrapper& query);
	// 分页查询 
	std::list<CourseRecordViewDO> selectWithPageCourseRecord(const StudentQuery::Wrapper& query);
	
};
#endif // !_SAMPLE_DAO_
