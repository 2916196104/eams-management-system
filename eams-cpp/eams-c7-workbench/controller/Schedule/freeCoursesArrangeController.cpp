#include "stdafx.h"
#include "freeCoursesArrangeController.h"
#include "service/Schedule/CoursesArrange_To_Lesson/freeCoursesArrangeService.h"

StringJsonVO::Wrapper freeCoursesArrangeController::execAddSample(const freeCoursesArrangeDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	std::string errmsg = dto->validate();
	if (!errmsg.empty())
	{
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据新增
	try
	{
		// 执行数据新增,调用service层接口进行数据新增
		dto->setPayload(&payload);
		uint64_t ans = FreeCoursesArrangeService().saveFreeCoursesArrange(dto);
		std::ostringstream oss;
		oss << ZH_WORDS_GETTER("controller.message.add_success") << ans << ZH_WORDS_GETTER("controller.message.add_count_suffix");
		std::string successMsg = oss.str();
		//返回排课成功的次数
		if (ans != 0)
		{
			jvo->success(successMsg);
		}
		else
		{
			jvo->fail(ZH_WORDS_GETTER("controller.message.add_failed"));
		}
	}
	catch (const std::exception& e)
	{
		jvo->init(e.what(), RS_FAIL);
	}

	// 响应结果
	return jvo;
}
