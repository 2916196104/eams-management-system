#pragma once
#ifndef _STUDENT_COURSE_MAPPER_
#define _STUDENT_COURSE_MAPPER_
#include "Mapper.h"
#include "../../domain/do/StudentRecord/student_course/student_coursedo.h"
#include "../../domain/do/StudentRecord/view/student_courseviewdo.h"
/**
 * 将查询CourseProgress结果映射成DO对象
 */
class CourseProgressMapper : public Mapper<CourseProgressViewDO>
{
public:
	CourseProgressViewDO mapper(ResultSet* resultSet) const override
	{
		CourseProgressViewDO data;
		if (resultSet && !resultSet->isAfterLast())
		{
			
			data.setCourseName(resultSet->getString("name"));
			data.setCourseSum(resultSet->getInt("count_lesson_total"));
			data.setCourseStatus(to_string(resultSet->getInt("state")));
			data.setFinishedSum(resultSet->getInt("count_lesson_complete"));
			data.setUnfinishedSum(data.getCourseSum() - data.getFinishedSum());
		}
		
		return data;
	}
};

/**
 * 将查询CourseProgress结果映射成DO对象
 */
class PtrCourseProgressMapper : public Mapper<PtrCourseProgressViewDO>
{
public:
	PtrCourseProgressViewDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CourseProgressViewDO>();
		if (resultSet && !resultSet->isAfterLast())
		{
			data->setCourseName(resultSet->getString("name"));
			data->setCourseSum(resultSet->getInt("count_lesson_total"));
			data->setCourseStatus(to_string(resultSet->getInt("state")));
			data->setFinishedSum(resultSet->getInt("count_lesson_complete"));
			data->setUnfinishedSum(data->getCourseSum() - data->getFinishedSum());
		}
		return data;
	}
};

/**
 * 将查询StudentSignUp结果映射成DO对象
 */
class StudentSighnUPMapper : public Mapper<StudentSignUpViewDO>
{
public:
	StudentSignUpViewDO mapper(ResultSet* resultSet) const override
	{
		StudentSignUpViewDO data;
		if (resultSet && !resultSet->isAfterLast())
		{
			data.setCourseName(resultSet->getString("name"));
			data.setBuyCourseSum(resultSet->getInt("count_lesson_total"));
			data.setSignUpTime(resultSet->getString("add_time"));
			data.setPayAmount(resultSet->getDouble("paid_amount"));
		}

		return data;
	}
};

/**
 * 将查询StudentSignUp结果映射成DO对象
 */
class PtrStudentSighnUPMapper : public Mapper<PtrStudentSignUpViewDO>
{
public:
	PtrStudentSignUpViewDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<StudentSignUpViewDO>();
		if (resultSet && !resultSet->isAfterLast())
		{
			data->setCourseName(resultSet->getString("name"));
			data->setBuyCourseSum(resultSet->getInt("count_lesson_total"));
			data->setSignUpTime(resultSet->getString("add_time"));
			data->setPayAmount(resultSet->getDouble("paid_amount"));
		}
		return data;
	}
};

/**
 * 将查询CourseRecord结果映射成DO对象
 */
class CourseRecordMapper : public Mapper<CourseRecordViewDO>
{
public:
	CourseRecordViewDO mapper(ResultSet* resultSet) const override
	{
		CourseRecordViewDO data;
		if (resultSet && !resultSet->isAfterLast())
		{
			data.setCourseName(resultSet->getString("name"));
			data.setCourseStatus(to_string(resultSet->getInt("state")));
			data.setConsumeCourseNum(resultSet->getInt("count_lesson_complete"));
			data.setCourseBalance(resultSet->getInt("count_lesson_total") - resultSet->getInt("count_lesson_complete"));
		}

		return data;
	}
};

/**
 * 将查询CourseProgress结果映射成DO对象
 */
class PtrCourseRecordMapper : public Mapper<PtrCourseRecordViewDO>
{
public:
	PtrCourseRecordViewDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CourseRecordViewDO>();
		if (resultSet && !resultSet->isAfterLast())
		{
			data->setCourseName(resultSet->getString("name"));
			data->setCourseStatus(to_string(resultSet->getInt("state")));
			data->setConsumeCourseNum(resultSet->getInt("count_lesson_complete"));
			data->setCourseBalance(resultSet->getInt("count_lesson_total") - resultSet->getInt("count_lesson_complete"));
		}
		return data;
	}
};

#endif // !1
