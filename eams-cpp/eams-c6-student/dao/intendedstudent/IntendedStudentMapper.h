#pragma once

#ifndef _INTENDEDSTUDENT_MAPPER_
#define _INTENDEDSTUDENT_MAPPER_

#include "Mapper.h"
#include "../../domain/do/student/ClassGradeDO.h"
#include "../../domain/do/student/OrgDO.h"
#include "../../domain/do/student/StaffDO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/do/student/UserDO.h"

inline std::string getSafeString(ResultSet* rs, int idx) {
	return rs->isNull(idx) ? "" : std::string(rs->getString(idx));
}

struct StudentDetail
{
	ExcelStudentDO student;
	ExcelUserDO user;
	OrgDO org;
	ClassGradeDO classGrade;
	ExcelStaffDO staff;
};
typedef std::shared_ptr<StudentDetail> PtrStudentDetail;

class IntendedExportMapper : public Mapper<StudentDetail> {
	StudentDetail mapper(ResultSet* resultSet) const override {
		StudentDetail data;

		// 第1-3列：student表（id, name, gender）
		data.student.setId(resultSet->getString(1));
		data.student.setName(resultSet->getString(2));
		data.student.setGender(resultSet->getInt(3));

		// 第4-5列：user表（mobile, name）
		// 注意：可能为NULL，getString返回空串
		data.user.setMobile(getSafeString(resultSet, 4));
		data.user.setName(getSafeString(resultSet, 5));

		// 第6列：student表（family_rel）
		data.student.setFamilyRel(resultSet->getInt(6));

		// 第7列：org表（school_name）
		data.org.setName(getSafeString(resultSet, 7));

		// 第8列：class_grade表（grade_name）
		data.classGrade.setName(getSafeString(resultSet, 8));

		// 第9列：student表（birthday）
		data.student.setBirthday(getSafeString(resultSet, 9));

		// 第10列：staff表（counselor_name）
		data.staff.setName(getSafeString(resultSet, 10));

		return data;
	}
};

class PtrIntendedExportMapper : public Mapper<PtrStudentDetail>
{
public:
	PtrStudentDetail mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<StudentDetail>();
		// 第1-3列：student表（id, name, gender）
		data->student.setId(resultSet->getString(1));
		data->student.setName(resultSet->getString(2));
		data->student.setGender(resultSet->getInt(3));

		// 第4-5列：user表（mobile, name）
		data->user.setMobile(getSafeString(resultSet, 4));
		data->user.setName(getSafeString(resultSet, 5));

		// 第6列：student表（family_rel）
		data->student.setFamilyRel(resultSet->getInt(6));

		// 第7列：org表（school_name）
		data->org.setName(getSafeString(resultSet, 7));

		// 第8列：class_grade表（grade_name）
		data->classGrade.setName(getSafeString(resultSet, 8));

		// 第9列：student表（birthday）
		data->student.setBirthday(getSafeString(resultSet, 9));

		// 第10列：staff表（counselor_name）
		data->staff.setName(getSafeString(resultSet, 10));

		return data;
	}
};

#endif