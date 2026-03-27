package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface PositionApis {
    JsonVO<List<String>> listNames(String name);

    JsonVO<PageDTO<PositionDTO>> list(PositionQueryCondition condition);

    JsonVO<String> save(PositionDTO dto);

    JsonVO<String> delete(List<Long> ids);
}
