#include "stdafx.h"
#include "commentrecordcontroller.h"
#include "../../service/service-huitailang/commentrecord/commentrecordservice.h"

CommentrecordsonVO::Wrapper getcommentrecord::executeQueryComment(const CommentrecordQuery::Wrapper& query)
{
	//查询数据
	auto result = CommentrecordService().listAll(query);
	//响应结果
	auto jvo = CommentrecordsonVO::createShared();
	jvo->success(result);
	return jvo;
}