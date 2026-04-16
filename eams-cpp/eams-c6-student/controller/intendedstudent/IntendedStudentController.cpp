#include "stdafx.h"
#include "IntendedStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "../../service/intendedstudent/IntendedStudentService.h"

#pragma execution_character_set("utf-8")

//执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> IntendedStudentController::execExportExcel(
	const List<String>& ids)
{
	// 将前端 String 转换为 c++ string
	std::vector<std::string> idVec;
	for (const auto& id : *ids) {
		if (id)
		{
			idVec.push_back(*id);
		}
	}

	// 查询数据
	auto result = IntendedService().listByIds(idVec);

	// 将数据写入到 Excel 中
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

			// 写入数据
			int row = 2;
			int col = 1;

			// 转换数组（性别、关系）
			const char* genderArr[] = { "女", "男", "未知" };
			const char* relArr[] = { "本人", "父亲", "母亲", "其他" };
			for (auto& item : result) {
				col = 1;

				// ID (UInt64 -> string)
				ex->setCellValue(row, col++, std::to_string(item->id));
				// 姓名
				ex->setCellValue(row, col++, item->name);
				// 手机号码
				ex->setCellValue(row, col++, item->mobile);
				// 性别转换（0女 1男）
				int gender = item->gender;
				std::string genderStr = (gender >= 0 && gender <= 1) ? genderArr[gender] : "未知";
				ex->setCellValue(row, col++, genderStr);
				// 家长姓名
				ex->setCellValue(row, col++, item->parentName);
				// 家长关系转换（0本人 1父亲 2母亲 3其他）
				int rel = item->familyRel;
				std::string relStr = (rel >= 0 && rel <= 3) ? relArr[rel] : "其他";
				ex->setCellValue(row, col++, relStr);
				// 学校
				ex->setCellValue(row, col++, item->schoolName);
				// 年级
				ex->setCellValue(row, col++, item->gradeName);
				// 顾问
				ex->setCellValue(row, col++, item->counselorName);
				// 生日
				ex->setCellValue(row, col, item->birthday);
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息（下载文件名）
	std::string filename = "intended-students-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 返回成功结果
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
	oatpp::List<IntendedAddDTO::Wrapper> exceldata = oatpp::List<IntendedAddDTO::Wrapper>::createShared();
	ExcelComponent::read(file->data(), file->size(), "sheet1", [exceldata, &errmsg, &payload](xlnt::worksheet* sheet) {
		// 逐行解析解析数据
		int rn = 0;
		for (auto row : sheet->rows())
		{
			// 跳过表头
			if (rn++ == 0) continue;
			// 解析数据到DTO
			auto dto = IntendedAddDTO::createShared();
			dto->name = row[0].to_string();      // 姓名
			dto->mobile = row[1].to_string();    // 手机号
			dto->password = row[2].to_string();  // 登录密码
			dto->parent = row[3].to_string();    // 家长姓名

			int sex_mark = 0;
			if (row[4].to_string() == "女")
			{
				sex_mark = 0;
			}
			else if (row[4].to_string() == "男")
			{
				sex_mark = 1;
			}
			else
			{
				sex_mark = 2;
			}
			dto->sex = sex_mark;				 // 性别

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
	IntendedService service;
	bool success = service.importBatch(exceldata);

	if (!success) {
		jvo->init("import failed", RS_SERVER_ERROR);
		return jvo;
	}

	jvo->success(nullptr);
	return jvo;
}