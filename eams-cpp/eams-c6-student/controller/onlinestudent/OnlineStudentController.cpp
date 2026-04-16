#include "stdafx.h"
#include "OnlineStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "../../service/onlinestudent/OnlineStudentService.h"

#pragma execution_character_set("utf-8")

// 执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> OnlineStudentController::execExportExcel(
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
	auto result = OnlineService().listByIds(idVec);

	// 将数据写入到 Excel 中
	auto buff = ExcelComponent().writeVectorToBuff("online_student",
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
			const char* genderArr[] = { "女", "男" };
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
	std::string filename = "online-students-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 返回成功结果
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

// 执行修改顾问
StringJsonVO::Wrapper OnlineStudentController::execModifyCounselor(const ModifyCounselorDTO::Wrapper& dto)
{
	// 0 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 1 校验参数
	if (!dto->studentIds || dto->studentIds->size() == 0)
	{
		jvo->init("studentIds is empty.", RS_PARAMS_INVALID);
		return jvo;
	}

	if (!dto->counselorName || dto->counselorName->empty())
	{
		jvo->init("counselorName is empty.", RS_PARAMS_INVALID);
		return jvo;
	}

	if (!dto->counselorPosition || dto->counselorPosition->empty())
	{
		jvo->init("counselorPosition is empty.", RS_PARAMS_INVALID);
		return jvo;
	}

	// 2 调用 Service 层更新学员顾问信息
	// TODO: 实现 Service 层方法
	// OnlineStudentService::modifyCounselor(dto->studentIds, dto->counselorName, dto->counselorPosition);

	// 3 返回成功结果
	jvo->success(nullptr);
	return jvo;
}