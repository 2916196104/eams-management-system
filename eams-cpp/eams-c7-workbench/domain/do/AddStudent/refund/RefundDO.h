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

#ifndef _REFUND_H_
#define _REFUND_H_
#include "../../DoInclude.h"
#include "SqlHelper.h"

class RefundDO :public BaseDO
{
	//文件唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	//学生学号
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	//学生课程关联表id
	MYSQL_SYNTHESIZE(string, studentCourseId, StudentCourseId);
	//退费办理人
	MYSQL_SYNTHESIZE(string, operatorId, OperatorId);
	//退费金额 负数
	MYSQL_SYNTHESIZE(int, refundAmount, RefundAmount);
	//退费课时
	MYSQL_SYNTHESIZE(int, refundLessonCount, RefundLessonCount);
	//退费发起时间
	MYSQL_SYNTHESIZE(string, applyTime, ApplyTime);
	//退费说明
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//退费办完时间
	MYSQL_SYNTHESIZE(string, doneTime, DoneTime);
	//类型
	MYSQL_SYNTHESIZE(string, typeNum, TypeNum);
	//退款状态
	MYSQL_SYNTHESIZE(string, verifyState, VerifyState);
	//审核时间
	MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime);
	//审核人
	MYSQL_SYNTHESIZE(string, verifyStaff, VerifyStaff);
public:
	RefundDO() :BaseDO("refund")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("student_id", "s", studentId, false);
		MYSQL_ADD_FIELD_NULLABLE("student_course_id", "s", studentCourseId, false);
		MYSQL_ADD_FIELD("operator", "s", operatorId);
		MYSQL_ADD_FIELD("refund_amount", "i", refundAmount);
		MYSQL_ADD_FIELD("refund_lesson_count", "i", refundLessonCount);
		MYSQL_ADD_FIELD("apply_time", "s", applyTime);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("done_time", "s", doneTime);
		MYSQL_ADD_FIELD("type_num", "s", typeNum);
		MYSQL_ADD_FIELD("verify_state", "s", verifyState);
		MYSQL_ADD_FIELD("verify_time", "s", verifyTime);
		MYSQL_ADD_FIELD("verify_staff", "s", verifyStaff);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<RefundDO> PtrRefundDO;

/**
 * 文件视图对象，关联一些外表的字段
 */
class RefundViewDO : public RefundDO {
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	MYSQL_SYNTHESIZE(string, operatorName, OperatorName);
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<RefundViewDO> PtrRefundViewDO;

#endif // !_FILEDO_H_