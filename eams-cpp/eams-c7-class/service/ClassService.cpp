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
#include "ClassService.h"
#include "../eams-c7-class/dao/Class/ClassDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include "../eams-c7-class/Macros.h"

/**
 * 分页查询所有班级
 * 方法步骤解释：
 * 1. 创建分页返回对象
 * 2. 查询总记录数
 * 3. 如果总数>0，计算分页并查询数据
 * 4. 将DO转换为DTO
 */
ClassPageDTO::Wrapper ClassService::listAll(const ClassQuery::Wrapper& query)
{
	// 构建返回对象
	// 这里使用ClassPageDTO，一个PageDTO的包装，用于分页查询
	auto pages = ClassPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	// 调用DAO的count方法，传入查询条件
	ClassDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		// 如果没有数据，直接返回空的分页对象
		return pages;
	}

	// 计算分页并查询数据
	// 设置总记录数，并计算总页数
	pages->total = count;
	pages->calcPages();

	// 分页查询数据，获取DO列表
	std::list<ClassViewDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	// 遍历DO列表，将每个DO转换为DTO，并添加到分页结果中
	for (ClassViewDO& sub : result)
	{
		auto dto = ClassDTO::createShared();


		dto->class_id = sub.getId();
		dto->classname = oatpp::String(sub.getName());
		dto->num_of_people = static_cast<int64_t>(sub.getPlannedStudentCount());
		dto->status = sub.getBeOver() ? 1 : 0;
		dto->StartDate = oatpp::String(sub.getStartDate());
		dto->endDate = oatpp::String(sub.getEndDate());
		dto->classroom = oatpp::String(std::to_string(sub.getClassroomId()));
		dto->remarks = oatpp::String(sub.getRemark());
		dto->homeroom_teacher = oatpp::String(sub.getTeacherName());
		dto->course_name = oatpp::String(sub.getCourseName());
		dto->enrollment_progress = "";
		dto->course_progress = "";
		pages->addData(dto);
	}
	return pages;
}

/**
 * 通过ID查询单个班级
 *
 * 1. 调用DAO查询数据
 * 2. 检查查询结果
 * 3. 将DO转换为DTO
 */
ClassDTO::Wrapper ClassService::getById(int64_t id)
{
	ClassDAO dao;
	auto res = dao.selectById(id);
	if (res.safeGetId() <= 0)
	{
		return nullptr;
	}

	// 创建一个 DTO
	auto dto = ClassDTO::createShared();

	dto->class_id = res.getId();
	dto->classname = oatpp::String(res.getName());
	dto->homeroom_teacher = oatpp::String(res.getTeacherName());
	dto->course_name = oatpp::String(res.getCourseName());
	dto->num_of_people = static_cast<int64_t>(res.getPlannedStudentCount());
	dto->status = res.getBeOver() ? 1 : 0;
	dto->StartDate = oatpp::String(res.getStartDate());
	dto->classroom = oatpp::String(std::to_string(res.getClassroomId()));
	dto->remarks = oatpp::String(res.getRemark());
	dto->enrollment_progress = "";
	dto->endDate = oatpp::String(res.getEndDate());
	dto->course_progress = "";

	return dto;
}

/*
ClassDTO::Wrapper ClassService::getByName(const std::string& name)
{
	ClassDAO dao;
	auto res = dao.selectByName(name);

	if (res.safeGetId() <= 0)
	{
		return nullptr;
	}

	// 创建一个 DTO
	auto dto = ClassDTO::createShared();

	dto->class_id = res.safeGetId();
	dto->classname = oatpp::String(res.getName());
	dto->homeroom_teacher = oatpp::String(res.getTeacherName());
	dto->course_name = oatpp::String(res.getCourseName());
	dto->num_of_people = static_cast<int64_t>(res.getPlannedStudentCount());
	dto->status = res.getBeOver() ? 1 : 0;
	dto->CreateTime = oatpp::String(res.getAddTime());
	dto->classroom = oatpp::String(std::to_string(res.getClassroomId()));
	dto->remarks = oatpp::String(res.getRemark());
	dto->enrollment_progress = "";
	dto->course_progress = "";

	return dto;
}
*/