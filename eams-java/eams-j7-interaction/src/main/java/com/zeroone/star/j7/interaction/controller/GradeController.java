package com.zeroone.star.j7.interaction.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeRecordSaveDTO;
import com.zeroone.star.project.j7.interaction.GradeApi;
import com.zeroone.star.project.query.j7.interaction.GradeRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.GradeRecordVO;
import com.zeroone.star.j7.interaction.service.GradeRecordService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import java.util.List;
import java.util.stream.Collectors;

@Api(tags = "成绩单管理")
@Validated
@RestController
@RequestMapping("/j7-interaction/j7-grade")
public class GradeController implements GradeApi {

    private final GradeRecordService gradeRecordService;

    // 构造器注入（Spring 最佳实践）
    public GradeController(GradeRecordService gradeRecordService) {
        this.gradeRecordService = gradeRecordService;
    }

    @ApiOperation("获取成绩列表（条件+分页）")
    @ApiOperationSupport(author = "开发人员", order = 1)
    @GetMapping("/list")
    public JsonVO<PageDTO<GradeRecordVO>> pageList(
            @ApiParam(value = "查询条件")
                    GradeRecordQuery query) {

        if (query == null) query = new GradeRecordQuery();
        if (query.getPageIndex() < 1) query.setPageIndex(1L);
        if (query.getPageSize() < 1) query.setPageSize(30L);

        return JsonVO.success(gradeRecordService.pageList(query));
    }

    @Override
    @PostMapping("/save-grade-list")
    @ApiOperation("保存成绩单")
    public JsonVO<Long> saveGrade(
        @ApiParam(value = "成绩单数据", required = true)
        @RequestBody GradeDTO gradeDTO){
        return gradeRecordService.saveGrade(gradeDTO);
    }

    @Override
    @DeleteMapping("/delete-grade-list")
    @ApiOperation("删除成绩单")
    public JsonVO<List<Long>> deleteGrade(
        @ApiParam(value = "要删除的成绩单 ID 列表", required = true)
        @RequestParam("ids") List<Long> ids){
        return gradeRecordService.deleteGrade(ids);
    }

    @Override
    @GetMapping("/get-grade-list")
    @ApiOperation("获取成绩列表")
    public JsonVO<PageDTO<GradeRecordVO>> queryPage(
        @ApiParam(value = "查询条件（分页 + 筛选），支持按考核项 ID、学生 ID 查询",
                  example = "{\"pageIndex\":1,\"pageSize\":30,\"gradeId\":1,\"studentId\":1001}")
        GradeRecordQuery condition){
        return JsonVO.success(gradeRecordService.pageList(condition));
    }


    @ApiOperation("导入成绩单")
    @PostMapping("/import")
    public JsonVO importExcel(@RequestParam("file") MultipartFile file, @RequestParam(value = "gradeId") Long gradeId) {
        try {
            gradeRecordService.importGradeRecord(file, gradeId);
            return JsonVO.success("成绩导入成功");
        } catch (Exception e) {
            return JsonVO.fail("成绩导入失败：" + e.getMessage());

        }
    }
    @ApiOperation("删除成绩")
    @Override
    @PostMapping("/delete")
    public JsonVO deleteRecord(List<Long> ids) {
        if (gradeRecordService.removeByIds(ids)) {
            return JsonVO.success("删除成功");
        } else {
            return JsonVO.fail("删除失败");
        }
    }
    @ApiOperation("保存成绩")
    @Override
    @PostMapping("/saveRecord")
    public JsonVO saveRecord(@Valid @RequestBody GradeRecordSaveDTO dto, BindingResult bindingResult) {
        // 处理DTO校验结果
        if (bindingResult.hasErrors()) {
            String errorMsg = bindingResult.getAllErrors().stream()
                    .map(error -> error.getDefaultMessage())
                    .collect(Collectors.joining("; "));
            return JsonVO.fail("保存失败：" + errorMsg);
        }
        try {
            if(gradeRecordService.saveOrUpdateByDTO(dto)){
                return JsonVO.success("保存成功");
            }else{
                return JsonVO.fail("保存失败");
            }
        } catch (RuntimeException e) {
            // 捕获业务异常（如学生不存在）
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            // 捕获其他未知异常
            return JsonVO.fail("保存失败：" + e.getMessage());
        }
    }
}
