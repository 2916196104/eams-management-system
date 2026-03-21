#pragma once

#include <string>

struct HomeworkListQuery {
  std::string admin_id;
  std::string class_id;
  int page = 1;
  int size = 10;
};

