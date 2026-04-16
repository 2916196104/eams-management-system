/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 16:58:02

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
#include "RegistRecordService.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"
RegistRecordPageDTO::Wrapper RegistRecordService::listAll(const RegistRecordQuery::Wrapper& query) {
	//构建返回对象
	auto pages = RegistRecordPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	//查询数据总条数
	RegistRecordViewDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0) {
		return pages;
	}

	//分页查询数据
	pages->total = count;
	pages->calcPages();
	
	// 注意：由于DO禁用了复制构造，遍历最好使用引用，避免发生二次复制行为
	list<RegistRecordViewDO> result = dao.selectWithPage(query);
	//将DO转换成DTO
	for (RegistRecordViewDO& sub : result) {
		auto dto = RegistRecordDTO::createShared();
		//ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, studentName, StudentName, courseName, CourseName, startDate, StartDate, expireDate, ExpireDate, paidAmount, PaidAmount);
		dto->id = sub.getId();
		dto->studentName = sub.getStudentName().c_str();
		dto->courseName = sub.getCourseName().c_str();
		dto->startDate = sub.getStartDate().c_str();
		dto->expireDate = sub.getExpireDate().c_str();
		dto->paidAmount = sub.getPaidAmount();
		pages->addData(dto);
	}
	return pages;
}

RegistRecordDTO::Wrapper RegistRecordService::getById(std::string id) {
	// 查询数据
	RegistRecordViewDAO dao;
	auto res = dao.selectById(id);

	// 没有查询到数据
	if (!res)
		return nullptr;

	// 查询到数据转换成DTO
	auto dto = RegistRecordDTO::createShared();
	//ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, studentName, StudentName, courseName, CourseName, subjectName, SubjectName, startDate, StartDate, courseAmount, CourseAmount, discountAmount, DiscountAmount, paidAmount, PaidAmount, expireDate, ExpireDate, addTime, AddTime, remark, Remark, countLessonTotal, CountLessonTotal, countLessonComplete, CountLessonComplete, remainingCount, RemainingCount, refundAmount, RefundAmount, refundLessonCount, RefundLessonCount);
	// 1. 手动逐个字段赋值，这样哪个字段报错编译器会直接指出来
	dto->id = res->getId();
	dto->studentName = res->getStudentName().c_str();
	dto->courseName = res->getCourseName().c_str();
	dto->subjectName = res->getSubjectName().c_str();
	dto->startDate = res->getStartDate().c_str();
	dto->courseAmount = res->getCourseAmount(); // double 转 oatpp::Float64
	dto->paidAmount = res->getPaidAmount();
	dto->discountAmount = res->getDiscountAmount();
	dto->expireDate = res->getExpireDate().c_str();
	dto->addTime = res->getAddTime().c_str();
	dto->remark = res->getRemark().c_str();
	dto->countLessonTotal = res->getCountLessonTotal();
	dto->countLessonComplete = res->getCountLessonComplete();
	dto->remainingCount = res->getRemainingCount();
	// 2. 处理退款信息 (Refund)
	// 修复：不能将 String 对象或普通 std::string 实例和 nullptr 进行比较，应该使用 empty() 方法进行判空
	if (!res->getId()) {
	// 退款金额
		dto->refundAmount = res->getRefundAmount();
		// 退款课时
		dto->refundLessonCount = res->getRefundLessonCount();

	}
	// 在 Service 层组装 DTO 时计算
	dto->debt = res->getCourseAmount() - res->getPaidAmount();

	return dto;
}