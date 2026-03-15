package com.zeroone.star.academic.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.j4.academic.ClassroomApis;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

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
    @Override
    @GetMapping("/list")
    @ApiOperation("获取教室列表（条件+分页）")
    public JsonVO<PageDTO<ClassroomVO>> queryClassroom(ClassroomQuery query) {
        // TODO: 调用 service 层实现
        return null;
    }

    @Override
    @GetMapping("/{id}")
    @ApiOperation("获取教室详情（用于编辑数据回显）")
    public JsonVO<ClassroomVO> getClassroomById(@PathVariable Long id) {
        // TODO: 调用 service 层实现
        return null;
    }

    @Override
    @PostMapping("/save")
    @ApiOperation("保存教室")
    public JsonVO<Long> saveClassroom(@RequestBody @Validated ClassroomDTO classroomDTO) {
        // TODO: 调用 service 层实现
        return null;
    }

    @Override
    @DeleteMapping("/delete")
    @ApiOperation("删除教室（批量）")
    public JsonVO<List<Long>> deleteClassroom(@RequestBody List<Long> ids) {
        // TODO: 调用 service 层实现
        return null;
    }
}
