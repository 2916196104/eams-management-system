#pragma once

#include <string>
#include <vector>
#include "HomeworkSubmitVO.h"

struct HomeworkDetailVO {
  std::string homework_id;
  std::string title;
  std::string class_name;
  std::string content;
  std::string attachment;
  std::vector<HomeworkSubmitVO> submit_list;
};

