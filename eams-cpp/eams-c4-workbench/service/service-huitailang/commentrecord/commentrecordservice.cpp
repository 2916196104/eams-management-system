#include "stdafx.h"
#include "commentrecordservice.h"
#include "../../../dao/dao-huitailang/commentrecord/commentrecordDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件

CommentrecordPageDTO::Wrapper CommentrecordService::listAll(const CommentrecordQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = CommentrecordPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	CommentrecordDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}
	//cout << count << endl;
	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<CommentrecordViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	//cout << result.size() << endl;
	for (CommentrecordViewDO& sub : result)
	{
		auto dto = CommentrecordDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, studentName, StudentName, commentText, Content, commentDate, AddTime, score, Score1);
		if (sub.getAnonymity() == 1)
		{
			dto->studentName = ZH_WORDS_GETTER("comment.anonymityname");
			//dto->stuname = oatpp::DTO::String("匿名用户");
		}
		pages->addData(dto);
	}
	
	return pages;
}

