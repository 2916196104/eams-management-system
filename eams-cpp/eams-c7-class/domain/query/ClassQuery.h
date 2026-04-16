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
 * 班级列表查询类
 */
class ClassQuery : public PageQuery
{
    DTO_INIT(ClassQuery, PageQuery);

    // 班级名称（模糊查询）
    API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("class.field.classname"));

    // 课程
    API_DTO_FIELD_DEFAULT(Int64, course, ZH_WORDS_GETTER("class.field.course"));

    // 班主任
    API_DTO_FIELD_DEFAULT(String, homeroom_teacher, ZH_WORDS_GETTER("class.field.homeroom-teacher"));

    // 班级状态（0:停用, 1:启用）
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("class.field.status"));

    // 开始创建时间
    API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("class.field.createtime"));

    // 结束创建时间
    API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("class.field.endtime"));

    //教室
    API_DTO_FIELD_DEFAULT(String, classroom, ZH_WORDS_GETTER("class.field.classroom"));

    //招生进度
    API_DTO_FIELD_DEFAULT(String, enrollment_progress, ZH_WORDS_GETTER("class.field.enrollment-progress"));

    //课程进度
    API_DTO_FIELD_DEFAULT(String, course_progress, ZH_WORDS_GETTER("class.field.course-progress"));

    //备注
    API_DTO_FIELD_DEFAULT(String, remarks, ZH_WORDS_GETTER("class.field.remarks"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_ClassQuery_H_