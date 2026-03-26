#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/21 22:37:32

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
#ifndef _SCORE_DO_
#define _SCORE_DO_
#include "../DoInclude.h"

/**
 * 成绩单学生分数表数据模型
 */
class GradeRecordDO : public BaseDO {
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 考核项id
    MYSQL_SYNTHESIZE(uint64_t, gradeId, GradeId);
    // 学生id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 分数
    MYSQL_SYNTHESIZE(int, score, Score);
    // 添加时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);

public:
    GradeRecordDO() : BaseDO("grade_record")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("grade_id", "ull", gradeId, true);
        MYSQL_ADD_FIELD_NULLABLE("student_id", "ull", studentId, true);
        MYSQL_ADD_FIELD_NULLABLE("score", "i", score, true);
        MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
    }
};

// 给GradeRecordDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GradeRecordDO> PtrGradeRecordDO;

/**
 * 成绩视图对象，关联一些外表的字段
 */
class ScoreViewDO : public GradeRecordDO {
    MYSQL_SYNTHESIZE(string, gradeTitle, GradeTitle);   // 关联Grade表的title字段
    MYSQL_SYNTHESIZE(string, studentName, StudentName); // 关联Student表的name字段
};

// 给ScoreDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ScoreViewDO> PtrScoreViewDO;

/**
 * 成绩单表数据模型
 */
class GradeDO : public BaseDO {
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 成绩项目标题
    MYSQL_SYNTHESIZE(string, title, Title);
    // 成绩项目说明
    MYSQL_SYNTHESIZE(string, info, Info);
    // 创建者
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);
    // 创建时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 逻辑删除
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 编辑者
    MYSQL_SYNTHESIZE(int64_t, editor, Editor);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 创建者所属组织ID
    MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
    GradeDO() : BaseDO("grade")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("title", "s", title, false);
        MYSQL_ADD_FIELD_NULLABLE("info", "s", info, false);
        MYSQL_ADD_FIELD_NULLABLE("creator", "ll", creator, true);
        MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
        MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleted, true);
        MYSQL_ADD_FIELD_NULLABLE("editor", "ll", editor, true);
        MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime, true);
        MYSQL_ADD_FIELD_NULLABLE("org_id", "ll", orgId, true);
    }
};

// 给GradeDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GradeDO> PtrGradeDO;

/**
 * 学生表数据模型
 */
class StudentDO : public BaseDO {
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 家长id
    MYSQL_SYNTHESIZE(int64_t, userId, UserId);
    // 家庭关系
    MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
    // 家长默认查看的学员
    MYSQL_SYNTHESIZE(int, asDefault, AsDefault);
    // 所属分校
    MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
    // 姓名
    MYSQL_SYNTHESIZE(string, name, Name);
    // 逻辑删除
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 阶段状态0意向学员
    MYSQL_SYNTHESIZE(int, stage, Stage);
    // 性别
    MYSQL_SYNTHESIZE(int, gender, Gender);
    // 生日
    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    // 头像
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);
    // 加入方式
    MYSQL_SYNTHESIZE(int64_t, joinWay, JoinWay);
    // 备注
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 结业日期
    MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
    // 结业原因
    MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
    // 加入时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 顾问
    MYSQL_SYNTHESIZE(int64_t, counselor, Counselor);
    // 创建者
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);
    // 编辑人
    MYSQL_SYNTHESIZE(int64_t, editor, Editor);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 身份证号
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    // 红点标记成绩最后查看时间
    MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
    // 红点标记点评最后查看时间
    MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
    // 入学年份
    MYSQL_SYNTHESIZE(int, grade, Grade);
    // 入学日期
    MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
    // 微信登录记录id
    MYSQL_SYNTHESIZE(int64_t, wxAccessId, WxAccessId);
    // 学生积分
    MYSQL_SYNTHESIZE(int, credit, Credit);
    // 创建者所属组织ID
    MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);
    // 年级ID
    MYSQL_SYNTHESIZE(int, gradeId, GradeId);

public:
    StudentDO() : BaseDO("student")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("user_id", "ll", userId, false);
        MYSQL_ADD_FIELD_NULLABLE("family_rel", "i", familyRel, true);
        MYSQL_ADD_FIELD_NULLABLE("as_default", "i", asDefault, true);
        MYSQL_ADD_FIELD_NULLABLE("school_id", "ll", schoolId, true);
        MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
        MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleted, true);
        MYSQL_ADD_FIELD_NULLABLE("stage", "i", stage, true);
        MYSQL_ADD_FIELD_NULLABLE("gender", "i", gender, true);
        MYSQL_ADD_FIELD_NULLABLE("birthday", "s", birthday, true);
        MYSQL_ADD_FIELD_NULLABLE("head_img", "s", headImg, true);
        MYSQL_ADD_FIELD_NULLABLE("join_way", "ll", joinWay, true);
        MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
        MYSQL_ADD_FIELD_NULLABLE("graduation_date", "s", graduationDate, true);
        MYSQL_ADD_FIELD_NULLABLE("graduation_reason", "s", graduationReason, true);
        MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
        MYSQL_ADD_FIELD_NULLABLE("counselor", "ll", counselor, true);
        MYSQL_ADD_FIELD_NULLABLE("creator", "ll", creator, true);
        MYSQL_ADD_FIELD_NULLABLE("editor", "ll", editor, true);
        MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime, true);
        MYSQL_ADD_FIELD_NULLABLE("idcard", "s", idcard, true);
        MYSQL_ADD_FIELD_NULLABLE("redpoint_grade", "s", redpointGrade, true);
        MYSQL_ADD_FIELD_NULLABLE("redpoint_evaluate", "s", redpointEvaluate, true);
        MYSQL_ADD_FIELD_NULLABLE("grade", "i", grade, true);
        MYSQL_ADD_FIELD_NULLABLE("join_date", "s", joinDate, true);
        MYSQL_ADD_FIELD_NULLABLE("wx_access_id", "ll", wxAccessId, true);
        MYSQL_ADD_FIELD_NULLABLE("credit", "i", credit, true);
        MYSQL_ADD_FIELD_NULLABLE("org_id", "ll", orgId, true);
        MYSQL_ADD_FIELD_NULLABLE("grade_id", "i", gradeId, true);
    }
};

typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif // !_SCORE_DO_
