#include "stdafx.h"
#include "IntendedStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

// 执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> IntendedStudentController::execExportExcel(
	const ExcelQuery::Wrapper& query)
{
	// 生成 Excel
	auto buff = ExcelComponent().writeVectorToBuff("intended_student",
		[&](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("common.field.student.id") ,
				ZH_WORDS_GETTER("common.field.student.name") ,
				ZH_WORDS_GETTER("common.field.student.age") ,
				ZH_WORDS_GETTER("common.field.student.sex")
			});

			// 写入数据
			ex->setCellValue(2, 1, query->name ? query->name : "");
			ex->setCellValue(2, 2, query->sex ? query->sex : "");
			ex->setCellValue(2, 3, query->age ? std::to_string(query->age) : "");
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
	return response;
}

// 执行导入
StringJsonVO::Wrapper IntendedStudentController::execImportExcel(
	std::shared_ptr<IncomingRequest> request,
	const PayloadDTO& payload)
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
	oatpp::List<AddDTO::Wrapper> exceldata = oatpp::List<AddDTO::Wrapper>::createShared();
	ExcelComponent::read(file->data(), file->size(), "sample", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
		// 逐行解析解析数据
		int rn = 0;
		for (auto row : sheet->rows())
		{
			// 跳过表头
			if (rn++ == 0) continue;
			// 解析数据到DTO
			auto dto = AddDTO::createShared();
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

	jvo->success(nullptr);
	return jvo;
}