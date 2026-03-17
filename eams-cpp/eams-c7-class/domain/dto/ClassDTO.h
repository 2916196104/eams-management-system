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
#ifndef _CLASS_DTO_
#define _CLASS_DTO_
#include "../GlobalInclude.h"
#include "domain/dto/PageDTO.h"
#include "domain/vo/JsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 班级数据传输对象（用于新增）
 */
class ClassAddDTO : public oatpp::DTO
{
    DTO_INIT(ClassAddDTO, DTO);

    // 班级名称
    DTO_FIELD(String, className);
    DTO_FIELD_INFO(className) {
        info->required = true;
#ifndef LINUX
        info->description = u8"班级名称";
#else
        info->description = "class name";
#endif
    }

    // 年级
    DTO_FIELD(String, grade);
    DTO_FIELD_INFO(grade) {
        info->required = true;
#ifndef LINUX
        info->description = u8"年级";
#else
        info->description = "grade";
#endif
    }

    // 班级编号
    DTO_FIELD(String, classCode);
    DTO_FIELD_INFO(classCode) {
        info->required = true;
#ifndef LINUX
        info->description = u8"班级编号";
#else
        info->description = "class code";
#endif
    }

    // 班主任ID
    DTO_FIELD(UInt64, teacherId);
    DTO_FIELD_INFO(teacherId) {
#ifndef LINUX
        info->description = u8"班主任ID";
#else
        info->description = "teacher id";
#endif
    }

    // 班级描述
    DTO_FIELD(String, description);
    DTO_FIELD_INFO(description) {
#ifndef LINUX
        info->description = u8"班级描述";
#else
        info->description = "description";
#endif
    }

    // 最大学生人数
    DTO_FIELD(UInt32, maxStudents);
    DTO_FIELD_INFO(maxStudents) {
#ifndef LINUX
        info->description = u8"最大学生人数";
#else
        info->description = "maximum students";
#endif
    }

public:
    // 数据校验
    std::string validate()
    {
        if (!className || className->empty())
            return "class name cannot be empty.";
        if (!grade || grade->empty())
            return "grade cannot be empty.";
        if (!classCode || classCode->empty())
            return "class code cannot be empty.";
        if (maxStudents && maxStudents > 100)
            return "maximum students cannot exceed 100.";
        return "";
    }
};

/**
 * 班级数据传输对象（用于更新和详情）
 */
class ClassDTO : public ClassAddDTO
{
    DTO_INIT(ClassDTO, ClassAddDTO);

    // 班级ID
    DTO_FIELD(UInt64, classId);
    DTO_FIELD_INFO(classId) {
        info->required = true;
#ifndef LINUX
        info->description = u8"班级ID";
#else
        info->description = "class id";
#endif
    }

    // 状态 (0:停用, 1:启用)
    DTO_FIELD(UInt32, status);
    DTO_FIELD_INFO(status) {
#ifndef LINUX
        info->description = u8"状态";
#else
        info->description = "status";
#endif
    }

    // 创建时间
    DTO_FIELD(String, createTime);
    DTO_FIELD_INFO(createTime) {
#ifndef LINUX
        info->description = u8"创建时间";
#else
        info->description = "create time";
#endif
    }

    // 更新时间
    DTO_FIELD(String, updateTime);
    DTO_FIELD_INFO(updateTime) {
#ifndef LINUX
        info->description = u8"更新时间";
#else
        info->description = "update time";
#endif
    }

    // 创建人
    DTO_FIELD(String, createBy);
    DTO_FIELD_INFO(createBy) {
#ifndef LINUX
        info->description = u8"创建人";
#else
        info->description = "creator";
#endif
    }

    // 更新人
    DTO_FIELD(String, updateBy);
    DTO_FIELD_INFO(updateBy) {
#ifndef LINUX
        info->description = u8"更新人";
#else
        info->description = "updater";
#endif
    }
};

/**
 * 班级分页数据传输对象
 */
class ClassPageDTO : public PageDTO<ClassDTO::Wrapper>
{
    DTO_INIT(ClassPageDTO, PageDTO<ClassDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_DTO_