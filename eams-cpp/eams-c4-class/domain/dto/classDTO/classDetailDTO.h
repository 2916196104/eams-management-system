#pragma once
#ifndef CLASSDETAIL_DTO_
#define CLASSDETAIL_DTO_

#include"../../GlobalInclude.h"	
#include OATPP_CODEGEN_BEGIN(DTO)

/*
*班级数据传输对象
*/
class ClassDTO : public oatpp::DTO
{
	DTO_INIT(ClassDTO, DTO);
};

class ClassDetailDTO : public ClassDTO
{
	DTO_INIT(ClassDetailDTO, ClassDTO);

};


#include OATPP_CODEGEN_END(DTO)
#endif // !CLASSCONTROLLER_DTO_
