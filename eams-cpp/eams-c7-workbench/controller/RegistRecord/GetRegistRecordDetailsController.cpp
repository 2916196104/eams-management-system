#include"stdafx.h"
#include"GetRegistRecordDetailsController.h"


RegistRecordJsonVO::Wrapper GetRegistRecordDetailsController::execQueryById(const String& id) {
	auto jvo = RegistRecordJsonVO::createShared();
	//参数校验
	if (!id) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	//执行数据新增
	auto res = RegistRecordService().getById(id.getValue(""));
	// 【新增打印】
	if (res) {
		std::cout << "[Step 1] Service层：查询成功，学生姓名 = " << res->studentName.getValue("未知") << std::endl;
	}
	else {
		std::cout << "[Step 1] Service层：查询失败，DTO为空！输入ID为: " << id.getValue("NULL") << std::endl;
	}
	jvo->success(res);
	// 在 return jvo; 之前加入：
	if (jvo && jvo->data) {
		std::cout << "[Debug] jvo->data 存在，学生姓名: " << jvo->data->studentName.getValue("NULL") << std::endl;
	}
	else {
		std::cout << "[Debug] 警告：jvo->data 是空的！" << std::endl;
	}
	//响应结果
	return jvo;
}