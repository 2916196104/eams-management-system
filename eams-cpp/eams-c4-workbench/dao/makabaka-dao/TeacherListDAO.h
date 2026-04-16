#pragma once
#ifndef _TEACHERLISTDAO_H_
#define _TEACHERLISTDAO_H_
#include"BaseDAO.h"	
#include"../../domain/dto/makabaka-dto/teacher/teacherDTO.h"
#include"../../domain/query/makabaka-query/teacher/teacherQuery.h"

class TeacherListDAO :public BaseDAO{
private:
	inline std::string queryConditonBuilder(const TeacherQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	uint64_t count(const TeacherQuery::Wrapper& query);
	//分页查询数据
	std::list<TeacherDTO::Wrapper> selectWithPage(const TeacherQuery::Wrapper& query);
};

#endif // !_TEACHERLISTDAO_H_