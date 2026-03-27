#pragma once
#ifndef _COURSE_MAPPER_H_
#define _COURSE_MAPPER_H_

#include "Mapper.h"
#include "domain/do/course/CourseDO.h"

class CourseMapper : public Mapper<CourseDO>
{
public:
	CourseDO mapper(ResultSet* resultSet) const override
	{
		CourseDO data;

		if (!resultSet->isNull("id")) data.setId(resultSet->getUInt64("id"));
		if (!resultSet->isNull("subject_id")) data.setSubjectId(resultSet->getInt64("subject_id"));
		if (!resultSet->isNull("name")) data.setName(resultSet->getString("name"));
		if (!resultSet->isNull("state")) data.setState(resultSet->getInt("state"));
		if (!resultSet->isNull("info")) data.setInfo(resultSet->getString("info"));
		if (!resultSet->isNull("creator")) data.setCreator(resultSet->getInt64("creator"));
		if (!resultSet->isNull("editor")) data.setEditor(resultSet->getInt64("editor"));
		if (!resultSet->isNull("add_time")) data.setAddTime(resultSet->getString("add_time"));
		if (!resultSet->isNull("edit_time")) data.setEditTime(resultSet->getString("edit_time"));
		if (!resultSet->isNull("expire_months")) data.setExpireMonths(resultSet->getUInt("expire_months"));
		if (!resultSet->isNull("unit_price")) data.setUnitPrice(resultSet->getDouble("unit_price"));
		if (!resultSet->isNull("price")) data.setPrice(resultSet->getDouble("price"));
		if (!resultSet->isNull("unit_name")) data.setUnitName(resultSet->getString("unit_name"));
		if (!resultSet->isNull("discount")) data.setDiscount(resultSet->getDouble("discount"));
		if (!resultSet->isNull("lesson_count")) data.setLessonCount(resultSet->getUInt("lesson_count"));
		if (!resultSet->isNull("lesson_type")) data.setLessonType(resultSet->getInt("lesson_type"));
		if (!resultSet->isNull("description")) data.setDescription(resultSet->getString("description"));
		if (!resultSet->isNull("deleted")) data.setDeleted(resultSet->getBoolean("deleted"));
		if (!resultSet->isNull("bookable")) data.setBookable(resultSet->getBoolean("bookable"));
		if (!resultSet->isNull("for_sale")) data.setForSale(resultSet->getBoolean("for_sale"));
		if (!resultSet->isNull("recommend")) data.setRecommend(resultSet->getBoolean("recommend"));
		if (!resultSet->isNull("cover")) data.setCover(resultSet->getString("cover"));
		if (!resultSet->isNull("close_date")) data.setCloseDate(resultSet->getString("close_date"));
		if (!resultSet->isNull("teacher_info")) data.setTeacherInfo(resultSet->getString("teacher_info"));
		if (!resultSet->isNull("service_info")) data.setServiceInfo(resultSet->getString("service_info"));
		if (!resultSet->isNull("storage")) data.setStorage(resultSet->getInt("storage"));
		if (!resultSet->isNull("org_id")) data.setOrgId(resultSet->getInt64("org_id"));
		if (!resultSet->isNull("salary")) data.setSalary(resultSet->getDouble("salary"));
		if (!resultSet->isNull("grade_ids")) data.setGradeIds(resultSet->getString("grade_ids"));
		if (!resultSet->isNull("grade_names")) data.setGradeNames(resultSet->getString("grade_names"));

		return data;
	}
};

#endif // !_COURSE_MAPPER_H_
