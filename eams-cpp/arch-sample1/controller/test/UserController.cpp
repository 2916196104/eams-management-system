/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:19:14

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
#include "service/UserService.h"
#include "domain/vo/UserVO.h"


// 用户注册接口实现
StringJsonVO::Wrapper UserController::execRegister(const UserRegisterDTO::Wrapper& dto) {
    auto jvo = StringJsonVO::createShared();

    // 参数校验
    if (!dto->username || !dto->password || !dto->nickname) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 调用Service
    try {
        UserService service;
        std::string userId = service.registerUser(dto);
        jvo->success(userId);
    }
    catch (const std::exception& e) {
        jvo->fail("");
        jvo->message = e.what();
    }

    return jvo;
}

// 用户登录接口实现
LoginJsonVO::Wrapper UserController::execLogin(const UserLoginDTO::Wrapper& dto) {
    auto jvo = LoginJsonVO::createShared();

    // 参数校验
    if (!dto->username || !dto->password) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 调用Service
    try {
        UserService service;
        auto loginVO = service.login(dto);
        jvo->success(loginVO);
    }
    catch (const std::exception& e) {
        jvo->fail(nullptr);
        jvo->message = e.what();
    }

    return jvo;
}

// 其他方法实现类似..
