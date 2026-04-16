#include "stdafx.h"
#include "repeatCoursesArrangeController.h"
#include "service/Schedule/CoursesArrange_To_Lesson/repeatCoursesArrangeService.h"

//接收web的执行后，调用service层接口进行数据新增，根据执行结果返回对应响应结果
StringJsonVO::Wrapper repeatCoursesArrangeController::execAddSample(const repeatCoursesArrangeDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	string errmsg = dto->validate();	//检验参数是否合法
	if (errmsg != "")
	{// 参数校验失败，返回错误消息
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	try
	{
		// 执行数据新增,调用service层接口进行数据新增
		dto->setPayload(&payload);	//payload是凭证生成的Payload负载对象，包含用户身份信息，含用户id，用户名等		
		//控制器通过设置负载对象，将用户id传递给service层
		uint64_t ans = RepeatCoursesArrangeService().saveRepeatCoursesArrange(dto);
		std::ostringstream oss;
		oss << ZH_WORDS_GETTER("controller.message.add_success") << ans << ZH_WORDS_GETTER("controller.message.add_count_suffix");
		std::string successMsg = oss.str();
		//返回排课成功的次数
		if (ans != 0)
		{//新增数据成功，返回成功的次数
			jvo->success(successMsg);		//设置成功消息并且设置jvo.data为dto
		}
		else
		{//新增数据失败，返回失败消息
			jvo->fail(ZH_WORDS_GETTER("controller.message.add_failed"));
		}
	}
	catch (const std::exception& e)
	{// 捕获异常，返回错误消息
		jvo->init(e.what(), RS_FAIL);
	}

	// 响应结果
	return jvo;
}
