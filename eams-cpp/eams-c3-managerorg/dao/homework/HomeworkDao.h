#ifndef _HOMEWORKDAO_H_
#define _HOMEWORKDAO_H_
#include "BaseDao.h"
#include "domain/do/homework/HomeworkDO.h"
#include "domain/dto/backhomework/BackHomeworkDTO.h"
#include "domain/query/backhomework/backhomeworkquery.h"


//课后作业操作类
class HomeworkDao : public BaseDAO
{
public:
	//通过id查询数据
	PtrHomeworkDO getHomeworkById(int id);
	//分页查询数据
	std::list<PtrHomeworkDO> queryHomeworkList(const GetHomeworkListQuery& query);
	//通过作业标题查询数据
	std::list<PtrHomeworkDO> queryHomeworkListByTitle(const std::string& title);

};



#endif