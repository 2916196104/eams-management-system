#ifndef __BACKHOMEWORK_VO_H__
#define __BACKHOMEWORK_VO_H__

#include "domain/GlobalInclude.h"
#include "../../GlobalInclude.h"
#include "../../dto/backhomework/backhomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*删除作业视图类*/
class DeleteHomeworkVO : public oatpp::DTO {
	DTO_INIT(DeleteHomeworkVO, oatpp::DTO);

public:
	// 成功删除的作业数量
	DTO_FIELD(oatpp::UInt64, successCount);
	DTO_FIELD_INFO(successCount) {
		info->description = ZH_WORDS_GETTER("Homework.delete.successCount");
	}
	// 删除失败的作业ID列表（无失败则为空数组）
	DTO_FIELD(oatpp::List<oatpp::UInt64>, failIds);
	DTO_FIELD_INFO(failIds) {
		info->description = ZH_WORDS_GETTER("Homework.delete.failIds");
	}
	// 删除类型（回显：0-逻辑删除，1-物理删除）
	DTO_FIELD(oatpp::Int32, deleteType) = 0;
	DTO_FIELD_INFO(deleteType) {
		info->description = ZH_WORDS_GETTER("Homework.vo.deleteType");
	}
};

/*?κ?????????*/
class BackhomeworkVO : public oatpp::DTO {
	DTO_INIT(BackhomeworkVO, oatpp::DTO);

public:
	// ???????????к???? 1 ?????
	DTO_FIELD(UInt64, serialNo);
	DTO_FIELD_INFO(serialNo) {
		info->description = ZH_WORDS_GETTER("Homework.vo.serialNo");
	}
	// ??????????????
	DTO_FIELD(String, studentName);
	DTO_FIELD_INFO(studentName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitterName");
	}
	// ??????
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitContent");
	}
	// ???????????
	DTO_FIELD(Int64, submitTime);
	DTO_FIELD_INFO(submitTime) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitTime");
	}
	// ??????
	DTO_FIELD(String, teacherName);
	DTO_FIELD_INFO(teacherName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewerName");
	}
	// ?????÷?
	DTO_FIELD(Float32, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("Homework.vo.score");
	}
	// ?????????????
	DTO_FIELD(String, teacherComment);
	DTO_FIELD_INFO(teacherComment) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewComment");
	}

	// ????б?????
	DTO_FIELD(oatpp::List<BackhomeworkVO::Wrapper>, list);
	DTO_FIELD_INFO(list) {
		info->description = ZH_WORDS_GETTER("Homework.vo.list");
	}

	// 总记录数
	DTO_FIELD(oatpp::Int64, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("Homework.vo.total");
	}

	// 当前页码（默认第1页）
	DTO_FIELD(oatpp::UInt64, pageIndex) = 1;
	DTO_FIELD_INFO(pageIndex) {
		info->description = ZH_WORDS_GETTER("Homework.vo.pageIndex");
	}

	// 每页大小（默认10条）
	DTO_FIELD(oatpp::UInt64, pageSize) = 10;
	DTO_FIELD_INFO(pageSize) {
		info->description = ZH_WORDS_GETTER("Homework.vo.pageSize");
	}
};


//获取作业列表（条件+分页）
//返回了id（虽然没看的，但下一步获取作业详情要id）,标题，班级，提交量（数据库没这个功能），发布人，发布时间
class GetHomeworkListJsonVO : public JsonVO<GetHomeworkListPageDTO::Wrapper> {
	DTO_INIT(GetHomeworkListJsonVO, JsonVO<GetHomeworkListPageDTO::Wrapper>);

	DTO_FIELD(oatpp::Int64, id);
	DTO_FIELD(oatpp::String, title);
	DTO_FIELD(oatpp::Int64, class_id);
	DTO_FIELD(oatpp::Int64, creator);
	DTO_FIELD(oatpp::String, addtime);
};

//获取作业详情
//返回了内容
class GetHomeworkDetailJsonVO : public JsonVO<GetHomeworkDetailDTO::Wrapper> {
	DTO_INIT(GetHomeworkDetailJsonVO, JsonVO<GetHomeworkDetailDTO::Wrapper>);

	//是要回标题和班级等信息？
	DTO_FIELD(oatpp::String, title);
	DTO_FIELD(oatpp::Int64,class_id);
	DTO_FIELD(oatpp::String, content);
};

//保存作业
//但好像什么都没有返回，暂时先放个id吧
class SaveHomeworkJsonVO : public JsonVO<GetHomeworkDetailDTO::Wrapper> {
	DTO_INIT(SaveHomeworkJsonVO, JsonVO<GetHomeworkDetailDTO::Wrapper>);

	DTO_FIELD(oatpp::Int64, id);
};

#include OATPP_CODEGEN_END(DTO)

#endif