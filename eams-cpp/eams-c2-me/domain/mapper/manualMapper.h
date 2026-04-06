#pragma once
#include "Mapper.h"
#include "domain/do/manualDO.h"


/**
* 数据映射器
* 功能：将数据库查询结果映射为ManualDO对象
*/
class ListMapper : public Mapper<ManualDO>
{
public:
	/**
	* 映射方法
	* @param resultSet 数据库结果集指针
	* @return 映射后的ManualDO对象
	*/
	ManualDO mapper(ResultSet* resultSet) const override
	{
		ManualDO data;
		// 按列索引读取数据
		// 索引从1开始（JDBC标准）
		data.setId(resultSet->getInt(1)); // 第1列：id
		data.setTitle(resultSet->getString(2));
		data.setAddTime(resultSet->getString(3));
		data.setEditTime(resultSet->getString(4));
		return data;
	}
};

/**
* 数据映射器 - 返回智能指针版本
* 功能：将数据库查询结果映射为PtrManualDO对象（智能指针）
*/
class PtrDetailMapper : public Mapper<PtrManualDO>
{
public:
	PtrManualDO mapper(ResultSet* resultSet) const override
	{
		// 使用make_shared创建智能指针
		auto data = std::make_shared<ManualDO>();
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





