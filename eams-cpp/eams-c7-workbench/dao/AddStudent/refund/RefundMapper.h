#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/16 15:47:39

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
#ifndef _REFUNDMAPPER_H_
#define _REFUNDMAPPER_H_
#include "Mapper.h"
#include "domain/do/AddStudent/refund/RefundDO.h"

class RefundViewMapper : public Mapper<PtrRefundViewDO>
{
public:
	PtrRefundViewDO mapper(ResultSet* resultSet) const override
	{
		PtrRefundViewDO file = std::make_shared<RefundViewDO>();
		// Ó³Éä»ù´¡×Ö¶Î
		file->setId(resultSet->getString("id"));
		file->setStudentId(resultSet->getString("student_id"));
		file->setStudentCourseId(resultSet->getString("student_course_id"));
		file->setOperatorId(resultSet->getString("operator"));
		file->setRefundAmount(resultSet->getDouble("refund_amount"));
		file->setRefundLessonCount(resultSet->getInt("refund_lesson_count"));
		file->setApplyTime(resultSet->getString("apply_time"));
		file->setRemark(resultSet->getString("remark"));
		file->setDoneTime(resultSet->getString("done_time"));
		file->setTypeNum(resultSet->getString("type_num"));
		file->setVerifyState(resultSet->getString("verify_state"));
		file->setVerifyTime(resultSet->getString("verify_time"));
		file->setVerifyStaff(resultSet->getString("verify_staff"));
		// Ó³Éä¹ØÁª×Ö¶Î(ÊÓÍ¼DOÌØÓÐ)
		file->setStudentName(resultSet->getString("student_name"));
		file->setCourseName(resultSet->getString("course_name"));
		file->setOperatorName(resultSet->getString("operator_name"));
		return file;
	}
};

#endif // !_REFUNDMAPPER_H_