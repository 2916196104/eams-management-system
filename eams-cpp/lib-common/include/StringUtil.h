#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 
 @Author: awei
 @Date: 2022/10/24 16:18:29
 
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
#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_
#include <vector>
#include <string>
using namespace std;

/**
 * 字符串操作工具类
 */
class StringUtil final
{
public:
	//************************************
	// Method:    split
	// FullName:  StringUtil::split
	// Access:    public static 
	// Returns:   std::vector<std::string> 拆分字符串列表
	// Description: 字符串拆分
	// Parameter: const string & str 待拆分字符串
	// Parameter: const string & delim 分割符
	//************************************
	static vector<string> split(const string& str,const string& delim);

	//************************************
	// Method:    trim
	// FullName:  StringUtil::trim
	// Access:    public static 
	// Returns:   void
	// Description: 字符串清除两端空格
	// Parameter: string * str 待处理字符串
	//************************************
	static void trim(string* str);

	//************************************
	// Method:    replace
	// FullName:  StringUtil::replace
	// Access:    public static 
	// Returns:   void
	// Description: 字符串替换处理
	// Parameter: string * base 待替换字符串
	// Parameter: const string & src 替换子串
	// Parameter: const string & dst 目标子串
	//************************************
	static void replace(string* base, const string& src, const string& dst);
};
#endif // _STRINGUTIL_H_
