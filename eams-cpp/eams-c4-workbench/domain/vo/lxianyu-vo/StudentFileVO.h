#pragma once

//#include "ApiHelper.h"
//#include "../Macros.h"
//#include "ServerInfo.h"
#include "../../GlobalInclude.h"
#include "../../dto/lxianyu-dto/StudentFileDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
 */
class StudentFileJsonVO : public JsonVO<StudentFileDTO::Wrapper> {
	DTO_INIT(StudentFileJsonVO, JsonVO<StudentFileDTO::Wrapper>);
};

class StudentFilePageJsonVO : public JsonVO<StudentFilePageDTO::Wrapper> {
	DTO_INIT(StudentFilePageJsonVO, JsonVO<StudentFilePageDTO::Wrapper>);
};

class StudentTimeTableJsonVO : public JsonVO<StudentTimeTableDTO::Wrapper> {
	DTO_INIT(StudentTimeTableJsonVO, JsonVO<StudentTimeTableDTO::Wrapper>);
};

class StudentTimeTablePageJsonVO : public JsonVO<StudentTimeTablePageDTO::Wrapper> {
	DTO_INIT(StudentTimeTablePageJsonVO, JsonVO<StudentTimeTablePageDTO::Wrapper>);
};

class StudentFileProJsonVO : public JsonVO<StudentFileProDTO::Wrapper> {
	DTO_INIT(StudentFileProJsonVO, JsonVO<StudentFileProDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)