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
	//扣课时数
	API_DTO_FIELD_DEFAULT(UInt32, decLessonCount, ZH_WORDS_GETTER("attendance_records.dec_lesson_count"));
	//签到时间
	API_DTO_FIELD_DEFAULT(String, signTime, ZH_WORDS_GETTER("attendance_records.sign_time"));
	//补签
	API_DTO_FIELD_DEFAULT(UInt8, signState, ZH_WORDS_GETTER("attendance_records.sign_state"));
	//上课日期
	API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("attendance_records.date"));
	//上课开始时间
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("attendance_records.start_time"));
	//上课结束时间
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("attendance_records.end_time"));
	//课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("attendance_records.course_name"));
	//课时标题
	API_DTO_FIELD_DEFAULT(String, lessonTitle, ZH_WORDS_GETTER("attendance_records.lesson_title"));
	//是否可以评价
	API_DTO_FIELD_DEFAULT(UInt32, canEvaluate, ZH_WORDS_GETTER("attendance_records.can_evaluate"));
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
	// 课次id
	API_DTO_FIELD_REQUIRE(UInt64, lesson_id, ZH_WORDS_GETTER("attendance_records.teach_evaluation.lesson_id"), true);
	// 老师id
	API_DTO_FIELD_REQUIRE(UInt64, teacher_id, ZH_WORDS_GETTER("attendance_records.teach_evaluation.teacher_id"), true);
	// 综合评分
	API_DTO_FIELD_REQUIRE(UInt8, score1, ZH_WORDS_GETTER("attendance_records.teach_evaluation.score1"), true);
	// 课堂气氛
	API_DTO_FIELD_REQUIRE(UInt8, score2, ZH_WORDS_GETTER("attendance_records.teach_evaluation.score2"), true);
	// 授课态度
	API_DTO_FIELD_REQUIRE(UInt8, score3, ZH_WORDS_GETTER("attendance_records.teach_evaluation.score3"), true);
	// 教学效果
	API_DTO_FIELD_REQUIRE(UInt8, score4, ZH_WORDS_GETTER("attendance_records.teach_evaluation.score4"), true);
	// 评语
	API_DTO_FIELD_REQUIRE(String, content, ZH_WORDS_GETTER("attendance_records.teach_evaluation.content"), true);
	// 评价时间
	//API_DTO_FIELD_REQUIRE(String, add_time, ZH_WORDS_GETTER("attendance_records.teach_evaluation.add_time"), true);
	// 学生id
	API_DTO_FIELD_REQUIRE(UInt64, student_id, ZH_WORDS_GETTER("attendance_records.teach_evaluation.student_id"), true);
	// 是否匿名
	API_DTO_FIELD_REQUIRE(UInt8, anonymity, ZH_WORDS_GETTER("attendance_records.teach_evaluation.anonymity"), true);
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	string validate() 
	{
		if (score1 < 1 || score1 > 5) return "score1 invalidate.";
		if (score2 < 1 || score2 > 5) return "score2 invalidate.";
		if (score3 < 1 || score3 > 5) return "score3 invalidate.";
		if (score4 < 1 || score4 > 5) return "scpre4 invalidate.";
		return "";
	}
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_ATTENDANCEDTO_H_