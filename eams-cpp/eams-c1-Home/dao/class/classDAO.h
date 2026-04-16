#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _CLASSDAO_H_
#define _CLASSDAO_H_
#include "BaseDAO.h"
#include "../../domain/do/class/ClassDO.h"
#include "../../domain/query/class/classquery.h"

/**
 * class表数据库操作实现
 */
class ClassDAO : public BaseDAO
{
private:
	
	inline std::string queryConditionBuilder(const classQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const classQuery::Wrapper& query);
	// 分页查询数据
	std::list<ClassDO> selectWithPage(const classQuery::Wrapper& query);
	//id查询班级详情
	ClassDO selectById(const uint64_t& id);
};
/**
* student表数据库操作实现
*/
class StudentDAO : public BaseDAO
{
public:
	// 通过id查询数据列表
	std::list<StudentDO> selectByClassId(const uint64_t& class_id);
};
#endif // !_CLASSDAO_H_
