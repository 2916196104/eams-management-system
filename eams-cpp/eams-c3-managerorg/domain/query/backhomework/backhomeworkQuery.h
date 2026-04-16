#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//课后作业查询类
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

//定义查询作业列表（条件+分页）描述
//GetHomeworkList，每条数据只有关键数据与唯一表示，完整数据通过详情接口获取。
//流程中显示有 作业标题，班级，发布者，提交量，页码
class GetHomeworkListQuery : public PageQuery {
	DTO_INIT(GetHomeworkListQuery, PageQuery);

	//作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.title");
	}
	// 班级名称
	DTO_FIELD(Int64, class_id);
	DTO_FIELD_INFO(class_id) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.class_id");
	}
	// 发布者
	DTO_FIELD(Int64, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.creator");
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif