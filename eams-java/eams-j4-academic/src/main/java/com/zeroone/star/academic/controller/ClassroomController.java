package com.zeroone.star.academic.controller;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.academic.service.ClassroomService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.j4.academic.ClassroomApis;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import javax.validation.constraints.Min;
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
    @Autowired
    private ClassroomService classroomService;

    /**
     * 获取教室列表（条件+分页）
     * @param pageIndex    分页参数，第几页，默认第一页
     * @param pageSize 分页参数，每页数量，默认30条
     * @param name    查询参数，教室名称，默认空值
     * @return 教室列表分页结果对象
     * @return 教室列表
     */
    @Override
    @Validated
    @GetMapping("/list")
    @ApiOperation("获取教室列表（条件+分页）")
    public JsonVO<PageDTO<ClassroomVO>> queryClassroom(
            @ApiParam(value = "页码", required = true, example = "1")
            @RequestParam("pageIndex")
            @Min(value = 1, message = "页码最小值为1") Long pageIndex,

            @ApiParam(value = "每页条数", required = true, example = "30")
            @RequestParam("pageSize")
            @Min(value = 1, message = "每页条数最小值为1") Long pageSize,

            @ApiParam(value = "教室名称", example = "教学楼")
            @RequestParam(value = "name", defaultValue = "") String name) {

        ClassroomQuery query = new ClassroomQuery();
        query.setPageIndex(pageIndex);
        query.setPageSize(pageSize);
        query.setName(name);

        IPage<ClassroomVO> list = classroomService.getList(query);
        PageDTO<ClassroomVO> result = new PageDTO<>();
        result.setPageIndex(list.getCurrent());
        result.setPageSize(list.getSize());
        result.setTotal(list.getTotal());
        result.setPages(list.getPages());
        result.setRows(list.getRecords());
        return JsonVO.success(result);
    }


    /**
     * 获取教室详情
     * @param id 教室ID
     * @return 教室详情
     */
    @Override
    @GetMapping("/{id}")
    @ApiOperation("获取教室详情")
    public JsonVO<ClassroomVO> getClassroomById(@PathVariable @Min(value = 1, message = "ID最小值为1") Long id) {
        ClassroomVO classroomVO = classroomService.getClassroomById(id);
        return JsonVO.success(classroomVO);
    }

    /**
     * 保存教室
     * @param classroomDTO 教室数据传输对象
     * @return 教室ID
     */
    @Override
    @PostMapping("/save")
    @ApiOperation("保存教室")
    public JsonVO<Boolean> saveClassroom(@RequestBody @Validated ClassroomDTO classroomDTO) {
        return JsonVO.success(classroomService.save(classroomDTO));
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
    public JsonVO deleteClassroom(@RequestBody @Valid @NotEmpty(message = "删除 ID 列表不能为空") List<Long> ids) {
        if (classroomService.removeByIds(ids)) {
            return JsonVO.success(ids);
        } else {
            return JsonVO.fail(ids);
        }
    }
}
