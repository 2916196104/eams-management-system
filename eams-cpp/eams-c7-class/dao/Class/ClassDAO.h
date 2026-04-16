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
#ifndef _CLASS_DAO_
#define _CLASS_DAO_
#include "BaseDAO.h"
#include "../eams-c7-class/domain/do/ClassDO.h"
#include "../eams-c7-class/domain/query/ClassQuery.h"

/**
 * 班级表数据库操作实现
 */
class ClassDAO : public BaseDAO
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
    inline std::string queryConditionBuilder(const ClassQuery::Wrapper& query, SqlParams& params);
public:
    // 统计满足条件的班级数量
    uint64_t count(const ClassQuery::Wrapper& query);
    // 分页查询班级列表
	std::list<ClassViewDO> selectWithPage(const ClassQuery::Wrapper& query);
	// 通过班级ID查询单个班级详情
	ClassViewDO selectById(int64_t id); 
	//ClassViewDO selectByName(const std::string& name);
};
#endif // !_CLASS_DAO_