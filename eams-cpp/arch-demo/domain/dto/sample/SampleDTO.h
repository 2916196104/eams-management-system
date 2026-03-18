#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:59:38

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
#ifndef _SAMPLE_DTO_
#define _SAMPLE_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例新增数据传输对象
 */
class SampleAddDTO : public oatpp::DTO
{
	DTO_INIT(SampleAddDTO, DTO);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("sample.field.name");
	}
	// 年龄
	DTO_FIELD(Int32, age);
	DTO_FIELD_INFO(age) {
		info->description = ZH_WORDS_GETTER("sample.field.age");
	}
	// 性别
	DTO_FIELD(String, sex);
	DTO_FIELD_INFO(sex) {
		info->description = ZH_WORDS_GETTER("sample.field.sex");
	}

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		if (!age || age < 0)
			return "age invalidate.";
		if (!name || name->empty())
			return "name invalidate.";
		if (!sex || sex->empty())
			return "sex invalidate.";
		return "";
	}
};

/**
 * 示例传输对象
 */
class SampleDTO : public SampleAddDTO
{
	DTO_INIT(SampleDTO, SampleAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("sample.field.id");
	}
};

/**
 * 示例分页传输对象
 */
class SamplePageDTO : public PageDTO<SampleDTO::Wrapper>
{
	DTO_INIT(SamplePageDTO, PageDTO<SampleDTO::Wrapper>);
};

/**
 * 导入数据传输对象
 */
class SampleImportDTO : public oatpp::DTO
{
	DTO_INIT(SampleImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("sample.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_