#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

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
#ifndef _REGISTRATIONDTO_H_
#define _REGISTRATIONDTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */
// 报名记录DTO
class RegistrationRecordDTO : public oatpp::DTO
{
	DTO_INIT(RegistrationRecordDTO, DTO);

	// =========================================================================
	// 1. 必须的字段 
	// =========================================================================

	// 记录唯一标识
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("registration-records.id"));
	// 学生id
	API_DTO_FIELD_DEFAULT(Int64, student_id, ZH_WORDS_GETTER("registration-records.student_id"));
	// 学生姓名
	API_DTO_FIELD_DEFAULT(String, student_name, ZH_WORDS_GETTER("registration-records.student_name"));
	// 课程id
	API_DTO_FIELD_DEFAULT(Int64, course_id, ZH_WORDS_GETTER("registration-records.course_id"));
	// 课程名称
	API_DTO_FIELD_DEFAULT(String, course_name, ZH_WORDS_GETTER("registration-records.course_name"));
	// 科目id
	API_DTO_FIELD_DEFAULT(Int64, subject_id, ZH_WORDS_GETTER("registration-records.subject_id"))
	// 科目名称
	API_DTO_FIELD_DEFAULT(String, subject_name, ZH_WORDS_GETTER("registration-records.subject_name"));
	// 报名时间
	API_DTO_FIELD_DEFAULT(String, add_time, ZH_WORDS_GETTER("registration-records.add_time"));
	// 过期时间
	API_DTO_FIELD_DEFAULT(String, expire_date, ZH_WORDS_GETTER("registration-records.expire_date"));
	// 课程金额
	API_DTO_FIELD_DEFAULT(Float64, amount, ZH_WORDS_GETTER("registration-records.amount"));
	// 实付金额
	API_DTO_FIELD_DEFAULT(Float64, paid_amount, ZH_WORDS_GETTER("registration-records.paid_amount"));
	// 总课次
	API_DTO_FIELD_DEFAULT(Int32, count_lesson_total, ZH_WORDS_GETTER("registration-records.count_lesson_total"));
	// 已上课次
    API_DTO_FIELD_DEFAULT(Int32, count_lesson_complete, ZH_WORDS_GETTER("registration-records.count_lesson_complete"));
	// 报名类型
	API_DTO_FIELD_DEFAULT(Int8, lesson_type, ZH_WORDS_GETTER("registration-records.lesson_type"));
	// 审核状态
	API_DTO_FIELD_DEFAULT(Int8, verify_state, ZH_WORDS_GETTER("registration-records.verify_state"));
	// 是否已过期标记
	API_DTO_FIELD_DEFAULT(Boolean, expired, ZH_WORDS_GETTER("registration-records.expired"));

	// =========================================================================
	// 2. 可能多出的字段：状态相关
	// =========================================================================
	/*
	// 开始日期
	API_DTO_FIELD_DEFAULT(String, start_date, ZH_WORDS_GETTER("registration-records.start_date"));
	// 备注说明
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("registration-records.remark"));
	// 扣课优先级
	API_DTO_FIELD_DEFAULT(Int32, priority, ZH_WORDS_GETTER("registration-records.priority"));
	// 操作人姓名
	API_DTO_FIELD_DEFAULT(String, operator_name, ZH_WORDS_GETTER("registration-records.operator_name"));
	// 课时不足警告标记
	API_DTO_FIELD_DEFAULT(Boolean, warning, ZH_WORDS_GETTER("registration-records.warning"));
	*/
	// =========================================================================
	// 3. 可能多出的字段：考勤统计相关
	// =========================================================================
	/*
	// 出勤次数
	API_DTO_FIELD_DEFAULT(Int32, count_sign, ZH_WORDS_GETTER("registration-records.count_sign"));
	// 请假次数
	API_DTO_FIELD_DEFAULT(Int32, count_leave, ZH_WORDS_GETTER("registration-records.count_leave"));
	// 缺勤次数
	API_DTO_FIELD_DEFAULT(Int32, count_absent, ZH_WORDS_GETTER("registration-records.count_absent"));
	// 迟到次数
	API_DTO_FIELD_DEFAULT(Int32, count_late, ZH_WORDS_GETTER("registration-records.count_late"));
	*/
	// =========================================================================
	// 4. 可能多出的字段：财务退款相关
	// =========================================================================
	/*
	// 优惠金额
	API_DTO_FIELD_DEFAULT(Float64, discount_amount, ZH_WORDS_GETTER("registration-records.discount_amount"));
	// 欠费金额
	API_DTO_FIELD_DEFAULT(Float64, arrearage, ZH_WORDS_GETTER("registration-records.arrearage"));
	// 剩余金额
	API_DTO_FIELD_DEFAULT(Float64, remaining_amount, ZH_WORDS_GETTER("registration-records.remaining_amount"));
	// 应退金额
	API_DTO_FIELD_DEFAULT(Float64, should_refund_amount, ZH_WORDS_GETTER("registration-records.should_refund_amount"));
	// 实际退款金额
	API_DTO_FIELD_DEFAULT(Float64, refund_amount, ZH_WORDS_GETTER("registration-records.refund_amount"));
	// 退款课次
	API_DTO_FIELD_DEFAULT(Int32, refund_lesson_count, ZH_WORDS_GETTER("registration-records.refund_lesson_count"));
	// 已退课次
	API_DTO_FIELD_DEFAULT(Int32, count_lesson_refund, ZH_WORDS_GETTER("registration-records.count_lesson_refund"));
	// 课时单价
	API_DTO_FIELD_DEFAULT(Float64, unit_price, ZH_WORDS_GETTER("registration-records.unit_price"));
	// 退款备注
	API_DTO_FIELD_DEFAULT(String, refund_remark, ZH_WORDS_GETTER("registration-records.refund_remark"));
	// 退款状态
	API_DTO_FIELD_DEFAULT(String, refund_state, ZH_WORDS_GETTER("registration-records.refund_state"));
	// 所属校区名称
	API_DTO_FIELD_DEFAULT(String, school_name, ZH_WORDS_GETTER("registration-records.school_name"));
	// 计划收款
	API_DTO_FIELD_DEFAULT(Float64, plan_receipt, ZH_WORDS_GETTER("registration-records.plan_receipt"));
	// 实际收款
	API_DTO_FIELD_DEFAULT(Float64, actual_receipt, ZH_WORDS_GETTER("registration-records.actual_receipt"));
	*/
};

// 报名记录分页DTO
class RegistrationRecordPageDTO : public PageDTO<RegistrationRecordDTO::Wrapper>
{
	DTO_INIT(RegistrationRecordPageDTO, PageDTO<RegistrationRecordDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_REGISTRATIONDTO_H_