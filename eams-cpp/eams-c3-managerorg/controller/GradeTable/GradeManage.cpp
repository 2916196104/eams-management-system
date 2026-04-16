#include "GradeManage.h"
#include "stdafx.h"
#include "service/GradeTable/GradeManagerService.h"

//3.4 声明了要实现

GradeManagePageJsonVO::Wrapper GradeManage::execQueryPageScore(const GradeManageQuery::Wrapper& query)
{
    // 调用 Service 查询分页数据
    auto result = GradeManagerService().listAll(query);
    // 构建响应 VO
    auto jvo = GradeManagePageJsonVO::createShared();
    jvo->success(result);
    return jvo;
}

Uint64JsonVO::Wrapper GradeManage::execSave(const GradeManageDTO::Wrapper& dto, const PayloadDTO& payload)
{
    auto jvo = Uint64JsonVO::createShared();

    // 参数校验
    std::string errmsg = dto->validate();
    if (errmsg != "")
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 调用 Service 保存成绩
    uint64_t id = GradeManagerService().saveScore(dto, payload);
    if (id > 0)
    {
        jvo->success(id);
    }
    else
    {
        jvo->fail({});
    }
    return jvo;
}

ListJsonVO<String>::Wrapper GradeManage::execRemove(const List<String>& ids)
{
    auto jvo = ListJsonVO<String>::createShared();
    // 参数校验
    if (!ids || ids->empty())
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    // 调用 Service 批量删除
    if (GradeManagerService().removeScore(ids))
    {
        jvo->success(ids);
    }
    else
    {
        jvo->fail({});
    }
    return jvo;
}

StringJsonVO::Wrapper  GradeManage::execImportScore(const std::shared_ptr<IncomingRequest>& request, const PayloadDTO& payload)
{	// 0 定义返回数据对象
//	auto jvo = StringJsonVO::createShared();
//	// 1 初始化
//	API_MULTIPART_INIT(container, reader);
//	// 2 配置读取器
//	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
//	// 3 读取数据
//	request->transferBody(&reader);
//	// 4 获取文件数据
//	API_MULTIPART_PARSE_FILE_FIELD(container, "excel", file);
//	if (!file)
//	{
//		jvo->init("not set excel file.", RS_PARAMS_INVALID);
//		return jvo;
//	}
//	// 5 解析与校验数据
//	std::string errmsg = "";
//	oatpp::List<SampleAddDTO::Wrapper> exceldata = oatpp::List<SampleAddDTO::Wrapper>::createShared();
//	ExcelComponent::read(file->data(), file->size(), "sample", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
//		// 逐行解析解析数据
//		int rn = 0;
//		for (auto row : sheet->rows())
//		{
//			// 跳过表头
//			if (rn++ == 0) continue;
//			// 解析数据到DTO
//			auto dto = SampleAddDTO::createShared();
//			dto->name = row[0].to_string();
//			dto->age = std::atoi(row[1].to_string().c_str());
//			dto->sex = row[2].to_string();
//			// 校验数据
//			errmsg = dto->validate();
//			if (errmsg != "")
//			{
//				errmsg = "row(" + std::to_string(rn) + ") data error, " + errmsg;
//				return;
//			}
//			// 数据存储到添加列表中
//			dto->setPayload(&payload);
//			exceldata->push_back(dto);
//		}
//		});
//	if (errmsg != "")
//	{
//		jvo->init(errmsg, RS_PARAMS_INVALID);
//		return jvo;
//	}
//	if (exceldata->size() == 0)
//	{
//		jvo->init("excel file no data or not excel file.", RS_PARAMS_INVALID);
//		return jvo;
//	}
//
//	// 6 保存数据
//	bool res = GradeManagerService().saveDataBatch(exceldata);
//	if (res)
//	{
//		jvo->success(nullptr);
//		return jvo;
//	}
//	jvo->fail(nullptr);
//	return jvo;
//    
    return {};
}