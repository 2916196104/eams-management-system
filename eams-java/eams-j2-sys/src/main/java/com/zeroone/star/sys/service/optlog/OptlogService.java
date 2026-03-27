package com.zeroone.star.sys.service.optlog;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogOperatorQuery;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogQuery;

public interface OptlogService {
    PageDTO<OptlogDTO> queryOptlog(OptlogQuery query);
    PageDTO<OptlogOperatorDTO> queryOptlogOperators(OptlogOperatorQuery query);
}

