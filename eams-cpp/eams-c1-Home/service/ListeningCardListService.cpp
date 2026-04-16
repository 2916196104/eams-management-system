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
#include "ListeningCardListService.h"
#include"../domain/dto/listening-card/cardDTO.h"
#include "SimpleDateTimeFormat.h"
#include"../../lib-common/include/id/SnowFlake.h"

ListeningCardPageDTO::Wrapper ListeningCardListService::listAll(const oatpp::String& userId)
{
	// 构建返回对象
	auto pages = ListeningCardPageDTO::createShared();
	pages->pageIndex = 1;
	pages->pageSize = 1000;

	ListeningCardDAO dao;

	list<cardDO> result = dao.selectCardByUserId(userId);

	// 将DO转换成DTO
	for (cardDO& sub : result)
	{
		auto dto = ListeningCardDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, courseId, CourseId, title, Title, endDate, EndDate, lessonCount, LessonCount, addTime, AddTime);
		pages->addData(dto);
	}

	return pages;
}

bool ListeningCardListService::claimCard(const receiveCardDTO::Wrapper& dto)
{
	cardRecordDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, TrialId, trialId, StudentId, studentId, CourseId, courseId);
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, UserId, userId , EndDate, endDate);
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, LessonCount, lessonCount, SchoolId, schoolId);
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Counselor, counselor);
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, StudentCourseId, studentCourseId, AddTime, addTime);
	SnowFlake sf(1, 1);
	//雪花算法插入id
	data.setId(sf.nextId());
	// 执行数据修改
	ListeningCardDAO dao;
	return  dao.insert(data) == 1;
}
