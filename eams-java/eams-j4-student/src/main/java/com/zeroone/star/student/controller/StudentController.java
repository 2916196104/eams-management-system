package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.student.service.IStudentService;
import com.zeroone.star.project.query.j4.student.ChangeCreditQuery;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.CreditSelectQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.MediaType;
import io.swagger.annotations.ApiParam;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {

    @Resource
    private IStudentService studentService;

    @GetMapping("/follow-up/page")
    @ApiOperation("获取跟进记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(FollowUpQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody FollowUpDTO followUpDTO) {
        // TODO: 调用 Service 层实现业务逻辑
        // 如果 DTO 中有 ID 则更新，无 ID 则新增
        return null;
    }

    @DeleteMapping("/follow-up")
    @ApiOperation("删除跟进记录（支持批量删除）")
    @ApiImplicitParam(name = "ids", value = "跟进记录ID列表", type = "Array", paramType = "body", required = true, example = "[\"1\",\"2\"]")
    @Override
    public JsonVO<List<Long>> deleteFollowUp(@RequestBody List<Long> ids) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @GetMapping("/follow-up/{id}")
    @ApiOperation("获取跟进记录详情")
    @Override
    public JsonVO<FollowUpDTO> getFollowUpDetail(@PathVariable Long id) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }
    @GetMapping("/page")
    @ApiOperation("获取班级列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<ClassDTO>> queryClassPage(ClassQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
        // 示例返回结构，实际需替换为 Service 调用
        return null;
    }
    @GetMapping("/queryOmyLessonCount")
    @ApiOperation("获取消课记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonCountDTO>> queryOmyLessonCount(@RequestParam(value = "2026010206",required = true) String StudentID) {
        return null;
    }

    @GetMapping("/queryCreditLog")
    @ApiOperation("获取积分记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<CreditLogDTO>> queryCreditLog(@RequestBody CreditSelectQuery creditSelectQuery) {
        return null;
    }

    @PostMapping("/saveCreditLog")
    @ApiOperation("调整积分")
    @Override
    public JsonVO<Long> saveCreditLog(@RequestBody ChangeCreditQuery changeCreditQuery) {
        return null;
    }

    @PostMapping("/modifyConsultant")
    @ApiOperation("修改学员顾问")
    @Override
    public JsonVO<String> modifyConsultant(@RequestBody StudentDTO studentDTO) {
        Boolean result = studentService.modifyConsultant(studentDTO);
        if(result) {
            return JsonVO.success(studentDTO.getId());
        }
        return JsonVO.fail(null);
    }

    @PostMapping("/importOnlineStudents")
    @ApiOperation("导入在学学员")
    @Override
    public JsonVO<String> importOnlineStudents(@RequestPart("file") MultipartFile file) {
        Boolean result = studentService.importOnlineStudents(file);
        if(result) {
            return JsonVO.success("在线学员导入成功");
        }
        return JsonVO.fail("在线学员导入失败");
    }

    @GetMapping("/exportOnlineStudents")
    @ApiOperation("导出在学学员")
    @Override
    public ResponseEntity<byte[]> exportOnlineStudents() {
        byte[] data = studentService.exportOnlineStudent();
        if(data != null && data.length > 0) {
            return ResponseEntity.ok()
                    .contentType(MediaType.APPLICATION_OCTET_STREAM)
                    .header("Content-Disposition", "attachment; filename=\"online_students.xlsx\"")
                    .body(data);
        } else {
            return ResponseEntity.noContent().build();
        }
    }

    @PostMapping("/student/join")
    @ApiOperation("加入班级")
    @Override
    public JsonVO<Long> joinClass(@RequestBody ClassStudentDTO dto) {
        // TODO: 调用 Service 层实现业务逻辑
        // 检查是否已存在，不存在则插入 class_student 表
        return null;
    }

    @DeleteMapping("/student/quit")
    @ApiOperation("退出班级")
    @Override
    public JsonVO<List<Long>> quitClass(
            @ApiParam(value = "班级ID", required = true, example = "2008418408985583620") @RequestParam Long classId,
            @ApiParam(value = "学生ID", required = true, example = "2008418408985583617") @RequestParam Long studentId) {
        // TODO: 调用 Service 层实现业务逻辑
        // 根据 classId 和 studentId 逻辑删除或物理删除 class_student 表记录
        return null;
    }

    @ApiOperation(value = "意向学员-导出全部")
    @GetMapping(value = "/export-intention", produces = MediaType.APPLICATION_OCTET_STREAM_VALUE)
    public void exportIntentionStudent(HttpServletResponse response) throws Exception {

        studentService.exportIntentionStudent(response);
    }

    @ApiOperation(value = "意向学员-批量导入")
    @PostMapping(value = "/import-intention", consumes = MediaType.MULTIPART_FORM_DATA_VALUE, produces = MediaType.APPLICATION_OCTET_STREAM_VALUE)
    public void importIntentionStudent(@RequestPart("file") MultipartFile file, HttpServletResponse response) throws Exception {
        studentService.importIntentionStudent(file, response);
    }
}