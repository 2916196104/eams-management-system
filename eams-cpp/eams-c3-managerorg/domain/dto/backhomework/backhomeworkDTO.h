#ifndef _BACKHOMEWORKDTO_H_
#define _BACKHOMEWORKDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/

//获取作业列表（条件+分页）
class GetHomeworkListDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkListDTO, oatpp::DTO);
	// 查看的作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.title");
	}
	// 查看的作业班级
	DTO_FIELD(String, classname);
	DTO_FIELD_INFO(classname) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.classname");
	}
	// 查看的作业发布者
	DTO_FIELD(String, publisher);
	DTO_FIELD_INFO(publisher) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.publisher");
	}
};

class GetHomeworkListPageDTO : public PageDTO<GetHomeworkListDTO::Wrapper>
{
	DTO_INIT(GetHomeworkListPageDTO, PageDTO<GetHomeworkListDTO::Wrapper>);
};

//获取作业详情
class GetHomeworkDetailDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkDetailDTO, oatpp::DTO);

	// 查看的作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworkdetail.title");
	}
	// 查看的作业班级
	DTO_FIELD(String, classname);
	DTO_FIELD_INFO(classname) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworkdetail.classname");
	}
};

//保存作业
class SaveHomeworkDTO : public oatpp::DTO
{
	DTO_INIT(SaveHomeworkDTO, oatpp::DTO);
	// 作业ID
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.id");
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif /* _BACKHOMEWORKDTO_H_ */