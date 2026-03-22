/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 16:41:04

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
#include "MenuService.h"
#include "dao/user/MenuDAO.h"
#include "tree/TreeUtil.h"
#include "TreeMenuMapper.h"

oatpp::List<MenuDTO::Wrapper> MenuService::listMenu()
{
	// 获取菜单数据
	std::list<PtrMenuDO> listData = MenuDAO().selectAll();

	// 转换为树形结构
	std::list<shared_ptr<TreeNode>> res = TreeUtil::listToTree<PtrMenuDO>(listData, TreeMenuMapper());

	// 将根节点存储到列表中
	auto data = oatpp::List<MenuDTO::Wrapper>::createShared();
	for (auto one : res)
	{
		data->push_back(MenuDTO::Wrapper(dynamic_pointer_cast<MenuDTO>(one), MenuDTO::Wrapper::Class::getType()));
	}
	return data;
}
