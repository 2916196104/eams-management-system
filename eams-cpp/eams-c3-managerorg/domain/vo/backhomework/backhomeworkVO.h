#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业视图类*/

//获取作业列表（条件+分页）
class GetHomeworkListJsonVO : public JsonVO<HomeworkDTO::Wrapper>{
	DTO_INIT(GetHomeworkListJsonVO, JsonVO<HomeworkDTO::Wrapper>)
};

//获取作业详情
class GetHomeworkDetailJsonVO : public JsonVO<HomeworkDTO::Wrapper> {
    DTO_INIT(GetHomeworkDetailJsonVO, JsonVO<HomeworkDTO::Wrapper>);
};

//保存作业
class SaveHomeworkJsonVO : public JsonVO<HomeworkDTO::Wrapper> {
    DTO_INIT(SaveHomeworkJsonVO, JsonVO<HomeworkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif