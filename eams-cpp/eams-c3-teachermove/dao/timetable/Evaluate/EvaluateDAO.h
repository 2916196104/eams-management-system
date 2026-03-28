#ifndef _EVALUATE_DAO_H_
#define _EVALUATE_DAO_H_

#include "BaseDAO.h"
#include "domain/query/timetable/TimetableQuery.h"



class EvaluateDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const EvaluationQuery::Wrapper& query, SqlParams& params);
public:
	bool queryById(const std::string& id);		// 通过Id来看是否被评价过了，被评价过了就不能再次评价了
};
#endif // !_EVALUATE_DAO_H_
