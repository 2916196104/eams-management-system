#ifndef _BACKHOMEWORKDTO_H_
#define _BACKHOMEWORKDTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/


class Backhomework : public oatpp::DTO
{
	DTO_INIT(Backhomework, DTO)
};

#include OATPP_CODEGEN_END(DTO)

#endif /* _BACKHOMEWORKDTO_H_ */