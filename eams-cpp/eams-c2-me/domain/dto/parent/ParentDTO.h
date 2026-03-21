#pragma once

#ifndef _PARENTDTO_H_
#define _PARENTDTO_H_

#include "../../GlobalInclude.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
	家长数据传输对象
 */



 // PageDTO是模板类，用于分页数据
class ParentDTO : public oatpp::DTO {
  DTO_INIT(ParentDTO, DTO);
};
// 自动包含字段：
// - pageIndex: 当前页码
// - pageSize: 每页条数
// - total: 总记录数
// - pages: 总页数
// - rows: 数据列表 List<SampleDTO::Wrapper>



//使用说明列表中的单条数据DTO
class UsageGuideDto : public oatpp::DTO {
	DTO_INIT(UsageGuideDto, DTO)
	//API_DTO_FIELD(Int32, id, "id", true, 0);
	API_DTO_FIELD(String, title, ZH_WORDS_GETTER("help.title"), true, "");
	//API_DTO_FIELD(String, add_time, "add_time", true, "");
	//API_DTO_FIELD(String, edit_time, "edit_time", true, "");
};

//使用说明详情
class UsageGuideDetailDto : public oatpp::DTO {
	DTO_INIT(UsageGuideDetailDto, DTO)
	//API_DTO_FIELD(Int32, id, "id", true, 0);
	API_DTO_FIELD(String, title, ZH_WORDS_GETTER("help.title"), true, "");
	API_DTO_FIELD(String, content, ZH_WORDS_GETTER("help.content"), true, "");
	//API_DTO_FIELD(String, type, "type", true, "");
	/*API_DTO_FIELD(Int32, creator, "creator", true,0);
	API_DTO_FIELD(String, add_time, "add_time", true, "");
	API_DTO_FIELD(Int32, deleted, "deleted", true, 0);
	API_DTO_FIELD(String, edit_time, "edit_time", true, "");
	API_DTO_FIELD(Int32, editor, "editor", true, 0);
	API_DTO_FIELD(Int32, state, "state", true, 0);
	API_DTO_FIELD(Int32, sort_num, "sort_num", true, 0);*/
};

/**
* 分页DTO
* 用于：GET /users 接口（分页查询）
*/

//分页展示列表信息
class UsageListDTO : public PageDTO<UsageGuideDto::Wrapper>
{
	DTO_INIT(UsageListDTO, PageDTO<UsageGuideDto::Wrapper>);
};

//分页展示列表中某一详细信息
class UsagePageDTO : public PageDTO<UsageGuideDetailDto::Wrapper>
{
	DTO_INIT(UsagePageDTO, PageDTO<UsageGuideDetailDto::Wrapper>);
};









//
////使用说明分页结果DTO
//class UsageGuidePageDto : public oatpp::DTO {
//	DTO_INIT(UsageGuidePageDto, DTO)
//	API_DTO_FIELD(Int32, total, "total", true, 0);
//	API_DTO_FIELD(Int32, pageIndex, "pageIndex", true, 0);
//	API_DTO_FIELD(Int32, pageSize, "pageSize", true, 0);
//	API_DTO_FIELD(Vector<Object<UsageGuideDto>>, list, "datalist", true, {});
//};
//



#include OATPP_CODEGEN_END(DTO)
#endif // _PARENTDTO_H_
