#include "stdafx.h"
#include "IntendedStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

// 执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> IntendedStudentController::execExportExcel(
	const IntendExcelQuery::Wrapper& query)
{
	// 从数据库中查询stage为0的学员
	// ...

	// 生成 Excel
	auto buff = ExcelComponent().writeVectorToBuff("intended_student",
		[&](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("intendedstudent.field.student.id") ,
				ZH_WORDS_GETTER("intendedstudent.field.student.name"),
				ZH_WORDS_GETTER("intendedstudent.field.student.mobile"),
				ZH_WORDS_GETTER("intendedstudent.field.student.sex"),
				ZH_WORDS_GETTER("intendedstudent.field.student.parent"),
				ZH_WORDS_GETTER("intendedstudent.field.student.parent-rel"),
				ZH_WORDS_GETTER("intendedstudent.field.student.school"),
				ZH_WORDS_GETTER("intendedstudent.field.student.grade"),
				ZH_WORDS_GETTER("intendedstudent.field.student.counselor"),
				ZH_WORDS_GETTER("intendedstudent.field.student.birthday")
				});
		});
		
	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-intended-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	
	// 响应成功结果
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
	oatpp::List<IntendAddDTO::Wrapper> exceldata = oatpp::List<IntendAddDTO::Wrapper>::createShared();
	ExcelComponent::read(file->data(), file->size(), "intended", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
		// 逐行解析解析数据
		int rn = 0;
		for (auto row : sheet->rows())
		{
			// 跳过表头
			if (rn++ == 0) continue;
			// 解析数据到DTO
			auto dto = IntendAddDTO::createShared();
			dto->name = row[0].to_string();      // 姓名
			dto->mobile = row[1].to_string();    // 手机号
			dto->password = row[2].to_string();  // 登录密码
			dto->parent = row[3].to_string();    // 家长姓名
			dto->sex = row[4].to_string();       // 性别
			dto->birthday = row[5].to_string();  // 生日
			dto->idCard = row[6].to_string();    // 身份证
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