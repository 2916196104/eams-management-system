#pragma once
#ifndef _COMMON_MAPPER_
#define _COMMON_MAPPER_

#include "Mapper.h"
#include "../../domain/do/student/StudentDO.h"
// 班级列表字段匹配映射
class getClassListMapper : public Mapper<getClassListDO>
{
public:
	getClassListDO mapper(ResultSet* resultSet) const override
	{
		getClassListDO data;
		data.setId(resultSet->getString(1));
		data.setClassName(resultSet->getString(2));
		data.setSubject(resultSet->getString(3));
		data.setClassroom(resultSet->getString(4));
		data.setStudentCount(resultSet->getInt(5));
		data.setMaxStudentCount(resultSet->getInt(6));
		return data;
	}
};

// 班级列表字段匹配映射 - 创建智能指针对象
class PtrgetClassListMapper : public Mapper<PtrgetClassListDO>
{
public:
	PtrgetClassListDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<getClassListDO>();
		data->setId(resultSet->getString(1));
		data->setClassName(resultSet->getString(2));
		data->setSubject(resultSet->getString(3));
		data->setClassroom(resultSet->getString(4));
		data->setStudentCount(resultSet->getInt(5));
		data->setMaxStudentCount(resultSet->getInt(6));
		return data;
	}
};

// 课程统计字段匹配映射
class getCourseStatisticsMapper : public Mapper<getCourseStatisticsDO>
{
public:
	getCourseStatisticsDO mapper(ResultSet* resultSet) const override
	{
		getCourseStatisticsDO data;
		data.setCourse(resultSet->getString(1));
		data.setTotalHours(resultSet->getInt(2));
		data.setRemainingHours(resultSet->getInt(3));
		data.setAttendedHours(resultSet->getInt(4));
		data.setExpireDate(resultSet->getString(5));
		data.setCancelPriority(resultSet->getInt(6));
		return data;
	}
};

//课程统计字段匹配映射 - 创建智能指针对象
class PtrgetCourseStatisticsMapper : public Mapper<PtrgetCourseStatisticsDO>
{
public:
	PtrgetCourseStatisticsDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<getCourseStatisticsDO>();
		data->setCourse(resultSet->getString(1));
		data->setTotalHours(resultSet->getInt(2));
		data->setRemainingHours(resultSet->getInt(3));
		data->setAttendedHours(resultSet->getInt(4));
		data->setExpireDate(resultSet->getString(5));
		data->setCancelPriority(resultSet->getInt(6));
		return data;
	}
};

// 加入班级字段匹配映射
class JoinclassMapper : public Mapper<JoinclassDO>
{
public:
	JoinclassDO mapper(ResultSet* resultSet) const override
	{
		JoinclassDO data;
		data.setClassName(resultSet->getString(1));
		data.setSchool(resultSet->getString(2));
		return data;
	}
};

// 加入班级字段匹配映射 - 创建智能指针对象

class PtrJoinclassMapper : public Mapper<PtrJoinclassDO>
{
public:
	PtrJoinclassDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<JoinclassDO>();
		data->setClassName(resultSet->getString(1));
		data->setSchool(resultSet->getString(2));
		return data;
	}
};
//student_course数据表字段匹配映射
class PtrStudentCourseMapper : public Mapper<PtrStudentCourseDO> {
public:
	PtrStudentCourseDO mapper(ResultSet* resultSet) const override {
		auto data = std::make_shared<StudentCourseDO>();
		data->setStudentId(resultSet->getInt(1));
		data->setCourseId(resultSet->getInt(2));
		data->setSubjectId(resultSet->getInt(3));
	}
};
#endif 
