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


#endif // HOMEWORK_MAPPER_H