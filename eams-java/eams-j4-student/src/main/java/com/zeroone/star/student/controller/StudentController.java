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
    @GetMapping("/follow-up/page")
    @ApiOperation("获取跟进记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(FollowUpQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
        // 模拟返回，实际需替换为 service.queryFollowUpPage(condition)
        return null;
    }

    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody FollowUpDTO followUpDTO) {
        // TODO: 调用 Service 层实现业务逻辑
        // 如果 followUpDTO.getId() != null 则更新，否则新增
        return null;
    }

    @DeleteMapping("/follow-up/{id}")
    @ApiOperation("删除跟进记录（单个删除）")
    @Override
    public JsonVO<Long> deleteFollowUp(@PathVariable Long id) {
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


    @Override
    @GetMapping("/page")
    @ApiOperation("获取班级列表（条件 + 分页）")
    public JsonVO<PageDTO<ClassDTO>> queryClassPage(ClassQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
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

    @Override
    public JsonVO<String> modifyConsultant(StudentDTO studentDTO) {
        return null;
    }

    @Override
    public JsonVO<String> importOnlineStudents(MultipartFile file) {
        return null;
    }

    @Override
    public ResponseEntity<byte[]> exportOnlineStudents() {
        return null;
    }

    @Override
    @PostMapping("/join")
    @ApiOperation("加入班级")
    public JsonVO<Long> joinClass(@RequestBody ClassStudentDTO dto) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @Override
    @DeleteMapping("/quit")
    @ApiOperation("退出班级")
    public JsonVO<List<Long>> quitClass(
            @ApiParam(value = "班级ID", required = true, example = "2008418408985583620") @RequestParam Long classId,
            @ApiParam(value = "学生ID", required = true, example = "2008418408985583617") @RequestParam Long studentId) {
        // TODO: 调用 Service 层
        // 模拟返回删除成功的记录 ID
        return null;
    }
    @Resource
    private IStudentService studentService;

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