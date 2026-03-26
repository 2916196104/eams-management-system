#pragma once

#ifndef _STUDENTMAPPER_H_
#define _STUDENTMAPPER_H_

#include "Mapper.h"
#include "domain/do/Student/StudentDO.h"

//定义mapper方便StudentDAO使用
class StudentMapper : public Mapper<PtrStudentDO>
{
public:
	PtrStudentDO mapper(ResultSet* resultSet) const override
	{
		PtrStudentDO stuDO = make_shared<StudentDO>();
		// 只映射接口需要的字段 ：数据库字段名 → DO 的 set 方法
		stuDO->setId(resultSet->getString("id"));
		stuDO->setName(resultSet->getString("name"));
		stuDO->setGender(resultSet->getInt("gender"));
		stuDO->setStage(resultSet->getInt("stage"));
		stuDO->setBirthday(resultSet->getString("birthday"));
		stuDO->setHeadImg(resultSet->getString("head_img"));
		stuDO->setCredit(resultSet->getInt("credit"));
		return stuDO;
	}
};


#endif 