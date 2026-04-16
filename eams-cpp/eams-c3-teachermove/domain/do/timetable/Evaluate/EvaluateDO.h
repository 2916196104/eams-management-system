#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/17 16:25:30

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
#ifndef _EVALUATEDO_H_
#define _EVALUATEDO_H_
#include "../../DoInclude.h"


class EvaluateDO : public BaseDO
{
	// 唯一编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 评价时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 评价人Id
	MYSQL_SYNTHESIZE(int, teacherId, TeacherId);
	// 评价分数
	MYSQL_SYNTHESIZE(int, score, Score);
	// 评价
	MYSQL_SYNTHESIZE(string, evaluation, Evaluation);

public:
	EvaluateDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("evaluate_time", "s", time);
		MYSQL_ADD_FIELD("evaluate_teacher", "i", teacherId);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
	}

};



#endif // !_EVALUATEDO_H_