#ifndef _BOARDMANAGERDTO_H_
#define _BOARDMANAGERDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//公共管理DTO类


class BoardManagerDTO : public oatpp::DTO
{
	DTO_INIT(BoardManagerDTO, DTO);
};

//定义一个添加公告信息的数据传输模型
class BoardUpdateDTO : public oatpp::DTO
{
	DTO_INIT(BoardUpdateDTO, DTO);
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

//定义一个添加公告信息的数据传输模型
class BoardAddDTO : public oatpp::DTO
{
	DTO_INIT(BoardAddDTO, DTO);
	// 公告标题
	API_DTO_FIELD_REQUIRE(String, boardTitle, ZH_WORDS_GETTER("board.field.boardTitle"),true);
	// 公告类型
	//API_DTO_FIELD_REQUIRE(Int8, boardType, ZH_WORDS_GETTER("board.field.boardType"),true);
	// 文章编码（公告唯一id）
	API_DTO_FIELD_REQUIRE(UInt64, boardAddId, ZH_WORDS_GETTER("board.field.boardAddId"),false);
	// 图片
	//API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, picture, ZH_WORDS_GETTER("board.field.idCard"), false);
	// 公告文字内容
	API_DTO_FIELD_REQUIRE(String, boardText, ZH_WORDS_GETTER("board.field.boardText"),true);
	// 公告文件
	//API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, boardFile, ZH_WORDS_GETTER("board.field.avatar"),false);
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

public:
	// 数据校验
	std::string validate()
	{
		if (!boardTitle || boardTitle->empty())
			return "boardTitle invalidate.";
		if (boardAddId && boardAddId<0)
			return "boardAddId invalidate.";
		if (!boardText || boardText->empty())
			return "boardText invalidate.";
		return "";
	}
};

class GetBoardDetailDTO : public oatpp::DTO
{
	DTO_INIT(GetBoardDetailDTO, DTO);
	// 查看公告标题
	DTO_FIELD(String, boardtitle);
	DTO_FIELD_INFO(boardtitle) {
		info->description = ZH_WORDS_GETTER("board.field.boardTitle");
	}
	// 查看公告内容
	DTO_FIELD(String, boardtext);
	DTO_FIELD_INFO(boardtext) {
		info->description = ZH_WORDS_GETTER("board.field.boardText");
	}
	// 查看公告类型
	DTO_FIELD(String, boardtype);
	DTO_FIELD_INFO(boardtype) {
		info->description = ZH_WORDS_GETTER("board.field.boardType");
	}
	// 查看公告状态
	DTO_FIELD(String, boardstatus);
	DTO_FIELD_INFO(boardstatus) {
		info->description = ZH_WORDS_GETTER("board.field.boardStatus");
	}

};

class BoardDTO : public BoardAddDTO
{
	DTO_INIT(BoardDTO, BoardAddDTO);
	// 公告状态
	//API_DTO_FIELD_REQUIRE(String, boardStatus, ZH_WORDS_GETTER("board.field.boardStatus"), true);
	// 公告发布者名称
	//API_DTO_FIELD_REQUIRE(String, boardPublisherName, ZH_WORDS_GETTER("board.field.boardPublisherName"), true);
	// 公告发布者id
	API_DTO_FIELD_REQUIRE(UInt64, boardPublisherId, ZH_WORDS_GETTER("board.field.boardPublisherId"), false);
	// 公告编辑者id
	API_DTO_FIELD_REQUIRE(UInt64, boardEditorId, ZH_WORDS_GETTER("board.field.boardEditorId"), false);
	// 公告发布时间
	API_DTO_FIELD_REQUIRE(String, boardTime, ZH_WORDS_GETTER("board.field.boardTime"), true);
	// 公告修改时间
	API_DTO_FIELD_REQUIRE(String, editTime, ZH_WORDS_GETTER("board.field.editTime"), true);
	// 是否删除
	API_DTO_FIELD_REQUIRE(Int8, deleted, ZH_WORDS_GETTER("board.field.deleted"), true);
	// 阅读次数
	API_DTO_FIELD_REQUIRE(Int32, viewNum, ZH_WORDS_GETTER("board.field.viewNum"), false);
};

/**
 * 定义一个公告信息分页传输对象
 */
class BoardPageDTO : public PageDTO<BoardDTO::Wrapper>
{
	DTO_INIT(BoardPageDTO, PageDTO<BoardDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif