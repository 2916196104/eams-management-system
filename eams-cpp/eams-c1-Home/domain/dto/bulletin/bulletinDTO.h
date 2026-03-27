#pragma once
#ifndef _BULLETINDTO_H_
#define _BULLETINDTO_H_
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 公告提醒数据传输对象
 */

 // 获取显示通知公告
class titleDTO : public oatpp::DTO
{
	DTO_INIT(titleDTO, DTO);
	// 添加时间
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("home.bulletin.field.add_time"));
	// 编辑时间
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("bulletin.field.edit_time"));
	// 创建者
	API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("bulletin.field.creator"));
	// 编辑者
	API_DTO_FIELD_DEFAULT(Int64, editor, ZH_WORDS_GETTER("bulletin.field.editor"));
	// 逻辑删除标识
	API_DTO_FIELD_DEFAULT(Int8, deleted, ZH_WORDS_GETTER("bulletin.field.deleted"));
	// 主键ID
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("bulletin.field.id"));
	// 标题
	API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("bulletin.field.title"));
	// 封面图
	API_DTO_FIELD_DEFAULT(String, cover, ZH_WORDS_GETTER("bulletin.field.cover"));
	// 内容
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("bulletin.field.content"));
	// 广告类型
	API_DTO_FIELD_DEFAULT(Int8, type, ZH_WORDS_GETTER("bulletin.field.type"));
	// 状态
	API_DTO_FIELD_DEFAULT(Int8, state, ZH_WORDS_GETTER("bulletin.field.state"));
	// 排序号
	API_DTO_FIELD_DEFAULT(Int32, sortNum, ZH_WORDS_GETTER("bulletin.field.sort_num"));
};

//获取所有公告（分页）
//class  listDTO : public titleDTO
//{
//	DTO_INIT(listDTO, titleDTO);
//};

class listPageDTO : public PageDTO<titleDTO::Wrapper>
{
	DTO_INIT(listPageDTO, PageDTO<titleDTO::Wrapper>);
};

// 获取显示通知公告
class redDTO : public oatpp::DTO
{
	DTO_INIT(redDTO, DTO);
	// 成绩未读数
	API_DTO_FIELD_DEFAULT(Int32, grade_count, ZH_WORDS_GETTER("bulletin.field.grade_count"));
	// 点评记录未读数
	API_DTO_FIELD_DEFAULT(Int32, evaluate_count, ZH_WORDS_GETTER("bulletin.field.evaluate_count"));
	// 作业未读数
	API_DTO_FIELD_DEFAULT(Int32, homework_count, ZH_WORDS_GETTER("bulletin.field.homework_count"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_BULLETINDTO_H_