#pragma once
#ifndef _GRADE_MAPPER_H_
#define _GRADE_MAPPER_H_

#include "Mapper.h"
#include "domain/do/Grade/GradeDO.h"

/**
 * 成绩管理联查结果字段映射
 * 联查 SQL 字段顺序：
 *   gr.id, g.title, gr.score, s.id, s.name
 * 其中 gr=grade_record, g=grade, s=student
 */
class PtrGradeManageMapper : public Mapper<PtrGradeDO>
{
public:
	PtrGradeDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<GradeDO>();

		// grade.title -> 考核项
		data->setTitle(resultSet->getString(2));

		// grade_record 字段
		data->setRecordId(resultSet->getInt64(1));  // gr.id
		data->setScore(resultSet->getInt(3));       // gr.score

		// 关联 student（取 name）
		auto student = std::make_shared<StudentDO>();
		student->setName(resultSet->getString(4)); // s.name
		data->setStudent(student);

		return data;
	}
};

class GradeManageMapper : public Mapper<GradeDO>
{
public:
	GradeDO mapper(ResultSet* resultSet) const override
	{
		GradeDO data;

		// grade.title -> 考核项
		data.setTitle(resultSet->getString(2));

		// grade_record 字段
		data.setRecordId(resultSet->getInt64(1));  // gr.id
		data.setScore(resultSet->getInt(3));       // gr.score

		// 关联 student（取 name）
		auto student = std::make_shared<StudentDO>();
		student->setName(resultSet->getString(4)); // s.name
		data.setStudent(student);

		return data;
	}
};

#endif // !_GRADE_MAPPER_H_
