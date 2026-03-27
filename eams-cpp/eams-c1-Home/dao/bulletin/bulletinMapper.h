#pragma once
#ifndef _BULLETIN_MAPPER_
#define _BULLETIN_MAPPER_

#include "Mapper.h"
#include "../../domain/do/bulletin/bulletinDO.h"

/**
 * 公告表字段匹配映射
 */
class BulletinMapper : public Mapper<bulletinDO>
{
public:
	bulletinDO mapper(ResultSet* resultSet) const override
	{
		bulletinDO data;
		data.setId(resultSet->getUInt64(1));         // id
		data.setTitle(resultSet->getString(2));      // title
		data.setCover(resultSet->getString(3));      // cover
		data.setContent(resultSet->getString(4));     // content
		data.setType(resultSet->getInt(5));          // type
		data.setState(resultSet->getInt(6));         // state
		data.setSortNum(resultSet->getInt(7));       // sort_num
		data.setAddTime(resultSet->getString(8));    // add_time
		data.setEditTime(resultSet->getString(9));   // edit_time
		data.setCreator(resultSet->getInt64(10));    // creator
		data.setEditor(resultSet->getInt64(11));     // editor
		data.setDeleted(resultSet->getInt(12));      // deleted
		return data;
	}
};

/**
 * 公告表字段匹配映射-创建智能指针对象
 */
class PtrBulletinMapper : public Mapper<ptrbulletinDO>
{
public:
	ptrbulletinDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<bulletinDO>();
		data->setId(resultSet->getUInt64(1));         // id
		data->setTitle(resultSet->getString(2));      // title
		data->setCover(resultSet->getString(3));      // cover
		data->setContent(resultSet->getString(4));     // content
		data->setType(resultSet->getInt(5));          // type
		data->setState(resultSet->getInt(6));         // state
		data->setSortNum(resultSet->getInt(7));       // sort_num
		data->setAddTime(resultSet->getString(8));    // add_time
		data->setEditTime(resultSet->getString(9));   // edit_time
		data->setCreator(resultSet->getInt64(10));    // creator
		data->setEditor(resultSet->getInt64(11));     // editor
		data->setDeleted(resultSet->getInt(12));      // deleted
		return data;
	}
};



/**
 * 未读数映射
 */
class RedMapper : public Mapper<redDO>
{
public:
	redDO mapper(ResultSet* resultSet) const override
	{
		redDO data;
		data.setHomeworkCount(resultSet->getInt(1));   // homework_count
		data.setEvaluateCount(resultSet->getInt(2));   // evaluate_count
		data.setGradeCount(resultSet->getInt(3));      // grade_count
		return data;
	}
};

/**
 * 未读数映射-智能指针版本
 */
class PtrRedMapper : public Mapper<ptrRedDO>
{
public:
	ptrRedDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<redDO>();
		data->setHomeworkCount(resultSet->getInt(1));   // homework_count
		data->setEvaluateCount(resultSet->getInt(2));   // evaluate_count
		data->setGradeCount(resultSet->getInt(3));      // grade_count
		return data;
	}
};


#endif // !_BULLETIN_MAPPER_