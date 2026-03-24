#pragma once
#ifndef _COMMON_DAO_
#define _COMMON_DAO_
#include "BaseDAO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/query/common/CommonQuery.h"

/**
 * 班级列表数据访问对象
 */
class getClassListDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const getClassListQuery::Wrapper& query, SqlParams& params);
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
	inline std::string queryConditionBuilder(const getCourseStatisticsQuery::Wrapper& query, SqlParams& params);
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
	inline std::string queryConditionBuilder(const JoinclassQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const JoinclassQuery::Wrapper& query);
	// 分页查询数据
	std::list<JoinclassDO> selectWithPage(const JoinclassQuery::Wrapper& query);
	std::list<PtrJoinclassDO> JoinclassDAO::selectWithPagePtr(const JoinclassQuery::Wrapper& query);
};








#endif 
