#ifndef _BOARDMANAGERDTO_H_
#define _BOARDMANAGERDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*公共管理DTO类*/


class BoardManagerDTO : public oatpp::DTO
{
	DTO_INIT(BoardManagerDTO, DTO)
};

/**
 * 定义一个添加用户信息的数据传输模型
 */
class BoardAddDTO : public oatpp::DTO
{
	DTO_INIT(BoardAddDTO, DTO);
	// 公告标题
	API_DTO_FIELD_REQUIRE(String, boardTitle, ZH_WORDS_GETTER("board.field.boardTitle"),true);
	// 公告类型
	API_DTO_FIELD_REQUIRE(Int8, boardType, ZH_WORDS_GETTER("board.field.boardType"),true);
	// 文章编码（公告唯一id）
	API_DTO_FIELD_REQUIRE(String, boardAddId, ZH_WORDS_GETTER("board.field.boardAddId"),false);
	// 图片
	//API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, picture, ZH_WORDS_GETTER("board.field.idCard"), false);
	// 公告文字内容
	API_DTO_FIELD_REQUIRE(String, boardText, ZH_WORDS_GETTER("board.field.boardText"),true);
	// 公告文件
	//API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, boardFile, ZH_WORDS_GETTER("board.field.avatar"),false);
};

#include OATPP_CODEGEN_END(DTO)

#endif