#pragma once

#include <string>

struct HomeworkListItemVO {
  std::string homework_id;
  std::string title;
  std::string class_name;
  int submit_count = 0;
  std::string create_time;
};

