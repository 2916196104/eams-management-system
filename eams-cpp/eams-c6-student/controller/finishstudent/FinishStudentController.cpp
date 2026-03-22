#include "stdafx.h"
#include "controller/finishstudent/FinishStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include <cstdint>
#include <sstream>

std::shared_ptr<FinishStudentController::OutgoingResponse> FinishStudentController::execExportFinishStudent(const List<String>& ids)
{
	auto data = m_finishStudentService.listFinishStudentByIds(ids);

	auto buff = ExcelComponent().writeVectorToBuff("finish_student",
		[&](ExcelComponent* ex) {
			ex->addHeader({
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.id"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.student-name"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.parent-name"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.family-relation"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.mobile"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.counselor"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.grade"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.school-name"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.lesson-count"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.points"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.gender"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.age"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.remark"),
				ZH_WORDS_GETTER("finishstudent.field.finish-student-query.graduation-date")
				});

			int rowIndex = 2;
			for (const auto& dto : data) {
				ex->setCellValue(rowIndex, 1, std::to_string(static_cast<long long>(dto->id.getValue(0))));
				ex->setCellValue(rowIndex, 2, dto->studentName.getValue(""));
				ex->setCellValue(rowIndex, 3, dto->parentName.getValue(""));
				ex->setCellValue(rowIndex, 4, std::to_string(dto->familyRel.getValue(0)));
				ex->setCellValue(rowIndex, 5, dto->mobile.getValue(""));
				ex->setCellValue(rowIndex, 6, dto->counselor.getValue(""));
				ex->setCellValue(rowIndex, 7, dto->grade.getValue(""));
				ex->setCellValue(rowIndex, 8, dto->schoolName.getValue(""));
				ex->setCellValue(rowIndex, 9, std::to_string(dto->lessonCount.getValue(0)));
				ex->setCellValue(rowIndex, 10, std::to_string(dto->points.getValue(0)));
				ex->setCellValue(rowIndex, 11, std::to_string(dto->gender.getValue(0)));
				ex->setCellValue(rowIndex, 12, std::to_string(dto->age.getValue(0)));
				ex->setCellValue(rowIndex, 13, dto->remark.getValue(""));
				ex->setCellValue(rowIndex, 14, dto->graduationDate.getValue(""));
				ex->setRowProperties(rowIndex++);
			}
		});

	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());
	auto response = createResponse(Status::CODE_200, fstring);

	std::string filename = "rp-finish-" + SimpleDateTimeFormat::format("%Y%m%d%H%M%S") + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	return response;
}

StringJsonVO::Wrapper FinishStudentController::execImportFinishStudent(std::shared_ptr<IncomingRequest> request)
{
	auto jvo = StringJsonVO::createShared();

	API_MULTIPART_INIT(container, reader);
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	request->transferBody(&reader);

	API_MULTIPART_PARSE_FILE_FIELD(container, "excel", file);
	if (!file) {
		jvo->init("not set excel file.", RS_PARAMS_INVALID);
		return jvo;
	}

	std::list<FinishStudentDTO::Wrapper> rows;
	std::string errmsg = "";
	ExcelComponent::read(file->data(), file->size(), "finish_student", [&rows, &errmsg](xlnt::worksheet* sheet) {
		int rn = 0;
		for (auto row : sheet->rows()) {
			if (rn++ == 0) continue;

			auto idText = row[0].to_string();
			if (idText.empty()) continue;

			auto dto = FinishStudentDTO::createShared();
			try {
				dto->id = static_cast<int64_t>(std::stoll(idText));
			}
			catch (...) {
				errmsg = "row(" + std::to_string(rn) + ") id invalid.";
				return;
			}

			dto->remark = row[12].to_string();
			dto->graduationDate = row[13].to_string();

			auto graduationDate = dto->graduationDate.getValue("");
			if (!graduationDate.empty()) {
				if (graduationDate.length() != 10 || graduationDate[4] != '-' || graduationDate[7] != '-') {
					errmsg = "row(" + std::to_string(rn) + ") graduationDate invalid.";
					return;
				}
			}

			rows.push_back(dto);
		}
		});

	if (!errmsg.empty()) {
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}
	if (rows.empty()) {
		jvo->init("excel file no data or not excel file.", RS_PARAMS_INVALID);
		return jvo;
	}

	const auto updatedRows = m_finishStudentService.importFinishStudent(rows);
	std::ostringstream oss;
	oss << "import success, rows=" << rows.size() << ", updated=" << updatedRows;
	jvo->success(oss.str().c_str());
	return jvo;
}
