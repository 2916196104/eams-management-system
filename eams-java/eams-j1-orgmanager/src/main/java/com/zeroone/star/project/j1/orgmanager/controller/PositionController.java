package com.zeroone.star.project.j1.orgmanager.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.j1.orgmanager.PositionApis;
import com.zeroone.star.project.j1.orgmanager.service.IPositionService;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.validation.annotation.Validated;

import javax.annotation.Resource;
import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * <p>
 * 描述：职位管理接口文档控制器
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@RestController
@Validated
@RequestMapping("/common/position")
@Api(tags = "职位管理")
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
    @ApiOperation(value = "职位列表", notes = "支持按职位名称模糊搜索，返回分页数据")
    @ApiOperationSupport(order = 2)
    @ApiImplicitParams({
            @ApiImplicitParam(name = "page", value = "页码", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", required = false, paramType = "query",
                    dataTypeClass = Integer.class, defaultValue = "30"),
            @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
                    dataTypeClass = String.class, defaultValue = "")
    })
    public JsonVO<PageDTO<PositionDTO>> list(@Valid PositionQueryCondition condition) {
        return JsonVO.success(positionService.list(condition));
    }

    @Override
    @PostMapping("/save")
    @ApiOperation(value = "创建和修改职位", notes = "ID为空时新增，有ID时修改")
    @ApiOperationSupport(order = 3)
    public JsonVO<String> save(@Valid @RequestBody PositionDTO dto) {
        boolean result = positionService.save(dto);
        return result ? JsonVO.success(dto.getId() == null ? "创建职位成功" : "修改职位成功") : JsonVO.fail("操作失败");
    }

    @Override
    @PostMapping("/delete")
    @ApiOperation(value = "删除职位", notes = "支持批量删除，传职位ID列表")
    @ApiOperationSupport(order = 4)
    public JsonVO<String> delete(@ApiParam(value = "职位ID列表", required = true, example = "[1,2,3]")
                                 @RequestBody @NotEmpty(message = "职位ID列表不能为空") List<@NotNull(message = "职位ID不能为空") Long> ids) {
        boolean result = positionService.delete(ids);
        return result ? JsonVO.success(String.format("成功删除 %d 个职位", ids.size())) : JsonVO.fail("删除职位失败");
    }
}
