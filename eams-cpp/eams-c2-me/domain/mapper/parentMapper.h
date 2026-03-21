#pragma once
#include "Mapper.h"
#include "domain/do/parentDO.h"
class ListMapper : public Mapper<ParentDO>
{
public:
	/**
	* 映射方法
	* @param resultSet 数据库结果集指针
	* @return 映射后的SampleDO对象
	*/
	ParentDO mapper(ResultSet* resultSet) const override
	{
		ParentDO data;
		// 按列索引读取数据
		// 索引从1开始（JDBC标准）
		data.setId(resultSet->getInt(1)); // 第1列：id
		data.setTitle(resultSet->getString(2));
		data.setAddTime(resultSet->getString(3)); 
		data.setEditTime(resultSet->getString(4));
		return data;
	}
};


class PtrDetailMapper : public Mapper<PtrParentDO>
{
public:
	PtrParentDO mapper(ResultSet* resultSet) const override
	{
		// 使用make_shared创建智能指针
		auto data = std::make_shared<ParentDO>();
		data->setId(resultSet->getInt(1)); // 第1列：id
		data->setTitle(resultSet->getString(2)); 
		data->setContent(resultSet->getString(3)); 
		data->setType(resultSet->getString(4));
		data->setCreator(resultSet->getInt(5));
		data->setAddTime(resultSet->getString(6));
		data->setDeleted(resultSet->getInt(7));
		data->setEditTime(resultSet->getString(8));
		data->setEditor(resultSet->getInt(9));
		data->setState(resultSet->getInt(10));
		data->setSortNum(resultSet->getInt(11));
		return data;
	}
};




