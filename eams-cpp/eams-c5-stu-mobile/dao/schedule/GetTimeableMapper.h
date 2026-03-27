#pragma once
#ifndef _GETTIMEABLE_MAPPER_
#define _GETTIMEABLE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/schedule/GetTimeableDO.h"

// 核心：Mapper 映射所有字段，索引对应 SQL 列的位置（从1开始）
class GetTimeableMapper : public Mapper<GetTimeableDO>
{
public:
    GetTimeableDO mapper(ResultSet* resultSet) const override
    {
        GetTimeableDO data;
        // 映射顺序严格对齐 MYSQL_ADD_FIELD 顺序（和 SampleDO 一致）
        data.setId(resultSet->getInt(1));                // 第1列：id
        data.setTitle(resultSet->getString(2));          // 第2列：title
        data.setSn(resultSet->getString(3));             // 第3列：sn
        data.setDate(resultSet->getString(4));           // 第4列：date
        data.setStart_time(resultSet->getString(5));     // 第5列：start_time
        data.setEnd_time(resultSet->getString(6));       // 第6列：end_time
        data.setTeacher_id(resultSet->getInt(7));        // 第7列：teacher_id
        data.setSchedule_id(resultSet->getInt(8));       // 第8列：schedule_id
        data.setTeacherName(resultSet->getString(9));    // 第9列：teacher_name
        data.setSignState(resultSet->getInt(10));        // 第10列：sign_state
        return data;
    }
};

// 智能指针版 Mapper（和示例风格一致）
class PtrGetTimeableMapper : public Mapper<PtrGetTimeableDO>
{
public:
    PtrGetTimeableDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<GetTimeableDO>();
        // 同上面的映射逻辑
        data->setId(resultSet->getInt(1));
        data->setTitle(resultSet->getString(2));
        data->setSn(resultSet->getString(3));
        data->setDate(resultSet->getString(4));
        data->setStart_time(resultSet->getString(5));
        data->setEnd_time(resultSet->getString(6));
        data->setTeacher_id(resultSet->getInt(7));
        data->setSchedule_id(resultSet->getInt(8));
        data->setTeacherName(resultSet->getString(9));
        data->setSignState(resultSet->getInt(10));
        return data;
    }
};
/**
 * 示例表字段匹配映射
 */
//class GetTimeableMapper : public Mapper<GetTimeableDO>
//{
//public:
//	GetTimeableDO mapper(ResultSet* resultSet) const override
//	{
//		GetTimeableDO data;
//		data.setId(resultSet->getInt(1));
//		data.setDate(resultSet->getString(1));
//		return data;
//	}
//};
//
/////**
//// * 示例表字段匹配映射-创建智能指针对象
//// */
//class PtrGetTimeableMapper : public Mapper<PtrGetTimeableDO>
//{
//public:
//	PtrGetTimeableDO mapper(ResultSet* resultSet) const override
//	{
//		auto data = std::make_shared<GetTimeableDO>();
//		data->setId(resultSet->getInt(1));
//		return data;
//	}
//};

#endif // !_GETTIMEABLE_MAPPER_