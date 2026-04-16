#include "Homework.h"
#include "stdafx.h"
#include "../../domain/vo/backhomework/backhomeworkVO.h"
#include "../../service/backhomework/HomeworkService.h"

//获取作业列表（条件+分页）
//修改前端该传入的数据，在query中
//修改后端该传出的数据，在Service中ZO_STAR_DOMAIN_DO_TO_DTO，DAO中sql编写，VO，Mapper
GetHomeworkListJsonVO::Wrapper Homework::execGetHomeworkList(const GetHomeworkListQuery::Wrapper& query) {
	// 查询数据
	auto result = HomeworkService().gethomeworklist(query);
	// 响应结果
	auto jvo = GetHomeworkListJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

//获取作业详情
GetHomeworkDetailJsonVO::Wrapper Homework::execGetHomeworkDetail(UInt64 id) {
	// 定义返回数据对象
	auto jvo = GetHomeworkDetailJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行
	auto res = HomeworkService().gethomeworkdetail(id.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
}

//保存作业
StringJsonVO::Wrapper Homework::execSaveHomework(const SaveHomeworkDTO::Wrapper& dto, const PayloadDTO& payload) {
	
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	std::string errmsg = dto->validate();
	if (errmsg != "")
	{
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行
	dto->setPayload(&payload);
	bool id = HomeworkService().saveHomework(dto);
	if (id == true) {jvo->success("success");}
	else{jvo->fail("");}

	//响应结果
	return jvo;
}

ListJsonVO<String>::Wrapper Homework::executeDelHomework(const DeleteHomework::Wrapper& dto)
{
	(void)dto; // TODO: 实现实际删除逻辑

	auto rsp = ListJsonVO<String>::createShared();
	auto emptyData = oatpp::List<String>::createShared(); // 返回空列表占位
	rsp->success(emptyData);                               // success 需要传入列表数据参数
	return rsp;
}