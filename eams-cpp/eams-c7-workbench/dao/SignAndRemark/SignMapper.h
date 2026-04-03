#pragma once
#ifndef _SIGNMAPPER_H_
#define _SIGNMAPPER_H_

#include "Mapper.h"
#include "domain/do/SignAndRemark/SignDO.h"

class SignMapper : public Mapper<PtrSignViewDO>
{
public:
	PtrSignViewDO mapper(ResultSet* resultSet) const override
	{
		PtrSignViewDO sign = std::make_shared<SignViewDO>();
		sign->setId(resultSet->getInt64("lesson_student_id")); // BIGINT UNSIGNED
		sign->setSign(std::to_string(resultSet->getInt("sign_state"))); // TINYINT ×ªÎª×Ö·û´®
		sign->setStu_id(resultSet->getInt64("student_id")); // BIGINT
		sign->setDate(resultSet->getString("sign_time")); // DATETIME
		sign->setStu_name(resultSet->getString("student_name")); // VARCHAR
		return sign;
	}
};

#endif