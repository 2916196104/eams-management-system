package com.zeroone.star.project.j1.orgmanager.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.WorkStationDTO;
import com.zeroone.star.project.j1.orgmanager.WorkStationApis;
import com.zeroone.star.project.query.j1.orgmanager.WorkStationQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

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
@RequestMapping("/workstation")
@Api(tags = "职位管理")
public class WorkStationController implements WorkStationApis {
    @Override
    @GetMapping("/query-page")
    @ApiOperation(value = "分页查询职位", notes = "支持按职位名称模糊搜索，返回分页数据")
    @ApiOperationSupport(order = 1)
    @ApiImplicitParams({
            @ApiImplicitParam(name = "pageIndex", value = "页码", required = false, paramType = "query",
                    dataTypeClass = Long.class, defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", required = false, paramType = "query",
                    dataTypeClass = Long.class, defaultValue = "10"),
            @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
                    dataTypeClass = String.class, defaultValue = "校长")
    })
    public JsonVO<PageDTO<WorkStationDTO>> queryWorkStationPage(@Valid WorkStationQueryCondition condition) {
        List<WorkStationDTO> records = buildWorkStations();
        if (condition.getName() != null && !condition.getName().trim().isEmpty()) {
            records = records.stream()
                    .filter(item -> item.getName().contains(condition.getName().trim()))
                    .collect(Collectors.toList());
        }
        PageDTO<WorkStationDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(condition.getPageIndex() == 0 ? 1L : condition.getPageIndex());
        pageDTO.setPageSize(condition.getPageSize() == 0 ? 10L : condition.getPageSize());
        pageDTO.setTotal((long) records.size());
        pageDTO.setPages(1L);
        pageDTO.setRows(records);
        return JsonVO.success(pageDTO);
    }

    @Override
    @PostMapping("/save")
    @ApiOperation(value = "保存职位", notes = "ID为空时新增，有ID时修改")
    @ApiOperationSupport(order = 2)
    public JsonVO<String> saveWorkStation(@Valid @RequestBody WorkStationDTO workStationDTO) {
        return JsonVO.success(workStationDTO.getId() == null ? "新增职位成功" : "修改职位成功");
    }

    @Override
    @DeleteMapping("/delete")
    @ApiOperation(value = "删除职位", notes = "支持批量删除，传职位ID列表")
    @ApiOperationSupport(order = 3)
    public JsonVO<String> removeWorkStations(@ApiParam(value = "职位ID列表", required = true, example = "[1,2,3]")
                                             @RequestBody List<Long> ids) {
        return JsonVO.success(String.format("成功删除 %d 个职位", ids.size()));
    }

    @Override
    @GetMapping("/query-name-list")
    @ApiOperation(value = "获取职位名称列表", notes = "用于下拉选框，名称为可选参数，无分页")
    @ApiOperationSupport(order = 4)
    @ApiImplicitParam(name = "name", value = "职位名称", required = false, paramType = "query",
            dataTypeClass = String.class, defaultValue = "校")
    public JsonVO<List<WorkStationDTO>> queryWorkStationNameList(String name) {
        List<WorkStationDTO> records = buildWorkStations();
        if (name != null && !name.trim().isEmpty()) {
            records = records.stream()
                    .filter(item -> item.getName().contains(name.trim()))
                    .collect(Collectors.toList());
        }
        return JsonVO.success(records);
    }

    private List<WorkStationDTO> buildWorkStations() {
        List<WorkStationDTO> list = new ArrayList<>();
        list.add(buildWorkStation(1L, "校长"));
        list.add(buildWorkStation(2L, "财务总监"));
        list.add(buildWorkStation(3L, "助教"));
        return list;
    }

    private WorkStationDTO buildWorkStation(Long id, String name) {
        WorkStationDTO workStationDTO = new WorkStationDTO();
        workStationDTO.setId(id);
        workStationDTO.setName(name);
        return workStationDTO;
    }
}
