#ifndef __CLASS_STUDENT_VO_H__
#define __CLASS_STUDENT_VO_H__

#include "../../GlobalInclude.h"
#include "domain/dto/class/ClassStudentDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员分页响应 VO
 */
class ClassStudentPageJsonVO : public JsonVO<ClassStudentListPageDTO::Wrapper>
{
	DTO_INIT(ClassStudentPageJsonVO, JsonVO<ClassStudentListPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
