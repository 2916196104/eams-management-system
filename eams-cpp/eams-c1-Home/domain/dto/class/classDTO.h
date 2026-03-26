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
#ifndef _CLASSDTO_H_
#define _CLASSDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 班级数据传输对象
 */
class ClassDTO : public oatpp::DTO
{
	DTO_INIT(ClassDTO, DTO);
	//主键id
	API_DTO_FIELD_REQUIRE(UInt32, id, ZH_WORDS_GETTER("class.id"), true);
	// 班级名
	API_DTO_FIELD_REQUIRE(String, class_name, ZH_WORDS_GETTER("class.class_name"), true);
	// 班级负责⼈id
	API_DTO_FIELD_DEFAULT(UInt32, teacher_id, ZH_WORDS_GETTER("class.teacher_id"));
	// 教师名称
	API_DTO_FIELD_DEFAULT(String, teacher_name, ZH_WORDS_GETTER("class.teacher_name"));
	// 课程id
	API_DTO_FIELD_REQUIRE(UInt32, course_id, ZH_WORDS_GETTER("class.course_id"), true);
	// 课程套餐课程名
	API_DTO_FIELD_REQUIRE(String, course_name, ZH_WORDS_GETTER("class.course_name"), true);
	// 计划开班日期
	API_DTO_FIELD_DEFAULT(String, start_date, ZH_WORDS_GETTER("class.start_date"));
	// 计划结业日期
	API_DTO_FIELD_DEFAULT(String, end_date, ZH_WORDS_GETTER("class.end_date"));
	//学生人数
	API_DTO_FIELD_DEFAULT(UInt32, student_count, ZH_WORDS_GETTER("class.student_count"));
};

/*
 * 班级分页数据传输对象
 */
class ClassPageDTO : public PageDTO<ClassDTO::Wrapper>
{
	DTO_INIT(ClassPageDTO, PageDTO<ClassDTO::Wrapper>);
};

/*
* 班级列表数据传输对象

class ClassListDTO : public oatpp::DTO
{
	DTO_INIT(ClassListDTO, DTO);
	// 班级列表
	API_DTO_FIELD_DEFAULT(List<ClassDTO::Wrapper>, class_list, ZH_WORDS_GETTER("class.class_list"));
};
*/

/*
* 班级详情数据传输对象
*/
class ClassInfoDTO : public ClassDTO
{
	DTO_INIT(ClassInfoDTO, ClassDTO);
	// 教室id
	API_DTO_FIELD_DEFAULT(UInt32, classroom_id, ZH_WORDS_GETTER("class.classroom_id"));
	// 教室名称
	API_DTO_FIELD_DEFAULT(String, classroom_name, ZH_WORDS_GETTER("class.classroom_name"));
	// 排课备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("class.remark"));
};

/*
* 学生数据传输对象
*/
class StudentDTO : public oatpp::DTO
{
	DTO_INIT(StudentDTO, DTO);
	// 学生id
	API_DTO_FIELD_REQUIRE(UInt32, id, ZH_WORDS_GETTER("class.student.id"), true);
	// 学生姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("class.student.name"), true);
	// 学生性别
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("class.student.gender"));
};

/*
* 学生列表数据传输对象
*/
class StudentListDTO : public oatpp::DTO
{
	DTO_INIT(StudentListDTO, DTO);
	// 学生列表
	API_DTO_FIELD_DEFAULT(List<StudentDTO::Wrapper>, student_list, ZH_WORDS_GETTER("class.student_list"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASSDTO_H_