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
 * 班级添加DTO
 */
class ClassAddDTO : public oatpp::DTO
{
    DTO_INIT(ClassAddDTO, DTO);

    // 班级名称
    API_DTO_FIELD_REQUIRE(String, classname, ZH_WORDS_GETTER("class.field.classname"), true);

    // 班主任
    API_DTO_FIELD_REQUIRE(String, homeroom_teacher, ZH_WORDS_GETTER("class.field.homeroom-teacher"), true);

    //课程
    API_DTO_FIELD_REQUIRE(String, course_name, ZH_WORDS_GETTER("class.field.course"), true);

    //人数
    API_DTO_FIELD_REQUIRE(Int64, num_of_people, ZH_WORDS_GETTER("class.field.num-of-people"), true);

    // 班级状态（0:停用, 1:启用）
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("class.field.status"));

    // 开始创建时间
    API_DTO_FIELD_DEFAULT(String, CreateTime, ZH_WORDS_GETTER("class.field.createtime"));

    //教室
    API_DTO_FIELD_DEFAULT(String, classroom, ZH_WORDS_GETTER("class.field.classroom"));

    //招生进度
    API_DTO_FIELD_DEFAULT(String, enrollment_progress, ZH_WORDS_GETTER("class.field.enrollment-progress"));

    //课程进度
    API_DTO_FIELD_DEFAULT(String, course_progress, ZH_WORDS_GETTER("class.field.course-progress"));

    //备注
    API_DTO_FIELD_DEFAULT(String, remarks, ZH_WORDS_GETTER("class.field.remarks"));
};

/**
 * 班级详情DTO（用于返回和修改）
 */
class ClassDTO : public oatpp::DTO
{
    DTO_INIT(ClassDTO, DTO);

    // 班级名称
    API_DTO_FIELD_REQUIRE(String, classname, ZH_WORDS_GETTER("class.field.classname"), true);

    // 班级id
    API_DTO_FIELD_REQUIRE(Int64, class_id, ZH_WORDS_GETTER("class.field.id"), true);

    // 班主任
    API_DTO_FIELD_REQUIRE(String, homeroom_teacher, ZH_WORDS_GETTER("class.field.homeroom-teacher"), true);

    //课程
    API_DTO_FIELD_REQUIRE(String, course_name, ZH_WORDS_GETTER("class.field.course"), true);

    //人数
    API_DTO_FIELD_REQUIRE(Int64, num_of_people, ZH_WORDS_GETTER("class.field.num-of-people"), true);

    // 班级状态（0:停用, 1:启用）
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("class.field.status"));

    // 开始创建时间
    API_DTO_FIELD_DEFAULT(String, StartDate, ZH_WORDS_GETTER("class.field.createtime"));

    // 截止时间 
    API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("class.field.enddate"));

    //教室
    API_DTO_FIELD_DEFAULT(String, classroom, ZH_WORDS_GETTER("class.field.classroom"));

    //招生进度
    API_DTO_FIELD_DEFAULT(String, enrollment_progress, ZH_WORDS_GETTER("class.field.enrollment-progress"));

    //课程进度
    API_DTO_FIELD_DEFAULT(String, course_progress, ZH_WORDS_GETTER("class.field.course-progress"));

    //备注
    API_DTO_FIELD_DEFAULT(String, remarks, ZH_WORDS_GETTER("class.field.remarks"));
};
/**
 * 班级分页DTO
 */
class ClassPageDTO : public PageDTO<ClassDTO::Wrapper>
{
    DTO_INIT(ClassPageDTO, PageDTO<ClassDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_DTO_