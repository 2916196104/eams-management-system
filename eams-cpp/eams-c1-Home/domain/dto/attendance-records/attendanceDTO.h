#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

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
#ifndef _ATTENDANCEDTO_H_
#define _ATTENDANCEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 上课记录数据传输对象
 */
class attendance_recordsDTO : public oatpp::DTO
{
	DTO_INIT(attendance_recordsDTO, DTO);
	//主键id
	API_DTO_FIELD_REQUIRE(UInt32, id, ZH_WORDS_GETTER("attendance_records.id"), true);
	//补签
	API_DTO_FIELD_DEFAULT(String, signState, ZH_WORDS_GETTER("attendance_records.sign_state"));
	//扣课时数
	API_DTO_FIELD_DEFAULT(UInt32, decLessonCount, ZH_WORDS_GETTER("attendance_records.dec_lesson_count"));
	//签到类型
	API_DTO_FIELD_DEFAULT(String, signType, ZH_WORDS_GETTER("attendance_records.sign_type"));
	//签到时间
	API_DTO_FIELD_DEFAULT(String, signTime, ZH_WORDS_GETTER("attendance_records.sign_time"));
	//课时id
	API_DTO_FIELD_REQUIRE(UInt32, lessonId, ZH_WORDS_GETTER("attendance_records.lesson_id"), true);
	//课时标题
	API_DTO_FIELD_DEFAULT(String, lessonTitle, ZH_WORDS_GETTER("attendance_records.lesson_title"));
	//课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("attendance_records.course_name"));
	//是否可以评价
	API_DTO_FIELD_DEFAULT(Boolean, canEvaluate, ZH_WORDS_GETTER("attendance_records.can_evaluate"));
	//上课日期
	API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("attendance_records.date"));
	//上课开始时间
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("attendance_records.start_time"));
	//上课结束时间
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("attendance_records.end_time"));
};

/*   
* 上课记录分页数据传输对象
*/
class attendance_recordsPageDTO : public PageDTO<attendance_recordsDTO::Wrapper>
{
	DTO_INIT(attendance_recordsPageDTO, PageDTO<attendance_recordsDTO::Wrapper>);
};

/*    
* 评价课次数据传输对象
*/
class attendance_recordsEvaluateDTO : public oatpp::DTO
{
    DTO_INIT(attendance_recordsEvaluateDTO, DTO);
    //主键id
    API_DTO_FIELD_REQUIRE(UInt32, id, ZH_WORDS_GETTER("attendance_records.id"), true);
	//上课日期  
	API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("attendance_records.date"));
	//上课开始时间
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("attendance_records.start_time"));
	//上课结束时间
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("attendance_records.end_time"));
	//课时标题
	API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("attendance_records.title"));
	//教师姓名
	API_DTO_FIELD_REQUIRE(String, teacherNames, ZH_WORDS_GETTER("attendance_records.teacher_names"), true);
	//教师id
	API_DTO_FIELD_REQUIRE(String, teacherIds, ZH_WORDS_GETTER("attendance_records.teacher_ids"), true);
	//助教姓名
	API_DTO_FIELD_DEFAULT(String, assistantNames, ZH_WORDS_GETTER("attendance_records.assistant_names"));
	//助教id
	API_DTO_FIELD_DEFAULT(String, assistantIds, ZH_WORDS_GETTER("attendance_records.assistant_ids"));
	//课程名称
	API_DTO_FIELD_REQUIRE(String, courseName, ZH_WORDS_GETTER("attendance_records.course_name"), true);
	//班级id
	API_DTO_FIELD_REQUIRE(UInt32, classId, ZH_WORDS_GETTER("attendance_records.class_id"), true);
	//教室id
	API_DTO_FIELD_DEFAULT(UInt32, roomId, ZH_WORDS_GETTER("attendance_records.room_id"));
	//班级名称
	API_DTO_FIELD_REQUIRE(String, className, ZH_WORDS_GETTER("attendance_records.class_name"), true);
	//课程类型
	API_DTO_FIELD_DEFAULT(String, lessonType, ZH_WORDS_GETTER("attendance_records.lesson_type"));
	//教室
	API_DTO_FIELD_DEFAULT(String, classroom, ZH_WORDS_GETTER("attendance_records.classroom"));
	//授课方式
	API_DTO_FIELD_DEFAULT(String, teachType, ZH_WORDS_GETTER("attendance_records.teach_type"));
	//扣课时数
	API_DTO_FIELD_DEFAULT(UInt32, decCount, ZH_WORDS_GETTER("attendance_records.dec_count"));
	//学生签到状态
	API_DTO_FIELD_DEFAULT(String, studentSignState, ZH_WORDS_GETTER("attendance_records.student_sign_state"));
	//学生扣课时数
	API_DTO_FIELD_DEFAULT(UInt32, studentDecLessonCount, ZH_WORDS_GETTER("attendance_records.student_dec_lesson_count"));
	//学生签到人数
	API_DTO_FIELD_DEFAULT(UInt32, studentSignNum, ZH_WORDS_GETTER("attendance_records.student_sign_num"));
	//学生总人数
	API_DTO_FIELD_DEFAULT(UInt32, studentNum, ZH_WORDS_GETTER("attendance_records.student_num"));
	//备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("attendance_records.remark"));
	//是否可预约
	API_DTO_FIELD_DEFAULT(Boolean, bookable, ZH_WORDS_GETTER("attendance_records.bookable"));
	//上课状态
	API_DTO_FIELD_DEFAULT(String, state, ZH_WORDS_GETTER("attendance_records.state"));
	//学生是否可以请假
	API_DTO_FIELD_DEFAULT(Boolean, studentCanLeave, ZH_WORDS_GETTER("attendance_records.student_can_leave"));
	//学生是否可以签到
	API_DTO_FIELD_DEFAULT(Boolean, studentCanSign, ZH_WORDS_GETTER("attendance_records.student_can_sign"));
	//教师是否可以评价
	API_DTO_FIELD_DEFAULT(Boolean, teacherCanEvaluate, ZH_WORDS_GETTER("attendance_records.teacher_can_evaluate"));
	//总人数
	API_DTO_FIELD_DEFAULT(UInt32, signCounts_countTotal, ZH_WORDS_GETTER("attendance_records.sign_counts_count_total"));
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_ATTENDANCEDTO_H_