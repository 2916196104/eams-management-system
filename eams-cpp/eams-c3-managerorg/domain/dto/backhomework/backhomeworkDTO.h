#ifndef _BACKHOMEWORKDTO_H_
#define _BACKHOMEWORKDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/

//获取作业列表（条件+分页）
class GetHomeworkListDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkListDTO, oatpp::DTO);
};

//获取作业详情
class GetHomeworkDetailDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkDetailDTO, oatpp::DTO);
};

//保存作业
class GetHomeworkDetailDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkDetailDTO, oatpp::DTO);
};


#include OATPP_CODEGEN_END(DTO)

#endif /* _BACKHOMEWORKDTO_H_ */