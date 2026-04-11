#pragma once
#ifndef COURSE_MAPPER_
#define COURSE_MAPPER_

#include"Mapper.h"
#include"../../domain/do/CourseDO.h"
#include"../../domain/do/StudentDO.h"
#include"../../domain/do/StudentCourseDO.h"
#include"../../domain/do/ViewDO/EnrolledRecordDO.h"
class CourseMapper : public Mapper<CourseDO>
{
public:
	CourseDO mapper(ResultSet* resultSet)const override
	{
		CourseDO data;
		data.setId(resultSet->getString(1));
		data.setSubject_id(resultSet->getString(2));
		data.setName(resultSet->getString(3));
		data.setPrice(resultSet->getString(4));//DO为string类型，数据库为double类型，自动转换
		data.setDiscount(resultSet->getString(5));//DO为string类型，数据库为double类型，自动转换
		data.setLesson_count(resultSet->getInt(6));
		data.setLesson_type(resultSet->getInt(7));
		data.setExpire_months(resultSet->getInt(8));
		data.setUnit_price(resultSet->getString(9));
		return data;
	}
};

class PtrCourseMapper :public Mapper<PtrCourseDO>
{

public://id,subject_id,name,price,discount,lessson_count,lesson_type
	PtrCourseDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<CourseDO>();
		data->setId(resultSet->getString(1));
		data->setSubject_id(resultSet->getString(2));
		data->setName(resultSet->getString(3));
		data->setPrice(resultSet->getString(4));//DO为string类型，数据库为double类型，自动转换
		data->setDiscount(resultSet->getString(5));//DO为string类型，数据库为double类型，自动转换
		data->setLesson_count(resultSet->getInt(6));
		data->setLesson_type(resultSet->getInt(7));
		data->setExpire_months(resultSet->getInt(8));
		data->setUnit_price(resultSet->getString(9));
		return data;
	}
};
class StudentMapper : public Mapper<StudentDO>
{
public:
	StudentDO mapper(ResultSet* resultSet)const override
	{
		StudentDO data;
		data.setId(resultSet->getInt(1));
		data.setName(resultSet->getString(2));
		return data;
	}
};
class PtrStudentMapper :public Mapper<PtrStudentDO>
{
public:
	PtrStudentDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<StudentDO>();
		data->setId(resultSet->getInt(1));
		data->setName(resultSet->getString(2));
		return data;
	}
};
class StudentCourseMapper : public Mapper<StudentCourseDO>
{
public:
	StudentCourseDO mapper(ResultSet* resultSet)const override
	{
		StudentCourseDO data;
		data.setId(resultSet->getInt(1));
		data.setStudentId(resultSet->getInt(2));
		data.setCourseId(resultSet->getInt(3));
		data.setSubjectId(resultSet->getInt(4));
		data.setStartDate(resultSet->getString(5));
		data.setExpireDate(resultSet->getString(6));
		data.setRemark(resultSet->getString(7));
		data.setCountLessonTotal(resultSet->getInt(8));
		data.setCountLessonComplete(resultSet->getInt(9));
		data.setCountLessonRefund(resultSet->getInt(10));
		data.setCourseAmount(resultSet->getDouble(11));
		data.setDiscountAmount(resultSet->getDouble(12));
		data.setAmount(resultSet->getDouble(13));
		data.setPaidAmount(resultSet->getDouble(14));
		data.setCreator(resultSet->getInt(15));
		data.setAddTime(resultSet->getString(16));
		data.setDeleted(resultSet->getInt(17));
		return data;
		
	}
};
class PtrStudentCourseMapper : public Mapper<PtrStudentCourseDO>
{
public:
	PtrStudentCourseDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<StudentCourseDO>();
		data->setId(resultSet->getInt(1));
		data->setStudentId(resultSet->getInt(2));
		data->setCourseId(resultSet->getInt(3));
		data->setSubjectId(resultSet->getInt(4));
		data->setStartDate(resultSet->getString(5));
		data->setExpireDate(resultSet->getString(6));
		data->setRemark(resultSet->getString(7));
		data->setCountLessonTotal(resultSet->getInt(8));
		data->setCountLessonComplete(resultSet->getInt(9));
		data->setCountLessonRefund(resultSet->getInt(10));
		data->setCourseAmount(resultSet->getDouble(11));
		data->setDiscountAmount(resultSet->getDouble(12));
		data->setAmount(resultSet->getDouble(13));
		data->setPaidAmount(resultSet->getDouble(14));
		data->setCreator(resultSet->getInt(15));
		data->setAddTime(resultSet->getString(16));
		data->setDeleted(resultSet->getInt(17));
		return data;
		
	}
};
class EnrolledRecordMapper : public Mapper<EnrolledRecordDO>
{
	public:
	EnrolledRecordDO mapper(ResultSet* resultSet)const override
	{
		EnrolledRecordDO data;
		data.setStudentName(resultSet->getString(1));
		data.setCourseName(resultSet->getString(2));
		data.setStartDate(resultSet->getString(3));
		data.setExpireDate(resultSet->getString(4));
		data.setAmount(resultSet->getString(5));
		return data;
	}
};
class PtrEnrolledRecordMapper : public Mapper<std::shared_ptr<EnrolledRecordDO>>
{
public:
	PtrEnrolledRecordDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<EnrolledRecordDO>();
		data->setId(resultSet->getInt(1));
		data->setStudentName(resultSet->getString(2));
		data->setCourseName(resultSet->getString(3));
		data->setStartDate(resultSet->getString(4));
		data->setExpireDate(resultSet->getString(5));
		data->setAmount(resultSet->getString(6));
		return data;
	}
};
class EnrolledRecordDetailMapper : public Mapper<EnrolledRecordDetailDO>
{
public:
	EnrolledRecordDetailDO mapper(ResultSet* resultSet)const override
	{
		EnrolledRecordDetailDO data;
		data.setStudentName(resultSet->getString(1));
		data.setCourseName(resultSet->getString(2));
		data.setSubjectName(resultSet->getString(3));
		data.setStartDate(resultSet->getString(4));
		data.setExpireDate(resultSet->getString(5));
		data.setCourseAmount(resultSet->getString(6));
		data.setDiscountAmount(resultSet->getString(7));
		data.setPaidAmount(resultSet->getString(8));
		data.setOwedAmount(resultSet->getString(9));
		data.setSubmitTime(resultSet->getString(10));
		data.setRemark(resultSet->getString(11));
		data.setTotalLessons(resultSet->getInt(12));
		data.setCompletedLessons(resultSet->getInt(13));
		data.setRemainingLessons(resultSet->getInt(14));
		data.setRefundInfo(resultSet->getString(15));
		return data;
	}
};
class PtrEnrolledRecordDetailMapper : public Mapper<std::shared_ptr<EnrolledRecordDetailDO>>
{
public:
	PtrEnrolledRecordDetailDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<EnrolledRecordDetailDO>();
		data->setStudentName(resultSet->getString(1));
		data->setCourseName(resultSet->getString(2));
		data->setSubjectName(resultSet->getString(3));
		data->setStartDate(resultSet->getString(4));
		data->setExpireDate(resultSet->getString(5));
		data->setCourseAmount(resultSet->getString(6));
		data->setDiscountAmount(resultSet->getString(7));
		data->setPaidAmount(resultSet->getString(8));
		data->setOwedAmount(resultSet->getString(9));
		data->setSubmitTime(resultSet->getString(10));
		data->setRemark(resultSet->getString(11));
		data->setTotalLessons(resultSet->getInt(12));
		data->setCompletedLessons(resultSet->getInt(13));
		data->setRemainingLessons(resultSet->getInt(14));
		data->setRefundInfo(resultSet->getString(15));
		return data;
	}

};
#endif // !COURSE_MAPPER_
