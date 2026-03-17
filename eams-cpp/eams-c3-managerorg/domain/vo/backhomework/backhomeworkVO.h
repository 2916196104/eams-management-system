#ifndef __BACKHOMEWORK_VO_H__
#define __BACKHOMEWORK_VO_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业视图类*/

class BackhomeworkVO : public oatpp::DTO {
	DTO_INIT(BackhomeworkVO, oatpp::DTO)

//----------------------获取作业提交列表（条件+分页）------------------------------
	// 序号（分页后的行号，从 1 开始）
	DTO_FIELD(UInt64, serialNo);
	DTO_FIELD_INFO(serialNo) {
		info->description = ZH_WORDS_GETTER("backhomework.field.serialNo");
	}

	// 提交人（学生姓名）
	DTO_FIELD(String, studentName);
	DTO_FIELD_INFO(studentName) {
		info->description = ZH_WORDS_GETTER("backhomework.field.studentName");
	}

	// 提交内容
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("backhomework.field.content");
	}

	// 提交时间（时间戳）
	DTO_FIELD(Int64, submitTime);
	DTO_FIELD_INFO(submitTime) {
		info->description = ZH_WORDS_GETTER("backhomework.field.submitTime");
	}

	// 点评人（教师姓名）
	DTO_FIELD(String, teacherName);
	DTO_FIELD_INFO(teacherName) {
		info->description = ZH_WORDS_GETTER("backhomework.field.teacherName");
	}

	// 点评得分
	DTO_FIELD(Float32, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("backhomework.field.score");
	}

	// 点评内容（评语）
	DTO_FIELD(String, teacherComment);
	DTO_FIELD_INFO(teacherComment) {
		info->description = ZH_WORDS_GETTER("backhomework.field.teacherComment");
	}

	DTO_FIELD(List<BackhomeworkVO::Wrapper>, list);
	DTO_FIELD(Int64, total);
	DTO_FIELD(UInt64, pageIndex) = 1;
	DTO_FIELD(UInt64, pageSize) = 10;
};

#include OATPP_CODEGEN_END(DTO)

#endif