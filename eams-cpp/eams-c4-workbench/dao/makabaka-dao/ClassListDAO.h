#pragma once

#ifndef _CLASSLISTDAO_H_
#define _CLASSLISTDAO_H_

#include"BaseDAO.h"
#include"../../domain/do/ClassDO.h"
#include"../../domain/query/makabaka-query/class/classQuery.h"

class ClassListDAO :public BaseDAO {
private:
	//sql语句条件构建
	inline  std::string queryConditionBuilder(const ClassQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	uint64_t count(const ClassQuery::Wrapper& query);
	//分页查询数据
	std::list<ClassDO> selectWithPage(const ClassQuery::Wrapper& query);
	//通过姓名查询数据
	std::list<ClassDO> selectByName(const string& name);
};

#endif  //!_CLASSLISTDAO_H_