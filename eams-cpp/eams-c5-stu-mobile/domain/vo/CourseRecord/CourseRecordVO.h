#pragma once
#ifndef _COURSERECORD_VO_H_
#define _COURSERECORD_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/CourseRecord/CourseRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 上课记录分页显示JsonVO，用于响应给客户端的Json对象
 */
Class CourseRecordJsonVO : public JsonVO<CourseRecordDTO::Wrapper>{
	DTO_INIT(CourseRecordJsonVO, JsonVO<CourseRecordDTO::Wrapper>);
}

/**
 * 课程评价分页显示JsonVO，用于响应给客户端的Json对象
 */
Class CourseRecordPageJsonVO : public JsonVO<CourseRecordPageDTO::Wrapper>{
	DTO_INIT(CourseRecordPageJsonVO, JsonVO<CourseRecordPageDTO::Wrapper>);
}

#inclulde OATPP_CODEGEN_END(DTO)


#endif // !_COURSERECORD_VO_H_
