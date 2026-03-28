/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:58:42

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

#include "stdafx.h"
#include "GetClassController.h"
#include "../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "domain/vo/ClassVO.h"
#include "../eams-c7-class/service/ClassService.h"

ClassJsonVO::Wrapper GetClassController::execQueryClassDetail(const oatpp::Int64& classId)
{
    auto jvo = ClassJsonVO::createShared();

    // 先创建一个空的DTO用于返回
    auto emptyClassDto = ClassDTO::createShared();

    if (!classId || classId <= 0)
    {
        jvo->fail(emptyClassDto);
        return jvo;
    }

    try {
        ClassService service;
        auto result = service.getById(classId);

        if (result)
        {
            jvo->success(result);
        }
        else
        {
            jvo->fail(emptyClassDto);
        }
    }
    catch (const std::exception& e)
    {
        // 使用空DTO
        jvo->fail(emptyClassDto);
    }
    return jvo;
}

ClassPageJsonVO::Wrapper GetClassController::execQueryPage(const ClassQuery::Wrapper& query)
{
    auto jvo = ClassPageJsonVO::createShared();

    // 创建空的ClassPageDTO用于返回
    auto emptyPageDto = ClassPageDTO::createShared();

    if (!query)
    {
        jvo->fail(emptyPageDto);
        return jvo;
    }

    // 创建查询对象的副本
    auto queryCopy = ClassQuery::createShared();

    // 复制查询条件字段
    if (query->className) queryCopy->className = query->className;
    if (query->course) queryCopy->course = query->course;
    if (query->homeroom_teacher) queryCopy->homeroom_teacher = query->homeroom_teacher;
    if (query->status) queryCopy->status = query->status;
    if (query->startTime) queryCopy->startTime = query->startTime;
    if (query->endTime) queryCopy->endTime = query->endTime;
    if (query->classroom) queryCopy->classroom = query->classroom;
    if (query->enrollment_progress) queryCopy->enrollment_progress = query->enrollment_progress;
    if (query->course_progress) queryCopy->course_progress = query->course_progress;
    if (query->remarks) queryCopy->remarks = query->remarks;

    // 复制分页字段
    queryCopy->pageIndex = query->pageIndex;
    queryCopy->pageSize = query->pageSize;

    // 校正分页参数
    if (queryCopy->pageIndex < 1)
    {
        queryCopy->pageIndex = 1;
    }
    if (queryCopy->pageSize < 1)
    {
        queryCopy->pageSize = 10;
    }
    if (queryCopy->pageSize > 100)
    {
        queryCopy->pageSize = 100;
    }

    try {
        ClassService service;
        auto result = service.listAll(queryCopy);

        if (!result || result->rows->size() == 0)
        {
            jvo->fail(emptyPageDto);
            return jvo;
        }

        jvo->success(result);
        return jvo;
    }
    catch (const std::exception& e)
    {
        jvo->fail(emptyPageDto);
        return jvo;
    }
}