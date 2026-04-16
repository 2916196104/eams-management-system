#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:51:41

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
#ifndef _LESSON_DO_H_
#define _LESSON_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"
#include <string>
#include <memory>

class LessonDO : public BaseDO
{
    MYSQL_SYNTHESIZE(uint64_t, id, Id);                 // 主键
    MYSQL_SYNTHESIZE(std::string, title, Title);        // 课程标题
    MYSQL_SYNTHESIZE(int32_t, sn, Sn);                  // 第几节课
    MYSQL_SYNTHESIZE(int64_t, courseId, CourseId);      // 课程ID
    MYSQL_SYNTHESIZE(int64_t, scheduleId, ScheduleId);  // 编排计划ID
    MYSQL_SYNTHESIZE(int64_t, classId, ClassId);        // 班级ID
    MYSQL_SYNTHESIZE(int64_t, roomId, RoomId);          // 教室ID
    MYSQL_SYNTHESIZE(std::string, date, Date);          // 上课日期
    MYSQL_SYNTHESIZE(std::string, startTime, StartTime);// 开始时间
    MYSQL_SYNTHESIZE(std::string, endTime, EndTime);    // 结束时间
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);        // 创建人
    MYSQL_SYNTHESIZE(int64_t, editor, Editor);          // 编辑者
    MYSQL_SYNTHESIZE(std::string, addTime, AddTime);    // 添加时间
    MYSQL_SYNTHESIZE(std::string, editTime, EditTime);  // 修改时间
    MYSQL_SYNTHESIZE(bool, deleted, Deleted);           // 删除标记
    MYSQL_SYNTHESIZE(uint32_t, decCount, DecCount);     // 应扣课次数
    MYSQL_SYNTHESIZE(std::string, remark, Remark);      // 备注
    MYSQL_SYNTHESIZE(int32_t, teachType, TeachType);    // 授课方式
    MYSQL_SYNTHESIZE(bool, onTrial, OnTrial);           // 是否开启试听
    MYSQL_SYNTHESIZE(std::string, trialResult, TrialResult);// 试听结果
    MYSQL_SYNTHESIZE(int32_t, state, State);            // 课次状态
    MYSQL_SYNTHESIZE(std::string, closeTime, CloseTime);// 结课时间
    MYSQL_SYNTHESIZE(int64_t, closeOperator, CloseOperator);// 结课人
    MYSQL_SYNTHESIZE(int64_t, teacherId, TeacherId);    // 主讲人
    MYSQL_SYNTHESIZE(bool, bookable, Bookable);         // 是否开放预约
    MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);      // 老师所属学校ID
    MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);            // 创建者所属组织ID

public:
    LessonDO() : BaseDO("lesson")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("title", "s", title, false);
        MYSQL_ADD_FIELD("sn", "i", sn);
        MYSQL_ADD_FIELD_NULLABLE("course_id", "ll", courseId, false);
        MYSQL_ADD_FIELD("schedule_id", "ll", scheduleId);
        MYSQL_ADD_FIELD("class_id", "ll", classId);
        MYSQL_ADD_FIELD("room_id", "ll", roomId);
        MYSQL_ADD_FIELD("date", "dt", date);
        MYSQL_ADD_FIELD("start_time", "dt", startTime);
        MYSQL_ADD_FIELD("end_time", "dt", endTime);
        MYSQL_ADD_FIELD("creator", "ll", creator);
        MYSQL_ADD_FIELD("editor", "ll", editor);
        MYSQL_ADD_FIELD("add_time", "dt", addTime);
        MYSQL_ADD_FIELD("edit_time", "dt", editTime);
        MYSQL_ADD_FIELD("deleted", "b", deleted);
        MYSQL_ADD_FIELD("dec_count", "ui", decCount);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("teach_type", "i", teachType);
        MYSQL_ADD_FIELD("on_trial", "b", onTrial);
        MYSQL_ADD_FIELD("trial_result", "s", trialResult);
        MYSQL_ADD_FIELD("state", "i", state);
        MYSQL_ADD_FIELD("close_time", "dt", closeTime);
        MYSQL_ADD_FIELD("close_operator", "ll", closeOperator);
        MYSQL_ADD_FIELD("teacher_id", "ll", teacherId);
        MYSQL_ADD_FIELD("bookable", "b", bookable);
        MYSQL_ADD_FIELD("school_id", "ll", schoolId);
        MYSQL_ADD_FIELD("org_id", "ll", orgId);
    }
};

// 智能指针别名
typedef std::shared_ptr<LessonDO> PtrLessonDO;


#endif // !_LESSON_DO_H_