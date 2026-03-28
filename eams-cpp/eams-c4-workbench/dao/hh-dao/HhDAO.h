#pragma once

#ifndef _HH_DAO_
#define _HH_DAO_
#include "BaseDAO.h"
#include "../../domain/do/ClassroomDO.h"
#include "../../domain/query/hh-query/CustomerQuery.h"
#include "../../domain/query/hh-query/ClassroomQuery.h"
#include "../../domain/do/ClassroomDO.h"
#include "../../domain/do/hh-do/HhDO.h"


class HhDAO : public BaseDAO {
private:
	// 根据CustomerQuery动态构建查询条件
	// 教室分页查询没有任何查询条件
	//inline std::string queryConditionBuilder(const CustomerQuery::Wrapper& query, SqlParams& params);
public:
	// 统计客户数据条数
	uint64_t countCustomer(const CustomerQuery::Wrapper& query, std::string creator_id);
	// 统计教室数据条数
	uint64_t countClassroom(const ClassroomQuery::Wrapper& query);
	// 接口一：分页查询客户数据
	std::list<HhStudentViewDO> selectCustomerWithPage(const CustomerQuery::Wrapper& query, std::string creator_id);
	// 接口二：通过学生ID查询学生详情
	PtrHhStudentViewDO selectCustomerDetailWithId(std::string id);
	// 接口三：通过学生ID查询学生课程
	std::list<HhCourseViewDO> selectCourseWithId(std::string id);
	// 接口四：分页查询教室数据
	std::list<ClassroomDO> selectClassroomWithPage(const ClassroomQuery::Wrapper& query);
};

#endif