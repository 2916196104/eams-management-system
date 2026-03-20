#pragma once

#include "domain/do/DoInclude.h"

class GradeDO : public BaseDO
{
public:
    GradeDO() : BaseDO("grade")
    {
        MYSQL_ADD_FIELD_PK("id", "bi", id);
        MYSQL_ADD_FIELD("title", "s", title);
        MYSQL_ADD_FIELD("info", "s", info);
        MYSQL_ADD_FIELD("creator", "bi", creator);
        MYSQL_ADD_FIELD("add_time", "s", add_time);
        MYSQL_ADD_FIELD("deleted", "b", deleted);
        MYSQL_ADD_FIELD("edit_time", "s", edit_time);
        MYSQL_ADD_FIELD("org_id", "bi", org_id);
    }

private:
    MYSQL_SYNTHESIZE(int64_t, id, Id);
    MYSQL_SYNTHESIZE(string, title, Title);
    MYSQL_SYNTHESIZE(string, info, Info);
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);
    MYSQL_SYNTHESIZE(string, add_time, AddTime);
    MYSQL_SYNTHESIZE(bool, deleted, Deleted);
    MYSQL_SYNTHESIZE(string, edit_time, EditTime);
    MYSQL_SYNTHESIZE(int64_t, org_id, OrgId);
};

typedef shared_ptr<GradeDO> PtrGradeDO;