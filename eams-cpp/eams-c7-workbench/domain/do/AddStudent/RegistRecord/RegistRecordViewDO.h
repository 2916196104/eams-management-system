#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:47:24

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

#ifndef _REGISTRECORDVIEWDO_H_
#define _REGISTRECORDVIEWDO_H_
#include "../../DoInclude.h"
#include "SqlHelper.h"
#include "domain/do/AddStudent/LessonLog/StudentLessonCountLogDO.h"
#include "domain/do/AddStudent/refund/RefundDO.h"

class RegistRecordViewDO {
	//文件唯一标识
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	MYSQL_SYNTHESIZE(string, subjectName, SubjectName);
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	//课程金额
	MYSQL_SYNTHESIZE(double, courseAmount, CourseAmount);
	//实付金额
	MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
	//优惠金额
	MYSQL_SYNTHESIZE(double, discountAmount, DiscountAmount);
	//欠款金额
	//MYSQL_SYNTHESIZE(double, debt, Debt);

	MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(int, countLessonTotal, CountLessonTotal);
	MYSQL_SYNTHESIZE(int, countLessonComplete, CountLessonComplete);
	MYSQL_SYNTHESIZE(int, remainingCount, RemainingCount);
	MYSQL_SYNTHESIZE(double, refundAmount, RefundAmount);
	MYSQL_SYNTHESIZE(int, refundLessonCount, RefundLessonCount);
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<RegistRecordViewDO> PtrRegistRecordViewDO;

#endif // !_REGISTRECORDVIEWDO_H_