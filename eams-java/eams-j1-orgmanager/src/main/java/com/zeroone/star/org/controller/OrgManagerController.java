package com.zeroone.star.org.controller;

import com.zeroone.star.org.mapstruct.DataPermissionConvert;
import com.zeroone.star.org.service.DataPermissionService;
import com.zeroone.star.project.Do.j1.PositionDataPermissionDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.j1.org.PositionDataPermissionApis;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

@RestController
@RequestMapping("/common/position/permission")
@Api(tags = "职位数据权限")
public class OrgManagerController implements PositionDataPermissionApis {
    @Resource
    private DataPermissionService dataPermissionService;

    @Resource
    private DataPermissionConvert dataPermissionConvert;

    @Override
    @GetMapping("/query")
    @ApiOperation("获取职位数据权限列表（条件+分页）")
    public JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition) {
        return JsonVO.success(dataPermissionService.listAll(condition));
    }

    @Override
    @PostMapping("/save")
    @ApiOperation("保存职位数据权限（新增/修改）")
    public JsonVO<Long> addPositionDataPermission(@RequestBody PositionDataPermissionDTO positionDataPermissionDTO) {
        Long id = positionDataPermissionDTO.getId();
        PositionDataPermissionDO permissionDO = dataPermissionConvert.dtoToDo(positionDataPermissionDTO);
        if (id == null) {
            if (dataPermissionService.save(permissionDO)) {
                return JsonVO.success(permissionDO.getId());
            }
        } else {
            if (dataPermissionService.updateById(permissionDO)) {
                return JsonVO.success(id);
            }
        }
        return JsonVO.fail(null);
    }

    @Override
    @DeleteMapping("/remove")
    @ApiOperation("删除职位数据权限（支持批量删除）")
    @ApiImplicitParam(name = "ids", value = "职位数据权限ID列表", dataTypeClass = List.class, required = true)
    public JsonVO<List<Long>> removePositionDataPermission(@RequestBody List<Long> ids) {
        if (dataPermissionService.removeByIds(ids)) {
            return JsonVO.success(ids);
        }
        return JsonVO.fail(null);
    }
}
