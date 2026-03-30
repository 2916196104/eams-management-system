#include "../../GlobalInclude.h"
#include "../../dto/lxianyu-dto/ClassDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
 */
class MyClassJsonVO : public JsonVO<MyClassDTO::Wrapper> {
	DTO_INIT(MyClassJsonVO, JsonVO<MyClassDTO::Wrapper>);
};

class MyClassPageJsonVO : public JsonVO<MyClassPageDTO::Wrapper> {
	DTO_INIT(MyClassPageJsonVO, JsonVO<MyClassPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)