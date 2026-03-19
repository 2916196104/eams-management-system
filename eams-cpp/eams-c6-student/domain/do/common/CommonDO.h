#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _SAMPLE_DO_
#define _SAMPLE_DO_
#include "../DoInclude.h"

/**
 *  添加跟进记录
 */
class AddFollowUpRecordDO : public BaseDO
{

public:

};


/**
 * 调整积分DO
 */
class ModifyPointsDO : public BaseDO
{
public:

};






// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<AddFollowUpRecordDO> PtrSampleDO;
#endif // !_SAMPLE_DO_
