#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 15:31:10

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
#ifndef _CHARSETCONVERTHEPLER_H_
#define _CHARSETCONVERTHEPLER_H_
#include <string>
/**
 * 字符串编码转码工具类
 */
class CharsetConvertHepler final
{
public:
	//************************************
	// Method:    unicodeToUtf8
	// FullName:  CharsetConvertHepler::unicodeToUtf8
	// Access:    public static 
	// Returns:   std::string 返回转换后的字符串
	// Description: 将Unicode字符串转换成UTF8字符串
	// Parameter: const std::wstring& wstr Unicode字符串
	//************************************
	static std::string unicodeToUtf8(const std::wstring& wstr);

	//************************************
	// Method:    utf8ToUnicode
	// FullName:  CharsetConvertHepler::utf8ToUnicode
	// Access:    public static 
	// Returns:   std::wstring 返回转换后的字符串
	// Description: 将UTF8字符串转换成Unicode字符串
	// Parameter: const std::string& str UTF8字符串
	//************************************
	static std::wstring utf8ToUnicode(const std::string& str);

	//************************************
	// Method:    unicodeToAnsi
	// FullName:  CharsetConvertHepler::unicodeToAnsi
	// Access:    public static 
	// Returns:   std::string 返回转换后的字符串
	// Description: 将Unicode字符串转换成ANSI字符串
	// Parameter: const std::wstring& wstr Unicode字符串
	//************************************
	static std::string unicodeToAnsi(const std::wstring& wstr);

	//************************************
	// Method:    ansiToUnicode
	// FullName:  CharsetConvertHepler::ansiToUnicode
	// Access:    public static 
	// Returns:   std::wstring 返回转换后的字符串
	// Description: 将ANSI字符串转换成Unicode字符串
	// Parameter: const std::string& str ANSI字符串
	//************************************
	static std::wstring ansiToUnicode(const std::string& str);

	//************************************
	// Method:      utf8ToAnsi
	// FullName:    CharsetConvertHepler::utf8ToAnsi
	// Access:      public static 
	// Returns:     std::string 返回转换后的字符串
	// Description:  将UTF8字符串转换成ANSI字符串
	// Parameter:   const std::string& str UTF8字符串
	//************************************
	static std::string utf8ToAnsi(const std::string& str);

	//************************************
	// Method:    ansiToUtf8
	// FullName:  CharsetConvertHepler::ansiToUtf8
	// Access:    public static 
	// Returns:   std::string
	// Description: 将ANSI字符串转换成UTF8字符串
	// Parameter: const std::string& str ANSI字符串
	//************************************
	static std::string ansiToUtf8(const std::string& str);

	// 字符串utf8编码转换gbk编码
	static std::string utf8ToGbk(const std::string& str);

	// 字符串gbk编码转换utf8编码
	static std::string gbkToUtf8(const std::string& str);
};
#endif // _CHARSETCONVERTHEPLER_H_
