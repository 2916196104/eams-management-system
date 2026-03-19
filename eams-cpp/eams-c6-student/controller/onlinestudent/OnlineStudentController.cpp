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