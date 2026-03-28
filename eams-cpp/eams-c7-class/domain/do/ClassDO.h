#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _CLASS_DO_
#define _CLASS_DO_
#include "DoInclude.h"
#include "../lib-mysql/include/SqlHelper.h"
/**
 * class表对应的数据库实体类
 */
class ClassDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(long long, id, Id);
    // 班级名称
    MYSQL_SYNTHESIZE(std::string, name, Name);
    // 课程ID
    MYSQL_SYNTHESIZE(long long, courseId, CourseId);
    // 教室ID
    MYSQL_SYNTHESIZE(long long, classroomId, ClassroomId);
    // 创建人ID
    MYSQL_SYNTHESIZE(long long, creator, Creator);
    // 编辑人ID
    MYSQL_SYNTHESIZE(long long, editor, Editor);
    // 创建时间
    MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
    // 编辑时间
    MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
    // 逻辑删除标志（0未删除，1已删除）
    MYSQL_SYNTHESIZE(bool, deleted, Deleted);
    // 教师ID
    MYSQL_SYNTHESIZE(long long, teacherId, TeacherId);
    // 备注
    MYSQL_SYNTHESIZE(std::string, remark, Remark);
    // 是否结束（0未结束，1已结束）
    MYSQL_SYNTHESIZE(bool, beOver, BeOver);
    // 结束时间
    MYSQL_SYNTHESIZE(std::string, overTime, OverTime);
    // 结束操作人ID
    MYSQL_SYNTHESIZE(long long, overOperator, OverOperator);
    // 开始日期
    MYSQL_SYNTHESIZE(std::string, startDate, StartDate);
    // 结束日期
    MYSQL_SYNTHESIZE(std::string, endDate, EndDate);
    // 计划学生人数
    MYSQL_SYNTHESIZE(int, plannedStudentCount, PlannedStudentCount);
    // 计划课时数
    MYSQL_SYNTHESIZE(int, plannedLessonCount, PlannedLessonCount);
    // 学校ID
    MYSQL_SYNTHESIZE(long long, schoolId, SchoolId);
    // 组织ID
    MYSQL_SYNTHESIZE(long long, orgId, OrgId);
    // 年级ID
    MYSQL_SYNTHESIZE(int, gradeId, GradeId);

public:
    // 添加安全的getter方法
    long long safeGetId() const { return id ? *id.get() : 0; }
    std::string safeGetName() const { return name ? *name.get() : ""; }
    long long safeGetCourseId() const { return courseId ? *courseId.get() : 0; }
    ClassDO() : BaseDO("class")  
    {
        // 初始化所有shared_ptr变量
        id = std::make_shared<long long>(0);
        name = std::make_shared<std::string>("");
        courseId = std::make_shared<long long>(0);
        classroomId = std::make_shared<long long>(0);
        creator = std::make_shared<long long>(0);
        editor = std::make_shared<long long>(0);
        addTime = std::make_shared<std::string>("");
        editTime = std::make_shared<std::string>("");
        deleted = std::make_shared<bool>(false);
        teacherId = std::make_shared<long long>(0);
        remark = std::make_shared<std::string>("");
        beOver = std::make_shared<bool>(false);
        overTime = std::make_shared<std::string>("");
        overOperator = std::make_shared<long long>(0);
        startDate = std::make_shared<std::string>("");
        endDate = std::make_shared<std::string>("");
        plannedStudentCount = std::make_shared<int>(0);
        plannedLessonCount = std::make_shared<int>(0);
        schoolId = std::make_shared<long long>(0);
        orgId = std::make_shared<long long>(0);
        gradeId = std::make_shared<int>(0);

        // 注册主键字段
        MYSQL_ADD_FIELD_PK("id", "ll", id);
        // 注册普通字段
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("course_id", "ll", courseId);
        MYSQL_ADD_FIELD("classroom_id", "ll", classroomId);
        MYSQL_ADD_FIELD("creator", "ll", creator);
        MYSQL_ADD_FIELD("editor", "ll", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "b", deleted);
        MYSQL_ADD_FIELD("teacher_id", "ll", teacherId);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("be_over", "b", beOver);
        MYSQL_ADD_FIELD("over_time", "dt", overTime);
        MYSQL_ADD_FIELD("over_operator", "ll", overOperator);
        MYSQL_ADD_FIELD("start_date", "dt", startDate);
        MYSQL_ADD_FIELD("end_date", "dt", endDate);
        MYSQL_ADD_FIELD("planned_student_count", "i", plannedStudentCount);
        MYSQL_ADD_FIELD("planned_lesson_count", "i", plannedLessonCount);
        MYSQL_ADD_FIELD("school_id", "ll", schoolId);
        MYSQL_ADD_FIELD("org_id", "ll", orgId);
        MYSQL_ADD_FIELD("grade_id", "i", gradeId);
    }
};
/**
 * 文件视图对象，关联一些外表的字段
 */
class ClassViewDO : public ClassDO 
{
    // 教师名称
    MYSQL_SYNTHESIZE(string, teacherName, TeacherName);
    // 课程名称
    MYSQL_SYNTHESIZE(string, courseName, CourseName);
public:
    ClassViewDO()
    {
        // 注册新增的视图字段
        MYSQL_ADD_FIELD("teacher_name", "s", teacherName);
        MYSQL_ADD_FIELD("course_name", "s", courseName);
    }
};
// 给ClassDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ClassDO> PtrClassDO;
#endif // !_CLASS_DO_
