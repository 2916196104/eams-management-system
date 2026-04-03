#pragma once
#ifndef _REMARKMAPPER_H_
#define _REMARKMAPPER_H_

#include "Mapper.h"
#include "domain/do/SignAndRemark/RemarkDO.h"

class RemarkMapper : public Mapper<PtrRemarkViewDO>
{
public:
	PtrRemarkViewDO mapper(ResultSet* resultSet) const override
	{
		PtrRemarkViewDO remark = std::make_shared<RemarkViewDO>();
		remark->setId(resultSet->getInt64("lesson_student_id")); // BIGINT UNSIGNED
		remark->setRemark(resultSet->getString("evaluation")); // VARCHAR(255)
		//remark->setStu_id(resultSet->getInt64("student_id")); // BIGINT
		remark->setScore(resultSet->getInt("score")); // TINYINT
		remark->setStu_name(resultSet->getString("student_name")); // VARCHAR
		remark->setRemark_time(resultSet->getString("evaluate_time")); // DATETIME
		remark->setTeacher_name(resultSet->getString("teacher_name")); // ¼ÙÉè teacher_name À´×Ô JOIN
		return remark;
	}
};

#endif