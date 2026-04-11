package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

public interface PositionApis {
    JsonVO<List<String>> listNames(String name);

    JsonVO<PageDTO<PositionDTO>> list(@Valid PositionQueryCondition condition);

    JsonVO<String> save(@Valid PositionDTO dto);

    JsonVO<String> delete(@NotEmpty(message = "职位ID列表不能为空") List<@NotNull(message = "职位ID不能为空") Long> ids);



    /* 下面是职位数据权限的Api  */

    JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition);

    JsonVO<Long> addPositionDataPermission(PositionDataPermissionDTO positionDataPermissionDTO) throws Exception;

    JsonVO<List<Long>> removePositionDataPermission(List<Long> ids);

}
