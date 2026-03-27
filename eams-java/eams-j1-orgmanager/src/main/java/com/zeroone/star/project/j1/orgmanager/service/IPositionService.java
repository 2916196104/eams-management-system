package com.zeroone.star.project.j1.orgmanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;

import java.util.List;

public interface IPositionService {
    List<String> listNames(String name);

    PageDTO<PositionDTO> list(PositionQueryCondition condition);

    boolean save(PositionDTO dto);

    boolean delete(List<Long> ids);
}
