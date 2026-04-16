#ifndef HOMEWORK_MAPPER_H
#define HOMEWORK_MAPPER_H
#include "Mapper.h"
#include "domain/do/homework/HomeworkDO.h"



//作业Mapper接口，定义作业相关数据库操作
class HomeworkMapper :public Mapper<HomeworkDO>
{
public:
	HomeworkDO mapper(ResultSet* resultSet) const override
	{
		HomeworkDO homework;
		homework.setId(resultSet->getInt("id"));
		homework.setClassId(resultSet->getInt("class_id"));
		homework.setTitle(resultSet->getString("title"));
		return homework;
	}
};


//定义智能指针
class PtrHomeworkMapper :public std::shared_ptr<HomeworkMapper>
{
public:
	PtrHomeworkDO mapper(ResultSet* resultSet) const //兄弟，你这原来写的是map，我改成mapper了，接口中是mapper，否则我们调用的时候会报错，找不到这个函数
	{
		auto homework = std::make_shared<HomeworkDO>();
		homework->setId(resultSet->getInt("id"));
		homework->setClassId(resultSet->getInt("class_id"));
		homework->setTitle(resultSet->getString("title"));
		return homework;
	}
};

//获取作业列表（功能+分页）的Mapper，上面的Mapper是另一个兄弟写的
class GetHomeworkListMapper :public Mapper<HomeworkDO>
{
public:
	HomeworkDO mapper(ResultSet* resultSet) const override
	{
		HomeworkDO homework;
		homework.setId(resultSet->getInt64("id"));
		homework.setClassId(resultSet->getInt64("class_id"));
		homework.setTitle(resultSet->getString("title"));
		homework.setCreator(resultSet->getInt64("creator"));
		homework.setAddTime(resultSet->getString("add_time"));
		return homework;
	}
};


//定义智能指针
class PtrGetHomeworkListMapper :public std::shared_ptr<GetHomeworkListMapper>
{
public:
	PtrHomeworkDO mapper(ResultSet* resultSet) const 
	{
		auto homework = std::make_shared<HomeworkDO>();
		homework->setId(resultSet->getInt64("id"));
		homework->setClassId(resultSet->getInt64("class_id"));
		homework->setTitle(resultSet->getString("title"));
		homework->setCreator(resultSet->getInt64("creator"));
		homework->setAddTime(resultSet->getString("add_time"));
		return homework;
	}
};

//获取作业详情的Mapper
// 前端传id
// 后端根据id查询数据，传回班级，标题，作业内容
class GetHomeworkDetailMapper :public Mapper<HomeworkDO>
{
public:
	HomeworkDO mapper(ResultSet* resultSet) const override
	{
		HomeworkDO homework;
		homework.setClassId(resultSet->getInt64("class_id"));
		homework.setTitle(resultSet->getString("title"));
		homework.setContent(resultSet->getString("content"));
		return homework;
	}
};


//定义智能指针
class PtrGetHomeworkDetailMapper :public std::shared_ptr<GetHomeworkListMapper>
{
public:
	PtrHomeworkDO mapper(ResultSet* resultSet) const
	{
		auto homework = std::make_shared<HomeworkDO>();
		homework->setClassId(resultSet->getInt64("class_id"));
		homework->setTitle(resultSet->getString("title"));
		homework->setContent(resultSet->getString("content"));
		return homework;
	}
};

#endif // HOMEWORK_MAPPER_H