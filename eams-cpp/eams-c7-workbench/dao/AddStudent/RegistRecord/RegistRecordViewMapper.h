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
#ifndef _REGISTRECORDVIEWMAPPER_H_
#define _REGISTRECORDVIEWMAPPER_H_
#include "Mapper.h"
#include "domain/do/AddStudent/RegistRecord/RegistRecordViewDO.h"

class RegistRecordViewMapper : public Mapper<PtrRegistRecordViewDO>
{
public:
	PtrRegistRecordViewDO mapper(ResultSet* resultSet) const override
	{
		PtrRegistRecordViewDO file = std::make_shared<RegistRecordViewDO>();
		// 映射基础字段
		file->setId(resultSet->getInt("id"));
		file->setStudentName(resultSet->getString("student_name"));
		file->setCourseName(resultSet->getString("course_name"));
		file->setSubjectName(resultSet->getString("subject_name"));
		file->setStartDate(resultSet->getString("start_date"));
		file->setCourseAmount(resultSet->getDouble("course_amount"));
		file->setPaidAmount(resultSet->getDouble("paid_amount"));
		file->setDiscountAmount(resultSet->getDouble("discount_amount"));
		file->setExpireDate(resultSet->getString("expire_date"));
		file->setAddTime(resultSet->getString("add_time"));
		file->setRemark(resultSet->getString("remark"));
		file->setCountLessonTotal(resultSet->getInt("count_lesson_total"));
		file->setCountLessonComplete(resultSet->getInt("count_lesson_complete"));
		file->setRefundAmount(resultSet->getDouble("refund_amount"));
		file->setRemainingCount(resultSet->getInt("remaining_count"));
		file->setRefundLessonCount(resultSet->getInt("refund_lesson_count"));
		return file;
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<RegistRecordViewMapper> PtrRegistRecordViewMapper;


class RegistRecordPageViewMapper : public Mapper<PtrRegistRecordViewDO>
{
public:
	PtrRegistRecordViewDO mapper(ResultSet* resultSet) const override
	{
		PtrRegistRecordViewDO file = std::make_shared<RegistRecordViewDO>();
		// 映射基础字段
		file->setId(resultSet->getInt("id"));
		file->setStudentName(resultSet->getString("student_name"));
		file->setCourseName(resultSet->getString("course_name"));
		file->setStartDate(resultSet->getString("start_date"));
		file->setPaidAmount(resultSet->getDouble("paid_amount"));
		file->setExpireDate(resultSet->getString("expire_date"));

		return file;
	}
};

#endif // !_REGISTRECORDVIEWMAPPER_H_