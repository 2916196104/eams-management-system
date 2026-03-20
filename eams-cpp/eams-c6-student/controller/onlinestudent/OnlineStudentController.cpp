#include "stdafx.h"
#include "OnlineStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

// 执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> OnlineStudentController::execExportExcel(
	const List<String>& ids)
{
	// 从数据库中查询stage为1的学员
	// ...

	// 生成 Excel
	auto buff = ExcelComponent().writeVectorToBuff("online_student",
		[&](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("onlinestudent.field.student.id") ,
				ZH_WORDS_GETTER("onlinestudent.field.student.name"),
				ZH_WORDS_GETTER("onlinestudent.field.student.mobile"),
				ZH_WORDS_GETTER("onlinestudent.field.student.sex"),
				ZH_WORDS_GETTER("onlinestudent.field.student.parent"),
				ZH_WORDS_GETTER("onlinestudent.field.student.parent-rel"),
				ZH_WORDS_GETTER("onlinestudent.field.student.school"),
				ZH_WORDS_GETTER("onlinestudent.field.student.grade"),
				ZH_WORDS_GETTER("onlinestudent.field.student.counselor"),
				ZH_WORDS_GETTER("onlinestudent.field.student.birthday")
			});
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-online-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 响应成功结果
	return response;
}

// 执行导入
StringJsonVO::Wrapper OnlineStudentController::execImportExcel(
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
	oatpp::List<OnlineAddDTO::Wrapper> exceldata = oatpp::List<OnlineAddDTO::Wrapper>::createShared();
	ExcelComponent::read(file->data(), file->size(), "online", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
		// 逐行解析解析数据
		int rn = 0;
		for (auto row : sheet->rows())
		{
			// 跳过表头
			if (rn++ == 0) continue;
			// 解析数据到 DTO
			auto dto = OnlineAddDTO::createShared();
			dto->name = row[1].to_string();         
			dto->parent = row[2].to_string();       
			dto->parentRel = row[3].to_string();    
			dto->mobile = row[4].to_string();       
			dto->counselor = row[5].to_string();    
			dto->grade = row[6].to_string();        
			dto->school = row[7].to_string();       
			dto->sex = row[10].to_string();         
			dto->age = std::stoi(row[11].to_string());            
			dto->note = row[12].to_string();        
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

	//6 保存数据
	// ...

	jvo->success(nullptr);
	return jvo;
}