package com.zeroone.star.academic.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.j4.academic.ClassroomApis;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * <p>
 * 描述：教室接口实现类
 * </p>
 * @author ab
 */
@RestController
@RequestMapping("/j4/classroom")
@Api(tags = "教室管理")
public class ClassroomController implements ClassroomApis {
    /**
     * 获取教室列表（条件+分页）
     * @param query 查询条件
     * @return 教室列表
     */
    @Override
    @GetMapping("/list")
    @ApiOperation("获取教室列表（条件+分页）")
    public JsonVO<PageDTO<ClassroomVO>> queryClassroom(ClassroomQuery query) {
        // TODO: 调用 service 层实现
        return null;
    }

    /**
     * 获取教室详情
     * @param id 教室ID
     * @return 教室详情
     */
    @Override
    @GetMapping("/{id}")
    @ApiOperation("获取教室详情")
    public JsonVO<ClassroomVO> getClassroomById(@PathVariable Long id) {
        // TODO: 调用 service 层实现
        return null;
    }

    /**
     * 保存教室
     * @param classroomDTO 教室数据传输对象
     * @return 教室ID
     */
    @Override
    @PostMapping("/save")
    @ApiOperation("保存教室")
    public JsonVO<Long> saveClassroom(@RequestBody @Validated ClassroomDTO classroomDTO) {
        // TODO: 调用 service 层实现
        return null;
    }

    /**
     * 删除教室
     * @param ids 教室ID列表
     * @return 删除结果
     */
    @Override
    @DeleteMapping("/delete")
    @ApiOperation("删除教室（批量）")
    @ApiImplicitParam(name = "ids", value = "教室ID列表",type = "Array",paramType = "body",required = true,example = "[\"1\", \"2\"]")
    public JsonVO<List<Long>> deleteClassroom(@RequestBody @Valid @NotEmpty(message = "删除 ID 列表不能为空") List<Long> ids) {
        // TODO: 调用 service 层实现
        return null;
    }
}
