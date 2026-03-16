package com.zeroone.star.sample.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.WorkPositionDTO;
import com.zeroone.star.project.j1.org.WorkPositionApis;
import com.zeroone.star.project.query.j1.org.WorkPositionQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：职位相接口实现类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@RestController
@RequestMapping("/j1/wp")
@Api(tags = "职位管理")
public class WorkPositionController implements WorkPositionApis {

    @GetMapping
    @ApiOperation("获取职位列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<WorkPositionDTO>> queryPage(WorkPositionQuery condition) {
        return null;
    }

    @GetMapping("/name")
    @ApiOperation("获取职位名称")
    @Override
    public JsonVO<List<WorkPositionDTO>> queryNameList(@RequestParam(value = "name", required = false) String name) {
        return null;
    }

    @PostMapping
    @ApiOperation("保存职位")
    @Override
    public JsonVO<Long> saveWorkPosition(@RequestBody WorkPositionDTO workPositionDTO) {
        return null;
    }

    @DeleteMapping
    @ApiOperation("删除职位（支持批量删除）")
    @ApiImplicitParam(name = "ids", value = "职位ID列表", type = "Array", paramType = "body", required = true, example = "[\"1\",\"2\"]")
    @Override
    public JsonVO<List<Long>> deleteWorkPosition(@RequestBody List<Long> ids) {
        return null;
    }
}
