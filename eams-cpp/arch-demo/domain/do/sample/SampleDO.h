#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _SAMPLE_DO_
#define _SAMPLE_DO_
#include "../DoInclude.h"

/**
 * 示例数据库实体类
 */
class SampleDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 性别
	MYSQL_SYNTHESIZE(string, sex, Sex);
	// 年龄
	MYSQL_SYNTHESIZE(int, age, Age);
	// 创建人
	MYSQL_SYNTHESIZE(string, createBy, CreateBy);
	// 创建时间
	MYSQL_SYNTHESIZE(string, createTime, CreateTime);
	// 修改人
	MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
	// 修改时间
	MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);
public:
	SampleDO() : BaseDO("sample")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("sex", "s", sex);
		MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("create_by", "s", createBy);
		MYSQL_ADD_FIELD("create_time", "s", createTime);
		MYSQL_ADD_FIELD("update_by", "s", updateBy);
		MYSQL_ADD_FIELD("update_time", "s", updateTime);
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<SampleDO> PtrSampleDO;
#endif // !_SAMPLE_DO_
