#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:08:56

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
#ifndef _CLASS_SERVICE_
#define _CLASS_SERVICE_

#include "domain/vo/ClassVO.h"
#include "domain/query/ClassQuery.h"
#include "domain/dto/ClassDTO.h"

/**
 * 班级服务类
 * Service层的作用：
 * 1. 处理业务逻辑
 * 2. 协调多个DAO操作
 * 3. 数据转换（DTO <-> DO）
 * 4. 事务管理（如果需要）
 * 5. 调用外部服务
 */
class ClassService
{
public:
	// 分页查询所有班级
	ClassPageDTO::Wrapper listAll(const ClassQuery::Wrapper& query);

	// 通过班级ID查询单个班级
	ClassDTO::Wrapper getById(int64_t id);

	//通过名称查询
	//ClassDTO::Wrapper getByName(const std::string& name);

	// 保存班级数据（新增）
	//int64_t saveData(const ClassAddDTO::Wrapper& dto);

	// 修改班级数据
	//bool updateData(const ClassDTO::Wrapper& dto);

	// 通过ID列表删除班级数据
	//bool removeData(const oatpp::List<oatpp::Int64>& ids);
};

#endif // !_CLASS_SERVICE_