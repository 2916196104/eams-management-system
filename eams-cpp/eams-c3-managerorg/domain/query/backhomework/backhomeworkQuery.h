#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "domain/GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业查询类*/
class BackhomeworkQuery : public PageQuery
{
	DTO_INIT(BackhomeworkQuery, PageQuery)

	// 学生ID（选填，用于筛选特定学生）
	API_DTO_FIELD_DEFAULT(oatpp::UInt64, studentId, ZH_WORDS_GETTER("Homework.query.studentId"))
	// 提交状态：-1-全部（默认），0-未提交，1-已提交，2-已批改
	DTO_FIELD(oatpp::Int32, status) = -1;
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("Homework.query.status");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif