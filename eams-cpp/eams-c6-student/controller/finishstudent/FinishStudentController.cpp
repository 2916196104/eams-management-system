#include "stdafx.h"
#include "controller/finishstudent/FinishStudentController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include <cstdint>
#include <limits>
#include <sstream>

std::shared_ptr<FinishStudentController::OutgoingResponse> FinishStudentController::execExportFinishStudent(const List<UInt64>& ids)
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
		auto trimCopy = [](const std::string& text) -> std::string {
			const auto begin = text.find_first_not_of(" \t\r\n");
			if (begin == std::string::npos) {
				return "";
			}
			const auto end = text.find_last_not_of(" \t\r\n");
			return text.substr(begin, end - begin + 1);
			};

		auto parseRequiredInt64 = [&trimCopy](const std::string& text, int64_t& value) -> bool {
			const auto trimmed = trimCopy(text);
			if (trimmed.empty()) {
				return false;
			}
			size_t pos = 0;
			try {
				const auto parsed = std::stoll(trimmed, &pos);
				if (pos != trimmed.size()) {
					return false;
				}
				value = static_cast<int64_t>(parsed);
				return true;
			}
			catch (...) {
				return false;
			}
			};

		auto parseOptionalInt32 = [&trimCopy](const std::string& text, int32_t& value) -> bool {
			const auto trimmed = trimCopy(text);
			if (trimmed.empty()) {
				return true;
			}
			size_t pos = 0;
			try {
				const auto parsed = std::stoll(trimmed, &pos);
				if (pos != trimmed.size()) {
					return false;
				}
				if (parsed < std::numeric_limits<int32_t>::min() || parsed > std::numeric_limits<int32_t>::max()) {
					return false;
				}
				value = static_cast<int32_t>(parsed);
				return true;
			}
			catch (...) {
				return false;
			}
			};

		int rn = 0;
		for (auto row : sheet->rows()) {
			if (rn++ == 0) continue;

			auto idText = trimCopy(row[0].to_string());
			if (idText.empty()) continue;

			auto dto = FinishStudentDTO::createShared();
			int64_t id = 0;
			if (!parseRequiredInt64(idText, id)) {
				errmsg = "row(" + std::to_string(rn) + ") id invalid.";
				return;
			}
			dto->id = id;

			dto->studentName = trimCopy(row[1].to_string());
			dto->parentName = trimCopy(row[2].to_string());
			int32_t familyRel = 0;
			if (!parseOptionalInt32(row[3].to_string(), familyRel)) {
				errmsg = "row(" + std::to_string(rn) + ") familyRel invalid.";
				return;
			}
			dto->familyRel = familyRel;
			dto->mobile = trimCopy(row[4].to_string());
			dto->counselor = trimCopy(row[5].to_string());
			dto->grade = trimCopy(row[6].to_string());
			dto->schoolName = trimCopy(row[7].to_string());
			int32_t lessonCount = 0;
			if (!parseOptionalInt32(row[8].to_string(), lessonCount)) {
				errmsg = "row(" + std::to_string(rn) + ") lessonCount invalid.";
				return;
			}
			dto->lessonCount = lessonCount;
			int32_t points = 0;
			if (!parseOptionalInt32(row[9].to_string(), points)) {
				errmsg = "row(" + std::to_string(rn) + ") points invalid.";
				return;
			}
			dto->points = points;
			int32_t gender = 0;
			if (!parseOptionalInt32(row[10].to_string(), gender)) {
				errmsg = "row(" + std::to_string(rn) + ") gender invalid.";
				return;
			}
			dto->gender = gender;
			int32_t age = 0;
			if (!parseOptionalInt32(row[11].to_string(), age)) {
				errmsg = "row(" + std::to_string(rn) + ") age invalid.";
				return;
			}
			dto->age = age;

			dto->remark = trimCopy(row[12].to_string());
			dto->graduationDate = trimCopy(row[13].to_string());

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
