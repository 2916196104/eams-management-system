#include "stdafx.h"
#include "OnlineStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

// 执行导出
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> OnlineStudentController::execExportExcel(
	const OnlineExcelQuery::Wrapper& query)
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