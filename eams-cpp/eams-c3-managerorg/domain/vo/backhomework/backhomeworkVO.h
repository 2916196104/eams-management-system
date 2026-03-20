#ifndef __BACKHOMEWORKVO_H__
#define __BACKHOMEWORKVO_H__

#include "../../GlobalInclude.h"
#include "../../dto/backhomework/backhomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/*课后作业视图类*/

//获取作业列表（条件+分页）
class GetHomeworkListJsonVO : public JsonVO<GetHomeworkListDTO::Wrapper> {
    DTO_INIT(GetHomeworkListJsonVO, JsonVO<GetHomeworkListDTO::Wrapper>)
};

class GetHomeworkListPageJsonVO : public JsonVO<GetHomeworkListPageDTO::Wrapper> {
    DTO_INIT(GetHomeworkListPageJsonVO, JsonVO<GetHomeworkListPageDTO::Wrapper>)
};

//获取作业详情
class GetHomeworkDetailJsonVO : public JsonVO<GetHomeworkDetailDTO::Wrapper> {
    DTO_INIT(GetHomeworkDetailJsonVO, JsonVO<GetHomeworkDetailDTO::Wrapper>);
};

//保存作业
class SaveHomeworkJsonVO : public JsonVO<GetHomeworkDetailDTO::Wrapper> {
    DTO_INIT(SaveHomeworkJsonVO, JsonVO<GetHomeworkDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif