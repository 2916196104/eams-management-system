#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 11:01:02

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
#ifndef _ClassQuery_H_
#define _ClassQuery_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级查询对象
 */
class ClassQuery : public PageQuery {
    DTO_INIT(ClassQuery, PageQuery);

    // 班级名称（模糊查询）
    API_DTO_FIELD_DEFAULT(String, className, u8"班级名称");

    // 年级
    API_DTO_FIELD_DEFAULT(UInt32, grade, u8"年级");

    // 专业ID
    API_DTO_FIELD_DEFAULT(UInt64, majorId, u8"专业ID");

    // 班主任ID
    API_DTO_FIELD_DEFAULT(UInt64, headTeacherId, u8"班主任ID");

    // 状态（0:停用, 1:启用）
    API_DTO_FIELD_DEFAULT(Int32, status, u8"状态");

    // 开始创建时间
    API_DTO_FIELD_DEFAULT(String, startCreateTime, u8"开始创建时间");

    // 结束创建时间
    API_DTO_FIELD_DEFAULT(String, endCreateTime, u8"结束创建时间");
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_ClassQuery_H_