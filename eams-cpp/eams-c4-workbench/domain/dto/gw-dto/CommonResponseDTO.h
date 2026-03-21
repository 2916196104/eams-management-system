#pragma once
#ifndef COMMON_RESPONSE_DTO_H
#define COMMON_RESPONSE_DTO_H

#include "../../GlobalInclude.h"
#include "ServerInfo.h"
#include "Macros.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CommonResponseDTO : public oatpp::DTO {
  DTO_INIT(CommonResponseDTO, DTO);

  DTO_FIELD(Int32, code) = 0;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, msg) = "success";
  DTO_FIELD_INFO(msg) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(String, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u6570\u636E\u5BF9\u8C61";
  }
};

class HomeworkListRowDTO : public oatpp::DTO {
  DTO_INIT(HomeworkListRowDTO, DTO);

  DTO_FIELD(String, homework_id) = "";
  DTO_FIELD_INFO(homework_id) {
    info->description = u8"\u4F5C\u4E1AID";
  }
  DTO_FIELD(String, title) = "";
  DTO_FIELD_INFO(title) {
    info->description = u8"\u4F5C\u4E1A\u6807\u9898";
  }
  DTO_FIELD(String, class_name) = "";
  DTO_FIELD_INFO(class_name) {
    info->description = u8"\u73ED\u7EA7\u540D\u79F0";
  }
  DTO_FIELD(Int32, submit_count) = 0;
  DTO_FIELD_INFO(submit_count) {
    info->description = u8"\u63D0\u4EA4\u4EBA\u6570";
  }
  DTO_FIELD(String, create_time) = "";
  DTO_FIELD_INFO(create_time) {
    info->description = u8"\u521B\u5EFA\u65F6\u95F4";
  }
};

class HomeworkListPageDTO : public oatpp::DTO {
  DTO_INIT(HomeworkListPageDTO, DTO);

  DTO_FIELD(UInt64, pageIndex) = 1;
  DTO_FIELD_INFO(pageIndex) {
    info->description = u8"\u5F53\u524D\u9875\u7801";
  }
  DTO_FIELD(UInt64, pageSize) = 5;
  DTO_FIELD_INFO(pageSize) {
    info->description = u8"\u6BCF\u9875\u6570\u636E\u6761\u6570";
  }
  DTO_FIELD(Int64, total) = v_int64(0);
  DTO_FIELD_INFO(total) {
    info->description = u8"\u6570\u636E\u603B\u6761\u6570";
  }
  DTO_FIELD(Int64, pages) = v_int64(0);
  DTO_FIELD_INFO(pages) {
    info->description = u8"\u6570\u636E\u603B\u9875\u6570";
  }
  DTO_FIELD(List<Object<HomeworkListRowDTO>>, rows) = {};
  DTO_FIELD_INFO(rows) {
    info->description = u8"\u5F53\u524D\u9875\u6570\u636E\u5217\u8868";
  }
};

class HomeworkListPageJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkListPageJsonVO, DTO);

  DTO_FIELD(Int32, code) = 10000;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, message) = "success";
  DTO_FIELD_INFO(message) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(Object<HomeworkListPageDTO>, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u5206\u9875\u6570\u636E";
  }
};

class HomeworkDetailDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkDetailDataDTO, DTO);

  DTO_FIELD(String, homework_id) = "";
  DTO_FIELD_INFO(homework_id) {
    info->description = u8"\u4F5C\u4E1AID";
  }
  DTO_FIELD(String, title) = "";
  DTO_FIELD_INFO(title) {
    info->description = u8"\u4F5C\u4E1A\u6807\u9898";
  }
  DTO_FIELD(String, class_name) = "";
  DTO_FIELD_INFO(class_name) {
    info->description = u8"\u73ED\u7EA7\u540D\u79F0";
  }
  DTO_FIELD(String, content) = "";
  DTO_FIELD_INFO(content) {
    info->description = u8"\u4F5C\u4E1A\u5185\u5BB9";
  }
};

class HomeworkDetailJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkDetailJsonVO, DTO);

  DTO_FIELD(Int32, code) = 10000;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, message) = "success";
  DTO_FIELD_INFO(message) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(Object<HomeworkDetailDataDTO>, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u8BE6\u60C5\u6570\u636E";
  }
};

class HomeworkAddDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkAddDataDTO, DTO);

  DTO_FIELD(String, homework_id) = "";
  DTO_FIELD_INFO(homework_id) {
    info->description = u8"\u4F5C\u4E1AID";
  }
  DTO_FIELD(String, title) = "";
  DTO_FIELD_INFO(title) {
    info->description = u8"\u4F5C\u4E1A\u6807\u9898";
  }
};

class HomeworkAddJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkAddJsonVO, DTO);

  DTO_FIELD(Int32, code) = 10000;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, message) = "success";
  DTO_FIELD_INFO(message) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(Object<HomeworkAddDataDTO>, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u65B0\u589E\u4F5C\u4E1A\u6570\u636E";
  }
};

class HomeworkCommentDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkCommentDataDTO, DTO);

  DTO_FIELD(String, comment_id) = "";
  DTO_FIELD_INFO(comment_id) {
    info->description = u8"\u70B9\u8BC4ID";
  }
  DTO_FIELD(Int32, score) = 0;
  DTO_FIELD_INFO(score) {
    info->description = u8"\u8BC4\u5206";
  }
  DTO_FIELD(String, content) = "";
  DTO_FIELD_INFO(content) {
    info->description = u8"\u70B9\u8BC4\u5185\u5BB9";
  }
};

class HomeworkCommentJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkCommentJsonVO, DTO);

  DTO_FIELD(Int32, code) = 10000;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, message) = "success";
  DTO_FIELD_INFO(message) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(Object<HomeworkCommentDataDTO>, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u70B9\u8BC4\u6570\u636E";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // COMMON_RESPONSE_DTO_H

