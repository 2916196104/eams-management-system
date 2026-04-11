package com.zeroone.star.project.j1.orgmanager.controller;
import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.project.DO.PositionDataPermissionDO;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.j1.orgmanager.PositionApis;
import com.zeroone.star.project.j1.orgmanager.mapstruct.DataPermissionConvert;
import com.zeroone.star.project.j1.orgmanager.service.DataPermissionService;
import com.zeroone.star.project.j1.orgmanager.service.IPositionService;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.extern.slf4j.Slf4j;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

@RestController
@Validated
@RequestMapping("/org/position")
@Api(tags = "职位管理")
@Slf4j

public class PositionController implements PositionApis {
    @Resource
    private IPositionService positionService;

    @Override
    @GetMapping("/names")
    @ApiOperation(value = "获取职位名称", notes = "用于下拉选择职位名称，可按名称模糊筛选")
    @ApiOperationSupport(order = 1)
    @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
            dataTypeClass = String.class, defaultValue = "")
    public JsonVO<List<String>> listNames(String name) {
        return JsonVO.success(positionService.listNames(name));
    }

    @Override
    @GetMapping("/list")
    @ApiOperation(value = "获取职位列表", notes = "支持按职位名称模糊搜索，返回分页数据")
    @ApiOperationSupport(order = 2)
    @ApiImplicitParams({
            @ApiImplicitParam(name = "page", value = "页码", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "30"),
            @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
                    dataTypeClass = String.class, defaultValue = "")
    })
    public JsonVO<PageDTO<PositionDTO>> list(PositionQueryCondition condition) {
        return JsonVO.success(positionService.list(condition));
    }

    @Override
    @PostMapping("/save")
    @ApiOperation(value = "保存职位", notes = "ID为空时新增，有ID时修改")
    @ApiOperationSupport(order = 3)
    public JsonVO<String> save(@RequestBody PositionDTO dto) {
        boolean result = positionService.save(dto);
        return result ? JsonVO.success(dto.getId() == null ? "创建职位成功" : "修改职位成功") : JsonVO.fail("操作失败");
    }

    @Override
    @DeleteMapping("/delete")
    @ApiOperation(value = "批量删除职位", notes = "支持批量删除，传职位ID列表")
    @ApiOperationSupport(order = 4)
    public JsonVO<String> delete(@ApiParam(value = "职位ID列表", required = true, example = "[1,2,3]")
                                 @RequestBody List<Long> ids) {
        boolean result = positionService.delete(ids);
        return result ? JsonVO.success(String.format("成功删除 %d 个职位", ids.size())) : JsonVO.fail("删除职位失败");
    }

    /*  下面是职位数据权限的Controller   */

    @Resource
    private DataPermissionService dataPermissionService;

    @Resource
    private DataPermissionConvert dataPermissionConvert;

    @Resource
    private UserHolder userHolder;

    @Override
    @GetMapping("/queryPermission")
    @ApiOperation("获取职位数据权限列表（条件+分页）")
    public JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition) {
        return JsonVO.success(dataPermissionService.listAll(condition));
    }

    @Override
    @PostMapping("/savePermission")
    @ApiOperation("保存职位数据权限（新增/修改）")
    public JsonVO<Long> addPositionDataPermission(@RequestBody PositionDataPermissionDTO positionDataPermissionDTO) throws Exception {
        Long id = positionDataPermissionDTO.getId();
        PositionDataPermissionDO permissionDO = dataPermissionConvert.dtoToDo(positionDataPermissionDTO);
        if (id == null) {
            // 【安全获取当前用户】
            UserDTO userDTO = userHolder.getCurrentUser();
            if (userDTO == null) {
                throw new RuntimeException("获取登录用户信息失败，请重新登录");
            }

            // 【安全获取 orgId】
            Long orgId = userDTO.getOrgId();
            if (orgId == null) {
                throw new RuntimeException("当前用户部门ID为空，无法保存");
            }

            // 赋值给 positionId
            permissionDO.setPositionId(orgId);
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
    @DeleteMapping("/removePermission")
    @ApiOperation("删除职位数据权限（支持批量删除）")
    @ApiImplicitParam(name = "ids", value = "职位数据权限ID列表", dataTypeClass = List.class, required = true)
    public JsonVO<List<Long>> removePositionDataPermission(@RequestBody List<Long> ids) {
        if (dataPermissionService.removeByIds(ids)) {
            return JsonVO.success(ids);
        }
        return JsonVO.fail(null);
    }

}
