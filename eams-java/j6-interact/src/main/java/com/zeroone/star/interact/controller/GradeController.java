package com.zeroone.star.interact.controller;

import com.baomidou.mybatisplus.extension.plugins.pagination.PageDTO;
import com.zeroone.star.interact.service.IGradeRecordService;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.j6.interact.GradeApis;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("j6/grade")
@Api(tags = "成绩单")
public class GradeController implements GradeApis {

    @Resource
    private IGradeRecordService gradeRecordService;

    /**
     * 获得成绩单列表（条件+分页）
     *
     * @param condition 查询条件
     * @return 成绩单列表
     */
    @GetMapping
    @ApiOperation("获取成绩单列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<GradeFormDTO>> queryForm(GradeFormQuery condition) {
        return null;
    }

    /**
     * 分页查询成绩信息
     *
     * @param id 成绩单id
     * @return 返回结果
     */
    @GetMapping("/{id}")
    @ApiOperation("获取成绩列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<GradeListDTO>> queryGrade(@PathVariable("id") Long id) {
        return null;
    }

    /**
     * 保存成绩单信息，新增和修改成绩单走这里
     *
     * @param gradeFormDTO 成绩单信息
     * @return 保存结果
     */
    @PostMapping("/form")
    @ApiOperation("保存成绩单")
    @Override
    public JsonVO<Long> saveGrade(@RequestBody GradeFormDTO gradeFormDTO) {
        return null;
    }

    /**
     * 删除成绩单
     *
     * @param ids 成绩单id列表
     * @return 返回结果
     */
    @DeleteMapping("/form")
    @ApiOperation("删除成绩单")
    @Override
    public JsonVO<List<Long>> deleteGrade(@RequestBody List<Long> ids) {
        return null;
    }

    /**
     * 保存成绩
     *
     * @param gradeRecordDTO 成绩数据对象
     * @return
     */
    @PostMapping("/record")
    @ApiOperation("保存成绩")
    @Override
    public JsonVO<String> saveGradeRecord(GradeRecordDTO gradeRecordDTO) {
        return gradeRecordService.saveGradeRecord(gradeRecordDTO);
    }

    /**
     * 删除成绩,支持批量删除
     *
     * @param ids
     * @return
     */
    @DeleteMapping("/record")
    @ApiOperation("删除成绩")
    @Override
    public JsonVO<List<Long>> deleteGradeRecord(@RequestBody List<Long> ids) {
       return  gradeRecordService.deleteGradeRecord(ids);
    }

    /**
     * 导入成绩
     *
     * @param gradeId
     * @param gradeRecords
     * @return
     */
    @PostMapping("/file")
    @ApiOperation("导入成绩")
    @Override
    public JsonVO<Map<Long, Object>> addGrades( @RequestParam Long gradeId,
                                                @RequestBody List<GradeRecordDTO> gradeRecords) {
        return gradeRecordService.addGrades(gradeId, gradeRecords);
    }

}
