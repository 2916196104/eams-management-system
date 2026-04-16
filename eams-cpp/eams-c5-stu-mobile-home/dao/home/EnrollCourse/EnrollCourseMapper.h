#pragma once

#ifndef _SAMPLE_MAPPER_
#define _SAMPLE_MAPPER_
#include "Mapper.h"
#include "../../../domain/do/home/EnrollCourse/EnrollCourseDO.h"

class EnrollCourseMapper : public Mapper<EnrollCourseDO>
{
public:
	EnrollCourseDO mapper(ResultSet* resultSet) const override
	{
		EnrollCourseDO data;
        data.setId(resultSet->getUInt64(1)); 

        data.setStudentId(resultSet->getUInt64(2));
        data.setCourseId(resultSet->getUInt64(3));
        data.setSubjectId(resultSet->getUInt64(4));

        data.setStartDate(resultSet->getString(5));
        data.setExpireDate(resultSet->getString(6));
        data.setRemark(resultSet->getString(7));

        data.setCountLessonTotal(resultSet->getInt(8));
        data.setCountLessonComplete(resultSet->getInt(9));
        data.setCountLessonRefund(resultSet->getInt(10));

        data.setCourseAmount(resultSet->getDouble(11));
        data.setDiscountAmount(resultSet->getDouble (12));
        data.setAmount(resultSet->getDouble(13));
        data.setPaidAmount(resultSet->getDouble(14));
        data.setPayOff(resultSet->getInt(15));
        data.setOperater(resultSet->getUInt64(16));
        data.setCreator(resultSet->getUInt64(17));
        data.setAddTime(resultSet->getString(18));
        data.setEditor(resultSet->getUInt64(19));
        data.setEditTime(resultSet->getString(20));

   
        data.setDeleted(resultSet->getInt(21));
        data.setVerifyState(resultSet->getInt(22));
        data.setWarningTimes(resultSet->getInt(23));
        data.setPriority(resultSet->getInt(24));
        data.setUnitPrice(resultSet->getDouble(25));
        data.setFromTrial(resultSet->getInt(26));

       
        
        data.setOrgId(resultSet->getUInt64(27));

        data.setCourseName(resultSet->getString(28));
        data.setSubjectName(resultSet->getString(29));
		return data;
	}
};



#endif