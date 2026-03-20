#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业查询类*/

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
	// 班级
	DTO_FIELD(String, classname);
	DTO_FIELD_INFO(classname) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.classname");
	}
	// 发布者
	DTO_FIELD(String, publisher);
	DTO_FIELD_INFO(publisher) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.publisher");
	}

};


//获取作业详情
class GetHomeworkDetailQuery : public PageQuery {
	DTO_INIT(GetHomeworkListQuery, PageQuery);

};

#include OATPP_CODEGEN_END(DTO)

#endif