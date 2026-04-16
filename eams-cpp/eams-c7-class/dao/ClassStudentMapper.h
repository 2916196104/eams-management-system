#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _CLASS_STUDENT_MAPPER_
#define _CLASS_STUDENT_MAPPER_

#include "Mapper.h"
#include "../domain/do/StudentDO.h"
#include "../domain/do/StudentCourseDO.h"

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;

/**
 * 班级学员列表字段匹配映射 (返回智能指针 StudentDO)
 */
class ClassStudentListMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<StudentDO>();
        data->setId(resultSet->getInt64(1));
        data->setName(String(resultSet->getString(2).c_str()));
        data->setGender(resultSet->getInt(3));
        data->setBirthday(String(resultSet->getString(4).c_str()));
        data->setHeadImg(String(resultSet->getString(5).c_str()));
        data->setStage(resultSet->getInt(6));
        data->setJoinDate(String(resultSet->getString(7).c_str()));
        return data;
    }
};

/**
 * 班级学员详情字段匹配映射 (返回智能指针 StudentDO)
 */
class PtrStudentMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<StudentDO>();
        data->setId(resultSet->getInt64(1));
        data->setName(String(resultSet->getString(2).c_str()));
        data->setGender(resultSet->getInt(3));
        data->setBirthday(String(resultSet->getString(4).c_str()));
        data->setHeadImg(String(resultSet->getString(5).c_str()));
        data->setStage(resultSet->getInt(6));
        data->setRemark(String(resultSet->getString(7).c_str()));
        data->setJoinDate(String(resultSet->getString(8).c_str()));
        data->setAddTime(String(resultSet->getString(9).c_str()));
        data->setCounselor(resultSet->getInt64(10));
        data->setGradeId(resultSet->getInt(11));
        data->setCredit(resultSet->getInt(12));
        return data;
    }
};

/**
 * 学员课程列表字段匹配映射 (返回智能指针 StudentCourseDO)
 */
class StudentCourseListMapper : public Mapper<PtrStudentCourseDO>
{
public:
    PtrStudentCourseDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<StudentCourseDO>();
        data->setId(resultSet->getInt64(1));
        data->setStudentId(resultSet->getInt64(2));
        data->setCourseId(resultSet->getInt64(3));
        data->setSubjectId(resultSet->getInt64(4));
        data->setCountLessonTotal(resultSet->getInt(5));
        data->setCountLessonComplete(resultSet->getInt(6));
        data->setCountLessonRefund(resultSet->getInt(7));
        data->setStartDate(String(resultSet->getString(8).c_str()));
        data->setExpireDate(String(resultSet->getString(9).c_str()));
        data->setAddTime(String(resultSet->getString(10).c_str()));
        data->setRemark(String(resultSet->getString(11).c_str()));
        data->setPriority(resultSet->getInt(12));
        data->setCourseName(String(resultSet->getString(13).c_str()));
        data->setSubjectName(String(resultSet->getString(14).c_str()));
        return data;
    }
};

/**
 * 字符串结果映射
 */
class StringMapper : public Mapper<String>
{
public:
    String mapper(ResultSet* resultSet) const override
    {
        return String(resultSet->getString(1).c_str());
    }
};

#endif // !_CLASS_STUDENT_MAPPER_