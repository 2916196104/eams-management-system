#ifndef _BACKHOMEWORKDTO_H_
#define _BACKHOMEWORKDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class DeleteHomework : public oatpp::DTO
{
	DTO_INIT(DeleteHomework, DTO)

public:
	// 作业ID列表（必填）
	API_DTO_FIELD_REQUIRE(oatpp::List<oatpp::UInt64>, homeworkIds, ZH_WORDS_GETTER("Homework.vo.homeworkIds"), true)
	// 删除类型：0-逻辑删除（默认） 1-物理删除
	DTO_FIELD(oatpp::Int32, deleteType) = 0;
	DTO_FIELD_INFO(deleteType) {
		info->description = ZH_WORDS_GETTER("Homework.vo.deleteType");
	}
};

//获取作业提交列表DTO类
class Backhomework : public oatpp::DTO
{
	DTO_INIT(Backhomework, DTO)

public:
	// 序号（可选）
	DTO_FIELD(oatpp::UInt32, index);
	DTO_FIELD_INFO(index) {
		info->description = ZH_WORDS_GETTER("Common.index");
	}

	// 提交人姓名
	DTO_FIELD(oatpp::String, submitterName);
	DTO_FIELD_INFO(submitterName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitterName");
	}

	// 提交内容（如文件URL、文本等）
	DTO_FIELD(oatpp::String, submitContent);
	DTO_FIELD_INFO(submitContent) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitContent");
	}

	// 提交时间（ISO8601 格式字符串，如 "2025-03-18T10:30:00Z"）
	DTO_FIELD(oatpp::String, submitTime);
	DTO_FIELD_INFO(submitTime) {
		info->description = ZH_WORDS_GETTER("Homework.vo.submitTime");
	}

	// 点评人姓名（可能为空）
	DTO_FIELD(oatpp::String, reviewerName);
	DTO_FIELD_INFO(reviewerName) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewerName");
	}

	// 点评得分（-1 表示未评分）
	DTO_FIELD(oatpp::Float32, score) = -1.0f;
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("Homework.vo.score");
	}

	// 点评内容
	DTO_FIELD(oatpp::String, reviewComment);
	DTO_FIELD_INFO(reviewComment) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewComment");
	}
};

/**
 * 点评作业DTO类
 */
class ReviewHomework : public oatpp::DTO {
	DTO_INIT(ReviewHomework, DTO)

public:
	// 作业ID列表（必填）
	API_DTO_FIELD_REQUIRE(oatpp::List<oatpp::UInt64>, homeworkIds, ZH_WORDS_GETTER("Homework.field.homeworkIds"), true)
	// 删除类型：0-逻辑删除（默认） 1-物理删除
	DTO_FIELD(oatpp::Int32, deleteType) = 0;
	DTO_FIELD_INFO(deleteType) {
		info->description = ZH_WORDS_GETTER("Homework.field.deleteType");
	}

	// 学生作业ID（必填）
	API_DTO_FIELD_REQUIRE(oatpp::UInt64, homeworkId, ZH_WORDS_GETTER("ReviewHomework.stuHomeworkId"), true)
	// 点评得分（与VO中的score保持一致）
	DTO_FIELD(oatpp::Float32, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("Homework.vo.score");
	}
	// 点评内容（与VO中的reviewComment保持一致）
	DTO_FIELD(oatpp::String, reviewComment);
	DTO_FIELD_INFO(reviewComment) {
		info->description = ZH_WORDS_GETTER("Homework.vo.reviewComment");
	}
};

//课后作业DTO类
//获取作业列表（条件+分页）
// 前端传来的数据有作业标题，班级ID，发布者，页码，每页条数，在query中
// 后端返回的数据有作业id，班级，标题，发布者，在DTO中，用于给VO组装数据
class GetHomeworkListDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkListDTO, oatpp::DTO);

	// 查看的作业id
	DTO_FIELD(Int64, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.id");
	}
	// 查看的作业班级
	DTO_FIELD(Int64, classId);
	DTO_FIELD_INFO(classId) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.class_id");
	}
	// 查看的作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.title");
	}
	// 查看的作业发布者
	DTO_FIELD(Int64, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.creator");
	}
	// 查看的作业创建时间
	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.add_time");
	}
};


class GetHomeworkListPageDTO : public PageDTO<GetHomeworkListDTO::Wrapper>
{
	DTO_INIT(GetHomeworkListPageDTO, PageDTO<GetHomeworkListDTO::Wrapper>);
};

//获取作业详情
// 前端传来的数据有作业ID，在query中
// 后端返回的数据有班级,标题，内容，在DTO中，用于给VO组装数据
class GetHomeworkDetailDTO : public oatpp::DTO
{
	DTO_INIT(GetHomeworkDetailDTO, oatpp::DTO);

	// 查看的作业班级
	DTO_FIELD(Int64, classId);
	DTO_FIELD_INFO(classId) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.class_id");
	}
	// 查看的作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.title");
	}
	// 查看的作业标题
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("homework.gethomeworklist.content");
	}
};

//保存作业，新增作业与修改作业
// 同时要给homework表与homeworkrecord表一起写数据
//前端传来的数据有，id（有id是修改，无id是新增），标题，内容，班级ID，创建者/修改人，新增时要传student_id
// 后端生成的数据有作业ID，新增时间/修改时间
class SaveHomeworkDTO : public oatpp::DTO
{
	DTO_INIT(SaveHomeworkDTO, oatpp::DTO);

	// 作业id，新增作业时id不传，修改作业时要作业id
	DTO_FIELD(Int64, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.id");
	}
	// 班级
	DTO_FIELD(Int64, classId);
	DTO_FIELD_INFO(classId) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.class_id");
	}
	// 作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.title");
	}
	// 作业内容
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.content");
	}
	// 创建人，新增作业时要创建人
	DTO_FIELD(Int64, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.creator");
	}
	// 编辑人，修改作业时要编辑人
	DTO_FIELD(Int64, editor);
	DTO_FIELD_INFO(editor) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.editor");
	}
	DTO_FIELD(Int64, studentid);
	DTO_FIELD_INFO(studentid) {
		info->description = ZH_WORDS_GETTER("homework.savehomework.studentid");
	}

	// 关联一个PayloadDTO负载数据对象，在controller层调用
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	//数据校验,在controller层调用validate方法进行数据校验,返回空字符串表示校验通过,否则返回错误信息
	std::string validate()
	{
		//if (id < 0)     // ID可以不存在，存在的话是不能为非负数
		//	return "id invalidate.";
		if (!classId || classId < 0)     // 班级ID必须存在且为非负数
			return "classId invalidate.";
		if (!title || title->empty())    // 作业标题必须存在且非空
			return "title invalidate.";
		if (!content || content->empty()) // 作业内容必须存在且非空
			return "content invalidate.";
		return "";
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif /* _BACKHOMEWORKDTO_H_ */