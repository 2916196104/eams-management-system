#ifndef __BACKHOMEWORK_VO_H__
#define __BACKHOMEWORK_VO_H__

#include "domain/GlobalInclude.h"

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

/*课后作业视图类*/
class BackhomeworkVO : public oatpp::DTO {
	DTO_INIT(BackhomeworkVO, oatpp::DTO);

public:
	// 序号（分页后的行号，从 1 开始）
	DTO_FIELD(UInt64, serialNo);
	DTO_FIELD_INFO(serialNo) {
		info->description = ZH_WORDS_GETTER("Homework.vo.serialNo");
	}
	// 提交人（学生姓名）
	DTO_FIELD(String, studentName);
	DTO_FIELD_INFO(studentName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitterName");
	}
	// 提交内容
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitContent");
	}
	// 提交时间（时间戳）
	DTO_FIELD(Int64, submitTime);
	DTO_FIELD_INFO(submitTime) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitTime");
	}
	// 点评人
	DTO_FIELD(String, teacherName);
	DTO_FIELD_INFO(teacherName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewerName");
	}
	// 点评得分
	DTO_FIELD(Float32, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("Homework.vo.score");
	}
	// 点评内容（评语）
	DTO_FIELD(String, teacherComment);
	DTO_FIELD_INFO(teacherComment) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewComment");
	}

	// 作业列表数据
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

#include OATPP_CODEGEN_END(DTO)

#endif