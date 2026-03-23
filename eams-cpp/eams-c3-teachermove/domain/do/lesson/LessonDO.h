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
#ifndef _DO_INCLUDE_
#define _DO_INCLUDE_

#include "../../Macros.h"
#include "BaseDO.h"
#include <string>
#include <list>
#include <memory>
using namespace std;
class LessonDO : public BaseDO
{

    MYSQL_SYNTHESIZE(long long, id, Id);               // 主键
    MYSQL_SYNTHESIZE(string, title, Title);            // 课程标题
    MYSQL_SYNTHESIZE(int, sn, Sn);                     // 排序编号
    MYSQL_SYNTHESIZE(long long, courseId, CourseId);   // 课程ID
    MYSQL_SYNTHESIZE(long long, scheduleId, ScheduleId); // 排课ID
    MYSQL_SYNTHESIZE(long long, classId, ClassId);     // 班级ID
    MYSQL_SYNTHESIZE(long long, roomId, RoomId);       // 教室ID
    MYSQL_SYNTHESIZE(string, date, Date);              // 上课日期
    MYSQL_SYNTHESIZE(string, startTime, StartTime);    // 开始时间
    MYSQL_SYNTHESIZE(string, endTime, EndTime);        // 结束时间
    MYSQL_SYNTHESIZE(long long, creator, Creator);     // 创建人
    MYSQL_SYNTHESIZE(long long, editor, Editor);       // 修改人
    MYSQL_SYNTHESIZE(string, addTime, AddTime);        // 创建时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);      // 修改时间
    MYSQL_SYNTHESIZE(int, deleted, Deleted);           // 逻辑删除标记
    MYSQL_SYNTHESIZE(unsigned char, decCount, DecCount); // 扣减次数
    MYSQL_SYNTHESIZE(string, remark, Remark);          // 备注
    MYSQL_SYNTHESIZE(int, teachType, TeachType);       // 授课类型
    MYSQL_SYNTHESIZE(int, onTrial, OnTrial);           // 是否试听课
    MYSQL_SYNTHESIZE(string, trialResult, TrialResult);// 试听结果
    MYSQL_SYNTHESIZE(int, state, State);               // 课程状态
    MYSQL_SYNTHESIZE(string, closeTime, CloseTime);    // 关闭时间
    MYSQL_SYNTHESIZE(long long, closeOperator, CloseOperator); // 关闭操作人
    MYSQL_SYNTHESIZE(long long, teacherId, TeacherId); // 授课老师ID
    MYSQL_SYNTHESIZE(int, bookable, Bookable);         // 是否可预约
    MYSQL_SYNTHESIZE(long long, schoolId, SchoolId);   // 学校ID
    MYSQL_SYNTHESIZE(long long, orgId, OrgId);         // 机构ID

public:
    LessonDO() : BaseDO("lesson")
    {
        MYSQL_ADD_FIELD_PK("id", "ll", id);
        MYSQL_ADD_FIELD("title", "s", title);
        MYSQL_ADD_FIELD("sn", "i", sn);
        MYSQL_ADD_FIELD("course_id", "ll", courseId);
        MYSQL_ADD_FIELD("schedule_id", "ll", scheduleId);
        MYSQL_ADD_FIELD("class_id", "ll", classId);
        MYSQL_ADD_FIELD("room_id", "ll", roomId);
        MYSQL_ADD_FIELD("date", "s", date);
        MYSQL_ADD_FIELD("start_time", "s", startTime);
        MYSQL_ADD_FIELD("end_time", "s", endTime);
        MYSQL_ADD_FIELD("creator", "ll", creator);
        MYSQL_ADD_FIELD("editor", "ll", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("dec_count", "c", decCount);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("teach_type", "i", teachType);
        MYSQL_ADD_FIELD("on_trial", "i", onTrial);
        MYSQL_ADD_FIELD("trial_result", "s", trialResult);
        MYSQL_ADD_FIELD("state", "i", state);
        MYSQL_ADD_FIELD("close_time", "s", closeTime);
        MYSQL_ADD_FIELD("close_operator", "ll", closeOperator);
        MYSQL_ADD_FIELD("teacher_id", "ll", teacherId);
        MYSQL_ADD_FIELD("bookable", "i", bookable);
        MYSQL_ADD_FIELD("school_id", "ll", schoolId);
        MYSQL_ADD_FIELD("org_id", "ll", orgId);
    }
};

// 智能指针别名
typedef std::shared_ptr<LessonDO> PtrLessonDO;


#endif // !_DO_INCLUDE_