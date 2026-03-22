#include "StudentService.h"


// 删除用户
bool StudentService::deleteStudent(const std::uint64_t& id)
{
    if (id <= 0) {
        return false;
    }//判断参数是否合法

    //调用DAO层，返回删除结果
	StudentDAO dao;
	bool result =dao.deleteById(id);
    return result;
}