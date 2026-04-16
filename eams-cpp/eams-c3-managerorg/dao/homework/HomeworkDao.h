#ifndef _HOMEWORKDAO_H_
#define _HOMEWORKDAO_H_
#include "BaseDAO.h"
#include "domain/do/homework/HomeworkDO.h"
#include "domain/dto/backhomework/backhomeworkDTO.h"
#include "domain/query/backhomework/backhomeworkQuery.h"


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
	//删除作业数据（支持单个和批量删除）
	int deleteHomework(const std::list<int>& ids);

private:
	inline std::string queryConditionBuilder(const GetHomeworkListQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	// 在service层会调用这个方法
	uint64_t count(const GetHomeworkListQuery::Wrapper& query);
	// 获取作业详情（条件+分页）
	std::list<HomeworkDO> gethomeworklist(const GetHomeworkListQuery::Wrapper& query);
	// 获取作业详情，传id，返回对应作业的DO
	PtrHomeworkDO gethomeworkdetail(int id);
};



#endif