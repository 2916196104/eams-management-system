#include "stdafx.h"
#include "Record_name.h"

// 接口 1: 获取学员列表(条件+分页) 的具体实现
TimetableStudentPageJsonVO::Wrapper Record_name::execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 1. 创建外层响应对象 VO
	auto jvo = TimetableStudentPageJsonVO::createShared();

	// 2. 创建分页数据容器 PageDTO (注意这里必须加 ::Wrapper)
	auto pages = PageDTO<TimetableStudentDTO::Wrapper>::createShared();

	pages->pageIndex = query->pageIndex ? query->pageIndex : 1;
	pages->pageSize = query->pageSize ? query->pageSize : 10;
	pages->total = 2; // 模拟总共有 2 条数据
	pages->calcPages(); // 计算总页数等分页数据

	// 3. 制造假数据 1
	auto stu1 = TimetableStudentDTO::createShared();
	stu1->id = "10001";
	stu1->name = "张三";
	stu1->head_img = "https://example.com/zhangsan.png";
	stu1->gender = "1";
	pages->addData(stu1);

	// 4. 制造假数据 2
	auto stu2 = TimetableStudentDTO::createShared();
	stu2->id = "10002";
	stu2->name = "李四";
	stu2->head_img = "https://example.com/lisi.png";
	stu2->gender = "2";
	pages->addData(stu2);

	// 5. 成功响应
	jvo->success(pages);
	return jvo;
}

// 接口 2: 添加学员到课次 的具体实现
StringJsonVO::Wrapper Record_name::execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->course_id || !dto->studentIds || dto->studentIds->size() == 0) {
		jvo->code = 500;
		jvo->message="参数不完整：课程ID或学员列表不能为空";
		return jvo;
	}

	// 模拟保存成功，返回成功信息
	jvo->success("成功将 " + std::to_string(dto->studentIds->size()) + " 名学员加入课次");
	return jvo;
}

// 接口 3: 获取学员课程列表 的具体实现
ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper Record_name::execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload)
{
	auto jvo = ListJsonVO<TimetableStudentCourseDTO::Wrapper>::createShared();

	// 1. 校验参数
	if (!query->id) {

		jvo->code = 500;
		jvo->message = "学员ID不能为空";
		return jvo;
	}

	// 2. 创建一个纯 List 容器 (注意 ::Wrapper)
	auto list = oatpp::List<TimetableStudentCourseDTO::Wrapper>::createShared();

	// 3. 制造假数据
	auto course1 = TimetableStudentCourseDTO::createShared();
	course1->course_id = "c_001";
	course1->title = "高等数学";
	course1->teacher_id = "王老师";
	course1->sn = "2";
	list->push_back(course1);

	auto course2 = TimetableStudentCourseDTO::createShared();
	course2->course_id = "c_002";
	course2->title = "大学英语";
	course2->teacher_id = "Lucy";
	course2->sn = "4";
	list->push_back(course2);

	// 4. 成功响应
	jvo->success(list);
	return jvo;
}