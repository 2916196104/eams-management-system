package com.zeroone.star.org.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.org.mapper.DataPermissionMapper;
import com.zeroone.star.org.mapstruct.DataPermissionConvert;
import com.zeroone.star.org.service.DataPermissionService;
import com.zeroone.star.project.Do.j1.PositionDataPermissionDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionSetDTO;
import com.zeroone.star.project.j1.org.PositionDataPermissionApis;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 描述：职位管理接口文档控制器
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@RestController
@RequestMapping("/common/position")
@Api(tags = "职位管理")
public class OrgManagerController implements PositionDataPermissionApis {

    @Resource
    DataPermissionService dataPermissionService;

    @Resource
    DataPermissionConvert dataPermissionConvert;

    @Override
    @GetMapping("/list")
    @ApiOperation(value = "职位列表", notes = "支持按职位名称模糊搜索，返回分页数据")
    @ApiOperationSupport(order = 1)
    @ApiImplicitParams({
            @ApiImplicitParam(name = "page", value = "页码", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "30"),
            @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
                    dataTypeClass = String.class, defaultValue = "")
    })
    public JsonVO<PageDTO<PositionDTO>> list(@Valid PositionQueryCondition condition) {
        List<PositionDTO> records = buildPositions();
        if (condition.getName() != null && !condition.getName().trim().isEmpty()) {
            records = records.stream()
                    .filter(item -> item.getName().contains(condition.getName().trim()))
                    .collect(Collectors.toList());
        }
        PageDTO<PositionDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(condition.getPage() == null ? 1L : condition.getPage().longValue());
        pageDTO.setPageSize(condition.getPageSize() == null ? 30L : condition.getPageSize().longValue());
        pageDTO.setTotal((long) records.size());
        pageDTO.setPages(1L);
        pageDTO.setRows(records);
        return JsonVO.success(pageDTO);
    }

    @Override
    @PostMapping("/save")
    @ApiOperation(value = "创建和修改职位", notes = "ID为空时新增，有ID时修改")
    @ApiOperationSupport(order = 2)
    public JsonVO<String> save(@Valid @RequestBody PositionDTO dto) {
        return JsonVO.success(dto.getId() == null ? "创建职位成功" : "修改职位成功");
    }

    @Override
    @PostMapping("/delete")
    @ApiOperation(value = "删除职位", notes = "支持批量删除，传职位ID列表")
    @ApiOperationSupport(order = 3)
    public JsonVO<String> delete(@ApiParam(value = "职位ID列表", required = true, example = "[1,2,3]")
                                 @RequestBody List<Long> ids) {
        return JsonVO.success(String.format("成功删除 %d 个职位", ids.size()));
    }

    @Override
    @PostMapping("/setStaffPosition")
    @ApiOperation(value = "设置员工职位", notes = "为员工设置所属组织和职位")
    @ApiOperationSupport(order = 4)
    public JsonVO<String> setStaffPosition(@Valid @RequestBody PositionSetDTO dto) {
        return JsonVO.success("设置员工职位成功");
    }

    private List<PositionDTO> buildPositions() {
        List<PositionDTO> list = new ArrayList<>();
        list.add(buildPosition(1L, "校长"));
        list.add(buildPosition(2L, "财务总监"));
        list.add(buildPosition(3L, "助教"));
        return list;
    }

    private PositionDTO buildPosition(Long id, String name) {
        PositionDTO positionDTO = new PositionDTO();
        positionDTO.setId(id);
        positionDTO.setName(name);
        return positionDTO;
    }


    @GetMapping("query")
    @ApiOperation("获取职位数据权限列 表（条件+分页）")
    @Override
    public JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition) {
        return JsonVO.success(dataPermissionService.listAll(condition));
    }

    @PostMapping("savePermission")
    @ApiOperation("保存职位数据权限 新增/修改")
    @Override
    public JsonVO<Long> addPositionDataPermission(@RequestBody PositionDataPermissionDTO positionDataPermissionDTO) {
        Long id = positionDataPermissionDTO.getId();

        PositionDataPermissionDO permissionDO = dataPermissionConvert.dtoToDo(positionDataPermissionDTO);
        // 新增
        if(id == null){
            if(dataPermissionService.save(permissionDO)){
                return JsonVO.success(permissionDO.getId());
            }
        }else{ // 修改
            if(dataPermissionService.updateById(permissionDO)){
                return JsonVO.success(id);
            }
        }
        return JsonVO.fail(null);
    }

    @DeleteMapping("remove")
    @ApiOperation("删除职位数据权限（支持批量删除）")
    @ApiImplicitParam(name = "ids",value = "职位数据权限对应的id列表",type = "Array",required = true,example = "1")
    @Override
    public JsonVO<List<Long>> removePositionDataPermission(@RequestBody List<Long> ids) {
        if(dataPermissionService.removeByIds(ids)){
            return JsonVO.success(ids);
        }
        return JsonVO.fail(null);
    }
}
