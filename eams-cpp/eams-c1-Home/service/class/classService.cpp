/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:13:11

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
#include "classService.h"
#include "../../dao/class/classDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

ClassPageDTO::Wrapper ClassService::listAll(const classQuery::Wrapper& query)
{
    // 构建返回对象
    auto pages = ClassPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    // 查询数据总条数
    ClassDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages;
    }

    // 分页查询数据
    pages->total = count;
    pages->calcPages();

    list<ClassDO> result = dao.selectWithPage(query);

    // 将 DO 转换成 DTO
    for (ClassDO& sub : result)
    {
        auto dto = ClassDTO::createShared();

        ZO_STAR_DOMAIN_DO_TO_DTO(
            dto, sub,
            class_name, Name,
            teacher_name, Teacher_Name,
            course_name, Course_Name,
            start_date, StartDate,
            end_date, EndDate,
            student_count, StudentCount
        );

        pages->addData(dto);
    }

    return pages;
}

/**
name 班级名
start_date 计划开班日期
end_date 计划结业日期
remark 排课备注
classroom 教室名
teacher_name （教师）姓名
course_name 课程名
student_count 班级人数
over_lesson_count 课次数量
*/
ClassInfoDTO::Wrapper ClassService::getById(const uint64_t& id)
{
    ClassDAO dao;
    ClassDO result = dao.selectById(id);
    auto dto = ClassInfoDTO::createShared();
	if (!result.getIdPtr()) {
        return nullptr;
    }
    ZO_STAR_DOMAIN_DO_TO_DTO(
        dto, result,
        class_name, Name,
        start_date, StartDate,
        end_date, EndDate,
        teacher_name, Teacher_Name,
        course_name, Course_Name,
        remark,Remark,
        classroom_name,ClassRoom,
        student_count, StudentCount,
		over_lesson_count, Over_Lesson_Count
    );
    return dto;
}

// 通过班级id查询学生列表
StudentListDTO::Wrapper StudentService::listByClassId(uint64_t class_id)
{
	auto listdto = StudentListDTO::createShared();
	StudentDAO dao;
	list<StudentDO> result = dao.selectByClassId(class_id);
	//避免空指针异常，先创建一个空的列表对象
    if (!listdto->student_list) {
        listdto->student_list = oatpp::List<StudentDTO::Wrapper>::createShared();
    }
    for (StudentDO& sub : result)
    {
        auto dto = StudentDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(
            dto, sub,
            name, Name,
            gender, Gender
        );
		listdto->student_list->push_back(dto);
    }
    return listdto;
}