#pragma once
#ifndef _COURSERECORD_VO_H_
#define _COURSERECORD_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/CourseRecord/CourseRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 上课记录分页显示JsonVO，用于响应给客户端的Json对象
 */
class CourseRecordPageJsonVO : public JsonVO<CourseRecordPageDTO::Wrapper> {
	DTO_INIT(CourseRecordPageJsonVO, JsonVO<CourseRecordPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSERECORD_VO_H_
