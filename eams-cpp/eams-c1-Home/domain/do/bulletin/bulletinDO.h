#pragma once
#ifndef _BULLETINDO_H_
#define _BULLETINDO_H_

#include "../DoInclude.h"

/**
 * 公告数据库实体类
 * 对应表：advertisement
 */
class bulletinDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 类型
	MYSQL_SYNTHESIZE(int8_t, type, Type);
	// 内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 封面图
	MYSQL_SYNTHESIZE(string, cover, Cover);
	// 创建者
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 逻辑删除标识
	MYSQL_SYNTHESIZE(int8_t, deleted, Deleted);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 编辑者
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	// 状态
	MYSQL_SYNTHESIZE(int8_t, state, State);
	// 排序号
	MYSQL_SYNTHESIZE(int32_t, sortNum, SortNum);
	// 唯一码
	MYSQL_SYNTHESIZE(string, code, Code);

public:
	bulletinDO() : BaseDO("advertisement")
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("type", "c", type);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("cover", "s", cover);
		MYSQL_ADD_FIELD("creator", "l", creator);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("deleted", "c", deleted);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("editor", "l", editor);
		MYSQL_ADD_FIELD("state", "c", state);
		MYSQL_ADD_FIELD("sort_num", "i", sortNum);
		MYSQL_ADD_FIELD("code", "s", code);
	}
};

typedef std::shared_ptr<bulletinDO> ptrbulletinDO;

// 未读数实体类
class redDO
{
private:
	int32_t gradeCount;      // 成绩未读数
	int32_t evaluateCount;   // 点评记录未读数
	int32_t homeworkCount;   // 作业未读数

public:
	// 无参构造函数
	redDO() : gradeCount(0), evaluateCount(0), homeworkCount(0) {}

	// 有参构造函数
	redDO(int32_t grade, int32_t evaluate, int32_t homework)
		: gradeCount(grade), evaluateCount(evaluate), homeworkCount(homework) {
	}

	// getter方法
	int32_t getGradeCount() const { return gradeCount; }
	int32_t getEvaluateCount() const { return evaluateCount; }
	int32_t getHomeworkCount() const { return homeworkCount; }

	// setter方法
	void setGradeCount(int32_t count) { gradeCount = count; }
	void setEvaluateCount(int32_t count) { evaluateCount = count; }
	void setHomeworkCount(int32_t count) { homeworkCount = count; }
};

typedef std::shared_ptr<redDO> ptrRedDO;

#endif // !_BULLETINDO_H_