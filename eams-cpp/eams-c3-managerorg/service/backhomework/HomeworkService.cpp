
#include "stdafx.h"
#include "HomeworkService.h"
#include "../../dao/homework/HomeworkRecordDao.h"
#include "../../dao/homework/HomeworkDao.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

GetHomeworkListPageDTO::Wrapper HomeworkService::gethomeworklist(const GetHomeworkListQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = GetHomeworkListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HomeworkDao dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<HomeworkDO> result = dao.gethomeworklist(query);  //无条件时，MySQL_Prepared_ResultSet::getInt: invalid value of 'columnIndex'
	// 将DO转换成DTO
	for (HomeworkDO& sub : result)
	{
		auto dto = GetHomeworkListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id,Id,classId, ClassId,title, Title,creator,Creator,add_time,AddTime);
		pages->addData(dto);
	}
	return pages;
}

GetHomeworkDetailDTO::Wrapper HomeworkService::gethomeworkdetail(int64_t id)
{
	// 查询数据
	HomeworkDao dao;
	auto res = dao.gethomeworkdetail(id);

	// 没有查询到数据
	if (!res)
		return nullptr;

	// 查询到数据转换成DTO
	auto dto = GetHomeworkDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, classId, ClassId, title, Title, content,Content);
	return dto;
}

//用于生成随机数，暂时用这个，后续可以改成雪花算法生成的id
int getRandomRange(int min, int max) {
	static bool flag = false;
	if (!flag) {
		srand((unsigned)time(NULL));
		flag = true;
	}
	return min + rand() % (max - min + 1);
}

//保存作业--修改/新增作业
bool HomeworkService::saveHomework(const SaveHomeworkDTO::Wrapper& dto)
{
	if (dto->id) {   //如果id存在，说明是修改作业
		// 组装DO数据
		HomeworkDO data;
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,Id, id , ClassId, classId,Title, title, Content, content,Editor, editor);
		
		HomeworkRecordDO homeworkrecord_data;
		ZO_STAR_DOMAIN_DTO_TO_DO(homeworkrecord_data, dto, Id,id,Content, content);
		// 设置修改时间
		data.setEditTime(SimpleDateTimeFormat::format()); //只用给homework表设置修改时间，homework_record表不需要修改时间
		// 执行数据修改
		// 查询数据是否存在？
		HomeworkDao dao;
		HomeworkRecordDAO record_dao;
		
		return dao.update(data) && record_dao.update(homeworkrecord_data);
	}
	else {       //如果id不存在，说明是新增作业
		// 组装homework表的DO数据,要给班级id，作业标题，作业内容，创建人
		HomeworkDO homework_data;
		ZO_STAR_DOMAIN_DTO_TO_DO(homework_data, dto, ClassId, classId, Title, title,  Content, content, Creator, creator);
		//组装homework_record表的DO数据，要给学生id，内容
		HomeworkRecordDO homeworkrecord_data;
		ZO_STAR_DOMAIN_DTO_TO_DO(homeworkrecord_data, dto,StudentId,studentid,Content,content);
		
		// 生成ID，sample中的id是string类型，但是homework的id是int64类型的，但是写homeworkDO的人给ID定义为int
		//UuidFacade uf;
		//data.setId(uf.genUuid());
		// 我这是用随机生成的int四字节的id，后续可以改成雪花算法生成的id
		int id = getRandomRange(1, 2147483647);  //分别给homework表和homework_record表赋值id
		homework_data.setId(id);
		homeworkrecord_data.setId(id);
		// 设置创建时间
		string add_time = SimpleDateTimeFormat::format(); //分别给homework表和homework_record表赋值创建时间
		homework_data.setAddTime(add_time);
		homeworkrecord_data.setAddTime(add_time);
		// 执行数据添加,
		HomeworkDao dao;
		HomeworkRecordDAO record_dao;

		return dao.insert(homework_data) && record_dao.insert(homeworkrecord_data);

	}
}
