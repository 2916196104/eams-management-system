#include "stdafx.h"
#include "service/finishstudent/FinishStudentService.h"

std::list<FinishStudentDTO::Wrapper> FinishStudentService::listFinishStudentByIds(const oatpp::List<oatpp::UInt64>& ids)
{
	return m_finishStudentDAO.listFinishStudentByIds(ids);
}

int FinishStudentService::importFinishStudent(const std::list<FinishStudentDTO::Wrapper>& rows)
{
	std::list<FinishStudentDO> dos;
	for (const auto& row : rows) {
		if (!row || !row->id) {
			continue;
		}
		auto& data = dos.emplace_back();
		data.setId(static_cast<uint64_t>(row->id.getValue(0)));
		data.setStudentName(row->studentName.getValue(""));
		data.setParentName(row->parentName.getValue(""));
		data.setFamilyRel(row->familyRel.getValue(0));
		data.setMobile(row->mobile.getValue(""));
		data.setCounselor(row->counselor.getValue(""));
		data.setGrade(row->grade.getValue(""));
		data.setSchoolName(row->schoolName.getValue(""));
		data.setLessonCount(row->lessonCount.getValue(0));
		data.setPoints(row->points.getValue(0));
		data.setGender(row->gender.getValue(0));
		data.setAge(row->age.getValue(0));
		data.setRemark(row->remark.getValue(""));
		data.setGraduationDate(row->graduationDate.getValue(""));
	}
	if (dos.empty()) {
		return 0;
	}
	return m_finishStudentDAO.updateFinishStudentBatch(dos);
}

