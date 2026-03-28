#include "stdafx.h"
#include "UserProfileDAO.h"
#include "UserProfileMapper.h"


// 获取用户资料，根据用户ID获取
PtrUserRelatedDO UserRelatedDAO::selectById(long long id)
{
	string sql = "SELECT id,name,mobile,gender,birthday,head_img FROM staff WHERE id = ? ";
	UserProfileMapper mapper;
	return sqlSession->executeQueryOne<PtrUserRelatedDO>(sql, mapper, "%ll", id);
}

//更新用户头像
bool UserRelatedDAO::updateHeadImg(long long userId, const std::string& headImgUrl) {
	string sql = "UPDATE staff SET head_img = ? WHERE id = ?";

	std::string url = headImgUrl;

	int affectedRows = sqlSession->executeUpdate(sql, "%s%ll", url, userId);
	return affectedRows > 0;  // 更新成功返回 true，否则 false
}