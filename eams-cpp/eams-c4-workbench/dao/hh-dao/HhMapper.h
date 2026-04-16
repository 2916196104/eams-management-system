#pragma once
#ifndef _HH_MAPPER_
#define _HH_MAPPER_

#include "Mapper.h"
#include "../../domain/do/hh-do/HhDO.h"
#include "../../domain/do/ClassroomDO.h"


class HhStudentViewMapper1 : public Mapper<HhStudentViewDO> {
public:
	// 接口一的mapper，用于将数据库返回数据映射为HhStudentViewDO类型
	HhStudentViewDO mapper(ResultSet* resultSet) const override {
		HhStudentViewDO data;
		data.setId(resultSet->getInt(1));
		data.setName(resultSet->getString(2));
		data.setMobile(resultSet->getString(3));
		return data;
	}

};

class HhStudentViewMapper2 : public Mapper<PtrHhStudentViewDO> {
public:
	// 接口二的mapper，虽说他们都将数据映射为同一种类型，但是映射过程并不相同
	// 此时数据库会返回更多的数据，需要我们更多的处理
	PtrHhStudentViewDO mapper(ResultSet* resultSet) const override {
		PtrHhStudentViewDO data = std::make_shared<HhStudentViewDO>();
		data->setId(resultSet->getInt(1));
		data->setName(resultSet->getString(2));
		data->setMobile(resultSet->getString(3));
		data->setGender(resultSet->getInt(4));
		data->setAge(resultSet->getInt(5));
		data->setBirthday(resultSet->getString(6));
		data->setStage(resultSet->getInt(7));
		data->setRemark(resultSet->getString(8));

		return data;
	}
};

// 接口三的mapper，用于将数据库返回数据映射为HhCourseViewDO类型
class HhCourseViewMapper : public Mapper<HhCourseViewDO> {
public:
	HhCourseViewDO mapper(ResultSet* resultSet) const override {
		HhCourseViewDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setProgress(resultSet->getString(3));
		data.setDeadLine(resultSet->getString(4));
		data.setRestTimes(resultSet->getInt(5));
		return data;
	}
};

// 接口四的mapper，用于将数据库返回数据映射为ClassroomDO类型
class HhClassroomMapper : public Mapper<ClassroomDO> {
public:
	ClassroomDO mapper(ResultSet* resultSet) const override {
		ClassroomDO data;
		data.setId(resultSet->getInt(1));
		data.setName(resultSet->getString(2));
		data.setAddress(resultSet->getString(3));

		return data;
	}
};

#endif
