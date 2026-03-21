#pragma once
#include "oatpp/core/Types.hpp"
#include "../lib-oatpp/include/ApiHelper.h"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/dto/parent/ParentDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// JsonVO是模板类，包装任意数据类型
class UsageGuideJsonVO : public JsonVO<UsageListDTO::Wrapper> {
	DTO_INIT(UsageGuideJsonVO, JsonVO<UsageListDTO::Wrapper>);
};

class UsagePageJsonVO : public JsonVO<UsagePageDTO::Wrapper> {
	DTO_INIT(UsagePageJsonVO, JsonVO<UsagePageDTO::Wrapper>);
};

class UsageDeatailJsonVO : public JsonVO<UsageGuideDetailDto::Wrapper> {
	DTO_INIT(UsageDeatailJsonVO, JsonVO<UsageGuideDetailDto::Wrapper>);
};

//class UsageGuideVO : public oatpp::DTO {
//	DTO_INIT(UsageGuideVO, DTO);
//	API_DTO_FIELD(Int32, id, "id", true, 0);
//	API_DTO_FIELD(String, title, "title", true, "");
//	API_DTO_FIELD(String, createtime, "createtime", true, "");
//};
//
//
//class UsageGuidePageVO : public oatpp::DTO {
//	DTO_INIT(UsageGuidePageVO, DTO);
//	API_DTO_FIELD(Int32, total, "total", true, 0);
//	API_DTO_FIELD(Int32, pageIndex, "pageIndex", true, 0);
//	API_DTO_FIELD(Int32, pageSize, " pageSize", true, 0);
//	API_DTO_FIELD(Vector<Object<UsageGuideDto>>, list, "datalist", true, {});
//};
//
////使用说明详情
//class UsageGuideDetailVO : public oatpp::DTO {
//	DTO_INIT(UsageGuideDetailVO, DTO);
//	API_DTO_FIELD(Int32, id, "id", true, 0);
//	API_DTO_FIELD(String, title, "title", true, "");
//	API_DTO_FIELD(String, content, " content", true, "");
//};

#include OATPP_CODEGEN_END(DTO)