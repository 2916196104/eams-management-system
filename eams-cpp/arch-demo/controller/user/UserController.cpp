/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/20 16:29:31

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "UserController.h"
#include "service/user/UserService.h"
#include "service/user/AddressService.h"
#include "service/user/MenuService.h"

UserPageJsonVO::Wrapper UserController::executeQueryAll(const UserQuery::Wrapper& query)
{
	UserService us;
	auto vo = UserPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}

UserDetailJsonVO::Wrapper UserController::executeQueryOne(const String& id)
{
	UserService us;
	auto jvo = UserDetailJsonVO::createShared();
	auto data = us.getUserDetail(id);
	if (data)
		jvo->success(data);
	else
		jvo->fail({});
	return jvo;
}

StringJsonVO::Wrapper UserController::executeAddUser(const UserAddDTO::Wrapper& dto)
{
	UserService us;
	auto jvo = StringJsonVO::createShared();
	auto id = us.saveUser(dto);
	if (id != "")
		jvo->success(id);
	else
		jvo->fail({});
	return jvo;
}

StringJsonVO::Wrapper UserController::executeAddUserAddr(const AddressAddDTO::Wrapper& dto)
{
	// 呼叫用户地址服务保存地址
	AddressService as;
	auto res = as.saveAddress(dto);
	// 创建响应数据
	auto vo = StringJsonVO::createShared();
	if (res != "")
		vo->success(res);
	else
		vo->fail({});
	return vo;
}

MenuJsonVO::Wrapper UserController::executeQueryMenu(const PayloadDTO& payload)
{
	// 定义一个JsonVO对象
	auto vo = MenuJsonVO::createShared();
	// 调用菜单服务
	MenuService ms;
	auto menu = ms.listMenu();
	if (menu)
		vo->success(ms.listMenu());
	else
		vo->fail({});
	// 响应结果
	return vo;
}
