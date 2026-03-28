#pragma once

#ifndef _HH_SERVICE_
#define _HH_SERVICE_

#include "../../../domain/dto/hh-dto/ClassroomDTO.h"
#include "../../../domain/query/hh-query/ClassroomQuery.h"
#include "../../../domain/dto/hh-dto/CustomerDTO.h"
#include "../../../domain/query/hh-query/CustomerQuery.h"

class HhService {
public:
	// 接口一：分页查询student表
	CustomerPageDTO::Wrapper listAllStudent(const CustomerQuery::Wrapper& query, std::string creator_id);
	// 接口二：通过ID查询学生的Detail
	CustomerDetailDTO::Wrapper getDetailById(std::string id);
	// 接口三：通过ID查询学生的课程
	CustomerLessonListDTO::Wrapper getLessonListById(std::string id);
	// 接口四：分页查询classroom表
	ClassroomPageDTO::Wrapper listAllClassroom(const ClassroomQuery::Wrapper& query);
};

#endif