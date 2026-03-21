package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.dto.j8.stumanager.OnlineStu.StudentAdvisorDTO;
import com.zeroone.star.project.j8.stumanager.OnlineStuApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

/**
 * 在线学员
 */
@RestController
@RequestMapping("/atu/online-stu")
@Api(tags = "在线学员")
public class OnlineStuController implements OnlineStuApis {
    @ApiOperation(value = "修改学员顾问", notes = "根据学员ID修改对应学员的顾问信息")
    @PutMapping("update-advisor")
    @Override
    public JsonVO<String> updateStudentAdvisor(@RequestBody StudentAdvisorDTO studentAdvisorDTO) {
        // TODO: 实现修改顾问逻辑
        return JsonVO.success("修改顾问成功");
    }

    @ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据")
    @PostMapping("import")
    @Override
    public JsonVO<String> importStudents(@ApiParam(value = "学员数据Excel文件", required = true) MultipartFile file) {
        // TODO: 实现导入学员逻辑
        return JsonVO.success("导入学员成功");
    }

    @ApiOperation(value = "导出学员", notes = "根据条件导出学员数据为Excel文件")
    @GetMapping("export")
    @Override
    public JsonVO<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition) {
        // TODO: 实现导出学员逻辑
        return JsonVO.success(new byte[0]);
    }
}
