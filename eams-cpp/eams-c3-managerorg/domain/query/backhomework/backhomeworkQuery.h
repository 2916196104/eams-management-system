#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业查询类*/

//获取作业列表（条件+分页）
class GetHomeworkListQuery : public PageQuery{
	DTO_INIT(GetHomeworkListQuery, PageQuery);

};

//获取作业详情
class GetHomeworkDetailQuery : public PageQuery {
	DTO_INIT(GetHomeworkListQuery, PageQuery);

};

#include OATPP_CODEGEN_END(DTO)

#endif