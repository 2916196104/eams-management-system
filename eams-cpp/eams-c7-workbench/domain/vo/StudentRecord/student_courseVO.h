#pragma once
//#include "../GlobalInclude.h"
#include "../../dto/StudentRecord/student_courseDTO.h"

#ifndef _STUDENT_COURSEVO_H_
#define _STUDENT_COURSEVO_H_

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学员课程进度JsonVO，用于响应给客户端的Json对象
 
class CourseProgressJsonVO : public JsonVO<CourseProgressDTO::Wrapper> {
	DTO_INIT(CourseProgressJsonVO, JsonVO<CourseProgressDTO::Wrapper>);
};*/

/**
 * 学员课程进度分页显示JsonVO，用于响应给客户端的Json对象
 */
class CourseProgressPageJsonVO : public JsonVO<CourseProgressPageDTO::Wrapper> {
	DTO_INIT(CourseProgressPageJsonVO, JsonVO<CourseProgressPageDTO::Wrapper>);
};
/**
 * 学员课时记录分页显示JsonVO，用于响应给客户端的Json对象
 */
class CourseRecordPageJsonVO : public JsonVO<CourseRecordPageDTO::Wrapper> {
	DTO_INIT(CourseRecordPageJsonVO, JsonVO<CourseRecordPageDTO::Wrapper>);
};
/**
 * 学员报名数据分页显示JsonVO，用于响应给客户端的Json对象
 */
class StudentSighnUPPageJsonVO : public JsonVO<StudentSighnUPPageDTO::Wrapper> {
	DTO_INIT(StudentSighnUPPageJsonVO, JsonVO<StudentSighnUPPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif