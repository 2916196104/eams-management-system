#include "stdafx.h"
#include "OnlineStudentService.h"
#include "../../dao/onlinestudent/OnlineStudentDAO.h"
#include "../../dao/common/CommonDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

std::list<OnlineExportDTO::Wrapper> OnlineService::listByIds(const std::vector<std::string>& ids)
{
	OnlineExportDAO dao;
	std::list<PtrStudentDetail> details = dao.selectByIds(ids);

	// 转换为导出DTO
	std::list<OnlineExportDTO::Wrapper> result;
	for (PtrStudentDetail& detail : details)
	{
		auto dto = OnlineExportDTO::createShared();

		// id 单独处理：string 转 UInt64
		dto->id = std::stoull(detail->student.getId());

		// student 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->student,
			name, Name,
			gender, Gender,
			familyRel, FamilyRel,
			birthday, Birthday
		);

		// user 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->user,
			mobile, Mobile,
			parentName, Name
		);

		// org 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->org,
			schoolName, Name
		);

		// class_grade 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->classGrade,
			gradeName, Name
		);

		// staff 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->staff,
			counselorName, Name
		);

		result.push_back(dto);
	}
	return result;
}

StringJsonVO::Wrapper OnlineService::importExcel(const oatpp::String& excelData, const PayloadDTO& payload)
{
	// 解析Excel文件（这里模拟解析过程）
	// 实际项目中需要使用Excel解析库
	std::vector<OnlineAddDTO::Wrapper> students;
	
	// 模拟解析结果
	for (int i = 0; i < 3; i++) {
		auto student = OnlineAddDTO::createShared();
		student->name = "学生" + std::to_string(i + 1);
		student->parent = "家长" + std::to_string(i + 1);
		student->parentRel = "父亲";
		student->mobile = "1380013800" + std::to_string(i);
		student->counselor = "顾问" + std::to_string(i + 1);
		student->grade = "一年级";
		student->school = "第一小学";
		student->sex = "男";
		student->age = 7 + i;
		student->note = "备注" + std::to_string(i + 1);
		students.push_back(student);
	}
	
	// 执行导入操作
	OnlineImportDAO dao;
	int importedCount = dao.importStudents(students);
	
	// 检查导入结果
	if (importedCount <= 0) {
		auto vo = StringJsonVO::createShared();
		vo->code = 500;
		vo->message = "导入失败";
		return vo;
	}
	
	// 导入成功
	auto vo = StringJsonVO::createShared();
	vo->code = 200;
	vo->message = "导入成功";
	vo->data = "导入了 " + std::to_string(importedCount) + " 条记录";
	return vo;
}

StringJsonVO::Wrapper OnlineService::modifyCounselor(const ModifyCounselorDTO::Wrapper& dto)
{
	// 验证参数
	if (!dto || !dto->studentIds || dto->studentIds->size() == 0) {
		auto vo = StringJsonVO::createShared();
		vo->code = 400;
		vo->message = "学员ID列表不能为空";
		return vo;
	}
	
	if (!dto->counselorName || dto->counselorName->empty()) {
		auto vo = StringJsonVO::createShared();
		vo->code = 400;
		vo->message = "顾问姓名不能为空";
		return vo;
	}
	
	// 转换学员ID列表
	std::vector<std::string> studentIds;
	if (dto->studentIds) {
		for (const auto& id : *dto->studentIds) {
			studentIds.push_back(id->c_str());
		}
	}
	
	// 执行修改顾问操作
	OnlineStudentDAO dao;
	// 这里需要获取顾问ID，暂时使用空字符串
	std::string counselorId = "";
	int result = dao.updateCounselor(studentIds, dto->counselorName->c_str(), counselorId);
	
	// 检查修改结果
	if (result <= 0) {
		auto vo = StringJsonVO::createShared();
		vo->code = 500;
		vo->message = "修改失败";
		return vo;
	}
	
	// 修改成功
	auto vo = StringJsonVO::createShared();
	vo->code = 200;
	vo->message = "修改成功";
	vo->data = "修改了 " + std::to_string(result) + " 个学员的顾问";
	return vo;
}