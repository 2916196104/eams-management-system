package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

public interface PositionApis {
    JsonVO<List<String>> listNames(String name);

    JsonVO<PageDTO<PositionDTO>> list(@Valid PositionQueryCondition condition);

    JsonVO<String> save(@Valid PositionDTO dto);

    JsonVO<String> delete(@NotEmpty(message = "职位ID列表不能为空") List<@NotNull(message = "职位ID不能为空") Long> ids);
}
