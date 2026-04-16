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
#ifndef _CLASSMAPPER_H_
#define _CLASSMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/class/ClassDO.h"

/**
 * class列表字段匹配映射
 */
class ClassMapper : public Mapper<ClassDO>
{
public:
    ClassDO mapper(ResultSet* resultSet) const override
    {
        ClassDO data;

        // class 表字段
        data.setId(resultSet->getInt("id"));
        data.setName(resultSet->getString("name"));
        data.setCourseId(resultSet->getInt("course_id"));
        data.setClassroomId(resultSet->getInt("classroom_id"));
        data.setCreator(resultSet->getInt("creator"));
        data.setEditor(resultSet->getInt("editor"));
        data.setAddTime(resultSet->getString("add_time"));
        data.setEditTime(resultSet->getString("edit_time"));
        data.setDeleted(resultSet->getInt("deleted"));
        data.setTeacherId(resultSet->getInt("teacher_id"));
        data.setRemark(resultSet->getString("remark"));
        data.setBeOver(resultSet->getInt("be_over"));
        data.setOverTime(resultSet->getString("over_time"));
        data.setOverOperator(resultSet->getInt("over_operator"));
        data.setStartDate(resultSet->getString("start_date"));
        data.setEndDate(resultSet->getString("end_date"));
        data.setPlannedStudentCount(resultSet->getInt("planned_student_count"));
        data.setPlannedLessonCount(resultSet->getInt("planned_lesson_count"));
        data.setSchoolId(resultSet->getInt("school_id"));
        data.setOrgId(resultSet->getInt("org_id"));
        data.setGradeId(resultSet->getInt("grade_id"));

        // join 出来的展示字段（SQL 里别名已经是 classroom/teacher_name/course_name）
        data.setClassRoom(resultSet->getString("classroom"));       // t3.name classroom
        data.setTeacher_Name(resultSet->getString("teacher_name"));   // t4.name teacher_name
        data.setCourse_Name(resultSet->getString("course_name"));   // t7.name course_name
        data.setStudentCount(resultSet->getInt("student_count"));

        return data;
    }
};

/**
* 班级详情字段匹配映射类，负责将数据库查询结果映射为 ClassDO 对象
  * 通过实现 Mapper 接口的 mapper 方法，定义了从 ResultSet 到 ClassDO 的映射规则
  * 在 mapper 方法中，根据 class 表的字段以及 SQL join 出来的展示字段，从 ResultSet 中获取对应的值并设置到 ClassDO 对象中
  * 最终返回完整填充的 ClassDO 对象供后续使用
field      Type      Nullable
name 班级名,varchar(50),YES
start_date 计划开班日期,date,YES
end_date 计划结业日期,date,YES
remark 排课备注,varchar(255),YES
classroom 教室名,varchar(50),YES
teacher_name （教师）姓名,varchar(20),YES
course_name 课程名,varchar(50),YES
student_count 班级人数,bigint,YES
over_lesson_count 课次数量,bigint,YES
*//*
class ClassMapper : public Mapper<ClassDO>
{
public:
    ClassDO mapper(ResultSet* resultSet) const override
    {
        ClassDO data;
        // class 表字段
		data.setName(resultSet->getString("name"));
		data.setStartDate(resultSet->getString("start_date"));
		data.setEndDate(resultSet->getString("end_date"));
		data.setRemark(resultSet->getString("remark"));
		data.setClassRoom(resultSet->getString("classroom"));
		data.setTeacher_Name(resultSet->getString("teacher_name"));
		data.setCourse_Name(resultSet->getString("course_name"));
		data.setStudentCount(resultSet->getInt("student_count"));
		data.setOver_Lesson_Count(resultSet->getInt("over_lesson_count"));
        return data;
    }
};
*/

/**
* * 班级表字段匹配映射类，负责将数据库查询结果映射为 ClassDO 对象
  * 通过实现 Mapper 接口的 mapper 方法，定义了从 ResultSet 到 ClassDO 的映射规则
  * 在 mapper 方法中，根据 class 表的字段以及 SQL join 出来的展示字段，从 ResultSet 中获取对应的值并设置到 ClassDO 对象中
  * 最终返回完整填充的 ClassDO 对象供后续使用
*/
class StudentListMapper : public Mapper<StudentDO>
{
public:
    StudentDO mapper(ResultSet* resultSet) const override
    {
        StudentDO data;
        // student 表字段
        data.setGender(resultSet->getInt(1));
        data.setName(resultSet->getString(2));
        return data;
    }

};

/*
* 班级详情映射类，负责将数据库查询结果映射为 StudentDO 对象
  * 通过实现 Mapper 接口的 mapper 方法，定义了从 ResultSet 到 StudentDO 的映射规则
  * 在 mapper 方法中，根据 student 表的字段，从 ResultSet 中获取对应的值并设置到 StudentDO 对象中
  * 最终返回完整填充的 StudentDO 对象供后续使用
*/
/* Field Type Null
* name,varchar(50),YES
start_date,date,YES
end_date,date,YES
remark,varchar(255),YES
classroom,varchar(50),YES
teacher_name,varchar(20),YES
course_name,varchar(50),YES
student_count,bigint,YES
over_lesson_count,bigint,YES
*/
class ClassInfoMapper : public Mapper<ClassDO>
{
public:
    ClassDO mapper(ResultSet* resultSet) const override
    {
        ClassDO data;
        // class 表字段
		data.setId(resultSet->getInt("id"));
		data.setName(resultSet->getString("name"));
		data.setStartDate(resultSet->getString("start_date"));
		data.setEndDate(resultSet->getString("end_date"));
		data.setRemark(resultSet->getString("remark"));
		data.setClassRoom(resultSet->getString("classroom"));
		data.setTeacher_Name(resultSet->getString("teacher_name"));
		data.setCourse_Name(resultSet->getString("course_name"));
		data.setStudentCount(resultSet->getInt("student_count"));
		data.setOver_Lesson_Count(resultSet->getInt("over_lesson_count"));
        return data;
    }
};

#endif // !_SAMPLE_MAPPER_