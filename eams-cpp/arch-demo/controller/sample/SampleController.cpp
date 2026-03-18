/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:58:42

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "SampleController.h"
#include "../../service/sample/SampleService.h"
#include "../../domain/bo/PdfReportBO.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

SamplePageJsonVO::Wrapper SampleController::execQuerySample(const SampleQuery::Wrapper& query)
{
	// 查询数据
	auto result = SampleService().listAll(query);
	// 响应结果
	auto jvo = SamplePageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

SampleJsonVO::Wrapper SampleController::execQueryById(const String& id)
{
	// 定义返回数据对象
	auto jvo = SampleJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据新增
	auto res = SampleService().getById(id.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> SampleController::execExportSample(const SampleQuery::Wrapper& query)
{
	// 查询数据
	auto result = SampleService().listAll(query);

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("sample",
		[result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("sample.field.id") ,
				ZH_WORDS_GETTER("sample.field.name") ,
				ZH_WORDS_GETTER("sample.field.age") ,
				ZH_WORDS_GETTER("sample.field.sex")
				});
			// 写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->id);
				ex->setCellValue(row, col++, item->name);
				ex->setCellValue(row, col++, std::to_string(item->age));
				ex->setCellValue(row, col, item->sex);
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 影响成功结果
	return response;
}

StringJsonVO::Wrapper SampleController::execExportSamplePdf(const SampleQuery::Wrapper& query)
{
	// 查询数据
	auto result = SampleService().listAll(query);
	// 绘制PDF
	PdfComponent pdf;
	OatppAccessor<SampleDTO::Wrapper> dataAccessor(result->rows);
	pdf.drawWithTemplate("tpl/sample-pdf-report.yml", "simple-pdf-report", &dataAccessor);
	// 保存PDF
	auto data = pdf.saveDocToMem();
	auto buff = reinterpret_cast<const char*>(data.data());
	// 转换成base64
	auto base64Str = jwt::base64_encode(buff, data.size());
	// 响应数据
	auto jvo = StringJsonVO::createShared();
	jvo->success(base64Str);
	return jvo;
}

StringJsonVO::Wrapper SampleController::execImportSample(std::shared_ptr<IncomingRequest> request, const PayloadDTO& payload)
{
	// 0 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 1 初始化
	API_MULTIPART_INIT(container, reader);
	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	// 3 读取数据
	request->transferBody(&reader);
	// 4 获取文件数据
	API_MULTIPART_PARSE_FILE_FIELD(container, "excel", file);
	if (!file)
	{
		jvo->init("not set excel file.", RS_PARAMS_INVALID);
		return jvo;
	}
	// 5 解析与校验数据
	std::string errmsg = "";
	oatpp::List<SampleAddDTO::Wrapper> exceldata = oatpp::List<SampleAddDTO::Wrapper>::createShared();
	ExcelComponent::read(file->data(), file->size(), "sample", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
		// 逐行解析解析数据
		int rn = 0;
		for (auto row : sheet->rows())
		{
			// 跳过表头
			if (rn++ == 0) continue;
			// 解析数据到DTO
			auto dto = SampleAddDTO::createShared();
			dto->name = row[0].to_string();
			dto->age = std::atoi(row[1].to_string().c_str());
			dto->sex = row[2].to_string();
			// 校验数据
			errmsg = dto->validate();
			if (errmsg != "")
			{
				errmsg = "row(" + std::to_string(rn) + ") data error, " + errmsg;
				return;
			}
			// 数据存储到添加列表中
			dto->setPayload(&payload);
			exceldata->push_back(dto);
		}
		});
	if (errmsg != "")
	{
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}
	if (exceldata->size() == 0)
	{
		jvo->init("excel file no data or not excel file.", RS_PARAMS_INVALID);
		return jvo;
	}

	// 6 保存数据
	bool res = SampleService().saveDataBatch(exceldata);
	if (res)
	{
		jvo->success(nullptr);
		return jvo;
	}
	jvo->fail(nullptr);
	return jvo;
}

StringJsonVO::Wrapper SampleController::execAddSample(const SampleAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	std::string errmsg = dto->validate();
	if (errmsg != "")
	{
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据新增
	dto->setPayload(&payload);
	std::string id = SampleService().saveData(dto);
	if (id != "") {
		jvo->success(id);
	}
	else
	{
		jvo->fail("");
	}
	//响应结果
	return jvo;
}

StringJsonVO::Wrapper SampleController::execModifySample(const SampleDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据修改
	dto->setPayload(&payload);
	if (SampleService().updateData(dto)) {
		jvo->success(dto->id);
	}
	else
	{
		jvo->fail(dto->id);
	}
	// 响应结果
	return jvo;
}

ListJsonVO<String>::Wrapper SampleController::execRemoveSample(const List<String>& ids)
{
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据删除
	if (SampleService().removeData(ids)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}
	// 响应结果
	return jvo;
}

SampleJsonVO::Wrapper SampleController::execQueryOne(const String& id, const PayloadDTO& payload)
{
	// 创建客户端对象
	API_CLIENT_CREATE(ac, om, SampleApiClient, "sample-api");
	// 构建凭证
	std::string token = PayloadDTO::getTokenPrefix() + payload.getToken();
	// 返回查询结果
	return ac->queryById(token, id)->readBodyToDto<SampleJsonVO::Wrapper>(om);
}

SamplePageJsonVO::Wrapper SampleController::execQueryAll(const SampleQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 创建客户端对象
	API_CLIENT_CREATE(ac, om, SampleApiClient, "sample-api");
	// 构建凭证
	std::string token = PayloadDTO::getTokenPrefix() + payload.getToken();
	// 返回查询结果
	return ac->queryAll(token, query->pageIndex, query->pageSize, URIUtil::urlEncode(query->name))->readBodyToDto<SamplePageJsonVO::Wrapper>(om);
}
