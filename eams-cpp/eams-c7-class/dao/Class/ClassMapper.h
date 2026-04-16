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
#ifndef _CLASS_MAPPER_
#define _CLASS_MAPPER_

#include "../eams-c7-class/domain/do/ClassDO.h"
#include "Mapper.h"


/**
 * 班级表字段匹配映射 (返回对象)
 */
class ClassMapper : public Mapper<ClassDO>
{
public:
    ClassDO mapper(ResultSet* resultSet) const override
    {
        ClassDO data;
        // 这里的序号(1,2,3...)对应SELECT语句中字段的顺序
        data.setId(resultSet->getInt64(1)); // id
        data.setName(resultSet->getString(2)); // name
        data.setCourseId(resultSet->getInt64(3)); // course_id
        data.setClassroomId(resultSet->getInt64(4)); // classroom_id
        data.setCreator(resultSet->getInt64(5)); // creator
        data.setEditor(resultSet->getInt64(6)); // editor
        data.setAddTime(resultSet->getString(7)); // add_time
        data.setEditTime(resultSet->getString(8)); // edit_time
        data.setDeleted(resultSet->getBoolean(9)); // deleted
        data.setTeacherId(resultSet->getInt64(10)); // teacher_id
        data.setRemark(resultSet->getString(11)); // remark
        data.setBeOver(resultSet->getBoolean(12)); // be_over
        data.setOverTime(resultSet->getString(13)); // over_time
        data.setOverOperator(resultSet->getInt64(14)); // over_operator
        data.setStartDate(resultSet->getString(15)); // start_date
        data.setEndDate(resultSet->getString(16)); // end_date
        data.setPlannedStudentCount(resultSet->getInt(17)); // planned_student_count
        data.setPlannedLessonCount(resultSet->getInt(18)); // planned_lesson_count
        data.setSchoolId(resultSet->getInt64(19)); // school_id
        data.setOrgId(resultSet->getInt64(20)); // org_id
        data.setGradeId(resultSet->getInt(21)); // grade_id
        return data;
    }
};

/**
 * 班级表字段匹配映射 (返回智能指针)
 */
class PtrClassMapper : public Mapper<PtrClassDO>
{
public:
    PtrClassDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<ClassDO>();
        // 映射逻辑与上方一致，但操作的是指针 data->
        data->setId(resultSet->getInt64(1));
        data->setName(resultSet->getString(2));
        data->setCourseId(resultSet->getInt64(3));
        data->setClassroomId(resultSet->getInt64(4));
        data->setCreator(resultSet->getInt64(5));
        data->setEditor(resultSet->getInt64(6));
        data->setAddTime(resultSet->getString(7));
        data->setEditTime(resultSet->getString(8));
        data->setDeleted(resultSet->getBoolean(9));
        data->setTeacherId(resultSet->getInt64(10));
        data->setRemark(resultSet->getString(11));
        data->setBeOver(resultSet->getBoolean(12));
        data->setOverTime(resultSet->getString(13));
        data->setOverOperator(resultSet->getInt64(14));
        data->setStartDate(resultSet->getString(15));
        data->setEndDate(resultSet->getString(16));
        data->setPlannedStudentCount(resultSet->getInt(17));
        data->setPlannedLessonCount(resultSet->getInt(18));
        data->setSchoolId(resultSet->getInt64(19));
        data->setOrgId(resultSet->getInt64(20));
        data->setGradeId(resultSet->getInt(21));

        return data;
    }
};
/**
 * 班级视图对象字段匹配映射
 */
class ClassViewMapper : public Mapper<ClassViewDO>
{
public:
    ClassViewDO mapper(ResultSet* resultSet) const override
    {
        ClassViewDO data;

        data.setId(resultSet->getInt64(1));
        data.setName(resultSet->getString(2));
        data.setCourseId(resultSet->getInt64(3));
        data.setClassroomId(resultSet->getInt64(4));
        data.setCreator(resultSet->getInt64(5));
        data.setEditor(resultSet->getInt64(6));
        data.setAddTime(resultSet->getString(7));
        data.setEditTime(resultSet->getString(8));
        data.setDeleted(resultSet->getBoolean(9));
        data.setTeacherId(resultSet->getInt64(10));
        data.setRemark(resultSet->getString(11));
        data.setBeOver(resultSet->getBoolean(12));
        data.setOverTime(resultSet->getString(13));
        data.setOverOperator(resultSet->getInt64(14));
        data.setStartDate(resultSet->getString(15));
        data.setEndDate(resultSet->getString(16));
        data.setPlannedStudentCount(resultSet->getInt(17));
        data.setPlannedLessonCount(resultSet->getInt(18));
        data.setSchoolId(resultSet->getInt64(19));
        data.setOrgId(resultSet->getInt64(20));
        data.setGradeId(resultSet->getInt(21));
        // 第 22, 23 个字段来自  JOIN
        data.setTeacherName(resultSet->getString(22));
        data.setCourseName(resultSet->getString(23));
        return data;
    }
};
#endif // !_CLASS_MAPPER_