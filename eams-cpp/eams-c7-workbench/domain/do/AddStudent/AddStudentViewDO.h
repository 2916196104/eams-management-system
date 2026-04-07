#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:47:24

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

#ifndef _ADDSTUDENTVIEWDO_H_
#define _ADDSTUDENTVIEWDO_H_
#include "../DoInclude.h"
#include "SqlHelper.h"
#include "domain/do/Mycustomers/StudentDo.h"

class AddStudentViewDo {
    // 主键ID
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 家长id
    MYSQL_SYNTHESIZE(uint64_t, user_id, UserId);
    // 家庭关系
    MYSQL_SYNTHESIZE(int32_t, family_rel, FamilyRel);
    // 所属分校
    MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
    // 姓名
    MYSQL_SYNTHESIZE(string, name, Name);
    // 阶段状态0意向学员
    MYSQL_SYNTHESIZE(int32_t, stage, Stage);
    // 性别
    MYSQL_SYNTHESIZE(int32_t, gender, Gender);
    // 生日
    MYSQL_SYNTHESIZE(string, birthday, Birthday);
    // 备注
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 加入时间
    MYSQL_SYNTHESIZE(string, add_time, AddTime);
    // 创建者
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 身份证号
    MYSQL_SYNTHESIZE(string, idcard, Idcard);
    // 入学年份
    MYSQL_SYNTHESIZE(int32_t, grade, Grade);
    // 入学日期
    MYSQL_SYNTHESIZE(string, join_date, JoinDate);

	MYSQL_SYNTHESIZE(string, phone, Phone);//仅用于查询user_id，不入库

};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<AddStudentViewDo> PtrAddStudentViewDo;

#endif // !_ADDSTUDENTVIEWDO_H_