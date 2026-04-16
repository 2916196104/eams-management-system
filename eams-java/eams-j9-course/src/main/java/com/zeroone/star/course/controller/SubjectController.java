package com.zeroone.star.course.controller;


import com.zeroone.star.course.service.ISubjectService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.subject.SubjectDTO;
import com.zeroone.star.project.j9.subject.SubjectApis;
import com.zeroone.star.project.query.j9.subject.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.subject.SubjectNameVO;
import com.zeroone.star.project.vo.j9.subject.SubjectVO;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import io.swagger.annotations.Api;

import javax.annotation.Resource;
import java.util.List;


@RestController
@RequestMapping("subject")
@Api(tags = "科目管理接口")
public class SubjectController implements SubjectApis {

    @Resource
    private ISubjectService subjectService;

    @Override
    @GetMapping("/names")
    @ApiOperation("获取科目名称列表（下拉框用）")
    public JsonVO<List<SubjectNameVO>> querySubjectNames() {
        return JsonVO.success(subjectService.listSubjectNames());
    }

    @Override
    @GetMapping("/list")
    @ApiOperation("分页查询科目列表（条件+分页）")
    public JsonVO<PageDTO<SubjectVO>> querySubjectPage(@Validated SubjectQuery condition) {
        return JsonVO.success(subjectService.listSubjectPage(condition));
    }

    @Override
    @PostMapping("/save")
    @ApiOperation("保存科目（新增/更新）")
    public JsonVO<Long> addSubject(@Validated @RequestBody SubjectDTO subjectDTO) {
        return JsonVO.success(subjectService.saveSubject(subjectDTO));
    }

    @Override
    @DeleteMapping("/delete")
    @ApiOperation("批量删除科目")
    public JsonVO<String> removeSubjects(
            @ApiParam(value = "科目ID列表", required = true) @RequestBody List<Long> ids) {
        if(ids == null || ids.isEmpty()){
            return JsonVO.fail("请选择要删除的科目");
        }
        boolean success = subjectService.removeSubjects(ids);
        return success ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }
}
