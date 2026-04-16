#pragma once
#ifndef COMMENTRECORDMAPPER_H
#define COMMENTRECORDMAPPER_H
#include "Mapper.h"
#include "../../../domain/do/TeachEvaluationDO.h"

class CommentrecordMapper : public Mapper<CommentrecordViewDO>
{
public:
	CommentrecordViewDO mapper(ResultSet* resultSet) const override
	{
		CommentrecordViewDO data;
		data.setId(resultSet->getUInt64(1));
		data.setTeacherId(resultSet->getUInt64(2));
		data.setScore1(resultSet->getInt(3));
		data.setContent(resultSet->getString(4));
		data.setAddTime(resultSet->getString(5));
		data.setStudentId(resultSet->getUInt64(6));
		data.setAnonymity(resultSet->getInt(7));
		data.setStudentName(resultSet->getString(8));
	
		return data;
	}
};


class PtrCommentrecordMapper : public Mapper<PtrCommentrecordViewDO>
{
public:
	PtrCommentrecordViewDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CommentrecordViewDO>();
		data->setId(resultSet->getUInt64(1));
		
		data->setTeacherId(resultSet->getUInt64(2));
		data->setScore1(resultSet->getInt(3));
		
		data->setContent(resultSet->getString(4));
		data->setAddTime(resultSet->getString(5));
		data->setStudentId(resultSet->getUInt64(6));
		data->setAnonymity(resultSet->getInt(7));
		data->setStudentName(resultSet->getString(8));
		
		return data;
	}
};


#endif