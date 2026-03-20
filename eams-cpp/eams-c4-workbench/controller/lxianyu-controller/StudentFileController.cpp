#include "StudentFileController.h"
#include "stdafx.h"

#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

StudentFilePageJsonVO::Wrapper StudentFileController::execQueryList(const StudentFilePageQuery::Wrapper& query)
{
	return {};
}

StudentTimeTablePageJsonVO::Wrapper StudentFileController::execQueryTimeTable(const StudentTimeTablePageQuery::Wrapper& query) {
	return {};
}

StudentFileProJsonVO::Wrapper StudentFileController::execQueryStudentById(const String& id) {
	return {};
}