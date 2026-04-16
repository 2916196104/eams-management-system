#pragma once

#ifndef _UPDATEHEADIMGSERVICE_H_
#define _UPDATEHEADIMGSERVICE_H_
#include "domain/dto/UserRelated/UserRelatedDTO.h"

class UpdateHeadImgService
{
public:
	//更新用户头像，根据用户ID和新的头像URL地址进行更新，返回更新后的头像URL地址
	ChangePictureDTO::Wrapper updateHeadImg(long long userId,
		const char* data,
		size_t size,
		const std::string& fileName);


};

#endif // !_UPDATEHEADIMGSERVICE_H_
