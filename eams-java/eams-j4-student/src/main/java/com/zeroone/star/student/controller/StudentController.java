package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.GraduateStudentImportBatchDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.*;
import com.zeroone.star.project.vo.j4.student.*;
import com.zeroone.star.student.mapper.IOmyMapper;
import com.zeroone.star.student.service.*;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.apache.commons.lang.StringUtils;
import org.apache.poi.util.StringUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.MediaType;
import io.swagger.annotations.ApiParam;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.bind.annotation.RestController;
import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import javax.validation.constraints.NotNull;
import java.io.IOException;
import java.io.OutputStream;
import java.math.BigDecimal;
import java.net.URLEncoder;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;

import java.util.List;

/**
 * <p>
 * 学生表 前端控制器
 * </p>
 * @author gintoki
 * @since 2026-03-23
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
@Validated
public class StudentController implements StudentApis {
    @Resource
    private IStudentService studentService;

    @Autowired
    private StudentGraduationService studentGraduationService;


    @Resource
    private IStudentFinanceService studentFinanceService;
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    private static final DateTimeFormatter DATETIME_FORMATTER = DateTimeFormatter.ofPattern("yyyyMMddHHmmss");


    @ApiOperation(value = "分页查询缴欠费与线下退费记录")
    @GetMapping("/finance/page")
    @Override
    public JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query) {
        return JsonVO.success(studentFinanceService.queryFinancePage(query));
    }

    @ApiOperation(value = "办理缴欠费")
    @PostMapping("/finance/pay-debt")
    @Override
    public JsonVO<FinanceDTO> payDebt(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.payDebt(financeDTO));
    }

    @ApiOperation(value = "发起退费申请")
    @PostMapping("/refund/apply")
    @Override
    public JsonVO<FinanceDTO> applyRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.applyRefund(financeDTO));
    }

    @GetMapping("/follow-up/page")
    @ApiOperation("获取跟进记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(@Validated FollowUpQuery condition) {
        return JsonVO.success(studentService.queryFollowUpPage(condition));
    }


    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody @Validated FollowUpDTO followUpDTO) {
        // 基本业务校验
        if (followUpDTO.getStudentId() == null) return JsonVO.fail("学生ID不能为空");
        if (followUpDTO.getContactTime() == null) return JsonVO.fail("联系时间不能为空");

        Long id = studentService.saveFollowUp(followUpDTO);
        return JsonVO.success(id);
    }

    @DeleteMapping("/follow-up/{id}")
    @ApiOperation("删除跟进记录（单个删除）")
    @Override
    public JsonVO<Long> deleteFollowUp(@PathVariable Long id) {
        try {
            return JsonVO.success(studentService.removeFollowUp(id));
        } catch (Exception e) {
            return JsonVO.fail("删除失败：" + e.getMessage());
        }
    }

    @GetMapping("/follow-up/{id}")
    @ApiOperation("获取跟进记录详情")
    @Override
    public JsonVO<FollowUpDTO> getFollowUpDetail(@PathVariable Long id) {
        FollowUpDTO detail = studentService.getFollowUpDetail(id);
        return detail != null ? JsonVO.success(detail) : JsonVO.fail("记录不存在");
    }

    @Override
    @GetMapping("/class/page")
    @ApiOperation("获取班级列表（条件 + 分页）")
    public JsonVO<PageDTO<ClassDTO>> queryClassPage(@Validated ClassQuery condition) {
        try {
            PageDTO<ClassDTO> result = studentService.queryClassPage(condition);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    @Override
    @PostMapping("/class/join")
    @ApiOperation("加入班级")
    public JsonVO<Long> joinClass(@RequestBody @Validated ClassStudentDTO dto) {
        try {
            if (dto.getClassId() == null) {
                return JsonVO.fail("班级ID不能为空");
            }
            if (dto.getStudentId() == null) {
                return JsonVO.fail("学生ID不能为空");
            }
            Long result = studentService.joinClass(dto);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            return JsonVO.fail("加入班级失败：" + e.getMessage());
        }
    }

    @Override
    @DeleteMapping("/class/quit")
    @ApiOperation("退出班级")
    public JsonVO<List<Long>> quitClass(
            @ApiParam(value = "班级 ID", required = true, example = "2008418408985583620")
            @RequestParam @NotNull(message = "班级ID不能为空") Long classId,
            @ApiParam(value = "学生 ID", required = true, example = "2008418408985583617")
            @RequestParam @NotNull(message = "学生ID不能为空") Long studentId) {
        try {
            List<Long> result = studentService.quitClass(classId, studentId);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            return JsonVO.fail("退出班级失败：" + e.getMessage());
        }
    }

    @Resource
    IOmyServcie IOmyServcie;

    @GetMapping("/queryOmyLessonCount")
    @ApiOperation("获取消课记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonCountDTO>> queryOmyLessonCount(@RequestParam(value = "2026010206") String StudentID) {

        if(StringUtils.isBlank(StudentID)){
            return JsonVO.fail("学生ID不能为空");
        }
        PageDTO<LessonCountDTO> lessonCountDTOPageDTO = IOmyServcie.PageLessonCount(StudentID);
        return JsonVO.success(lessonCountDTOPageDTO);
    }

    @Resource
    ISclServcie iSclServcie;

    @GetMapping("/queryCreditLog")
    @ApiOperation("获取积分记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<CreditLogDTO>> queryCreditLog(@RequestBody CreditSelectQuery creditSelectQuery) {
        if(creditSelectQuery.getStudent_Name() == null){
            creditSelectQuery.setStudent_Name("");
        }
        if (creditSelectQuery.getBegin_time() != null && creditSelectQuery.getEnd_time() != null) {
            // 比较开始时间是否大于结束时间
            if (creditSelectQuery.getBegin_time().compareTo(creditSelectQuery.getEnd_time()) > 0) {
                return JsonVO.fail("开始时间不能大于结束时间");
            }
        }
        PageDTO<CreditLogDTO> pageDTOPageDTO = iSclServcie.PageCreditLog(creditSelectQuery);
        return JsonVO.success(pageDTOPageDTO);
    }

    @PostMapping("/saveCreditLog")
    @ApiOperation("调整积分")
    @Override
    public JsonVO<Long> saveCreditLog(@RequestBody ChangeCreditQuery changeCreditQuery) {
        if(changeCreditQuery.getStudent_id().isEmpty()){
            return JsonVO.fail("学生学号不能为空");
        }
        if(changeCreditQuery.getChange_credit().isEmpty()){
            return JsonVO.fail("调整积分数不能为空");
        }
        if(iSclServcie.saveCreditLog(changeCreditQuery)){
            return JsonVO.success(200L);
        }
        return JsonVO.success(-1L);
    }

    @PostMapping("/modifyConsultant")
    @ApiOperation("修改学员顾问")
    @Override
    public JsonVO<String> modifyConsultant(@RequestBody StudentDTO studentDTO) {
        Boolean result = studentService.modifyConsultant(studentDTO);
        if(result) {
            return JsonVO.success("学员顾问修改成功");
        }
        return JsonVO.fail("学员顾问修改失败");
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
    /**
     * 保存学员信息
     * @param dto 学员DTO（包含ID、姓名等基础信息）
     * @return 保存结果
     */
    @Override
    public JsonVO<String> saveStudent(StudentDTO dto) {
        // 安全处理：防止dto或字段为空导致NPE
        String studentId = (dto.getStudentId() == null) ? "未知ID" : dto.getStudentId();
        String studentName = (dto.getStudentName() == null) ? "未知姓名" : dto.getStudentName();
        return JsonVO.success(String.format("学员保存成功：ID=%s，姓名=%s", studentId, studentName));
    }

    /**
     * 查询学员课程次数
     * @param studentId 学员ID（字符串类型）
     * @return 学员课次详情
     */
    @Override
    public JsonVO<StudentDetailVO> queryCourseTimes(String studentId) {
        // 安全处理：防止studentId为空
        String targetStudentId = (studentId == null) ? "默认ID" : studentId;

        // 构造返回VO（给所有字段赋值，避免空对象序列化报错）
        StudentDetailVO vo = new StudentDetailVO();
        vo.setStudentId(targetStudentId);
        vo.setStudentName("测试学员");
        vo.setCourseTimes(20); // 课程次数（示例值）
        vo.setRemainingTimes(5); // 剩余次数（示例值）

        return JsonVO.success(vo);
    }

    /**
     * 分页查询学员课时汇总
     * @param query 查询条件（包含学员ID+分页参数）
     * @return 分页课时汇总数据
     */
    @Override
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 1. 安全处理查询参数：PageQuery 是 long 基本类型，永远不会为 null
        // 直接使用 query 自带的 pageIndex/pageSize（已被 @Min 约束保证 ≥1）
        long pageIndex = query.getPageIndex();
        long pageSize = query.getPageSize();
        String studentId = (query.getStudentId() == null) ? "" : query.getStudentId();

        // 2. 构造课时汇总VO（给核心字段赋值）
        LessonSummaryVO summaryVO = new LessonSummaryVO();
        summaryVO.setStudentId(studentId);
        summaryVO.setTotalHour(15.5); // 总课时（示例值）
        summaryVO.setUsedHour(8.0);   // 已用课时（示例值）
        summaryVO.setRemainingHour(7.5); // 剩余课时（示例值）
        List<LessonSummaryVO> dataList = Collections.singletonList(summaryVO);

        // 3. 构造分页DTO（类型匹配，无需装箱）
        PageDTO<LessonSummaryVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(pageIndex);
        pageDTO.setPageSize(pageSize);
        pageDTO.setTotal(1L); // 总条数
        pageDTO.setPages(1L); // 总页数
        pageDTO.setRows(dataList); // 当前页数据

        // 4. 返回分页结果
        return JsonVO.success(pageDTO);
    }
    @Override
    @GetMapping("/studentList")
    @ApiOperation("获取开通指定课程学员列表（条件+分页）")
    public JsonVO<PageDTO<StudentDTO>> queryCourseStudent(@Validated CourseQuery condition) {
        return JsonVO.success(studentService.queryCourseStu(condition));
    }

    @Override
    @GetMapping("/list")
    @ApiOperation("获取学员列表（条件+分页）")
    public JsonVO<PageDTO<ResponseDTO>> listAllStudent(@Validated StudentQuery condition) {
        return JsonVO.success(studentService.listall(condition));
    }


    @Override
    @PutMapping("/avatar")
    @ApiOperation("修改学员头像")
    public JsonVO<String> updateStudentAvatar(@RequestBody StudentDTO studentDTO) {
        // 参数校验
        if (studentDTO == null || studentDTO.getId() == null) {
            return JsonVO.fail("学员ID不能为空");
        }
        if (studentDTO.getHeadImg() == null || studentDTO.getHeadImg().trim().isEmpty()) {
            return JsonVO.fail("头像URL不能为空");
        }

        // TODO: 调用Service层修改学员头像
        // studentService.updateStudentAvatar(studentDTO);

        // 模拟成功返回
        return JsonVO.success("修改成功");
    }

    @Override
    @GetMapping("/enroll/list")
    @ApiOperation("分页查询报名记录")
    public JsonVO<PageDTO<EnrollmentDTO>> queryEnrollRecords(EnrollQuery query) {
        // 参数校验
        if (query == null) {
            return JsonVO.fail("查询条件不能为空");
        }

        // TODO: 调用Service层分页查询报名记录
        // PageDTO<EnrollmentDTO> pageDTO = studentService.queryEnrollRecords(query);

        // 模拟数据（实际开发中需要删除）
        PageDTO<EnrollmentDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(query.getPageIndex());
        pageDTO.setPageSize(query.getPageSize());
        pageDTO.setTotal(100L);
        pageDTO.setPages(10L);

        List<EnrollmentDTO> records = new ArrayList<>();
        EnrollmentDTO dto1 = new EnrollmentDTO();
        dto1.setId(1L);
        dto1.setStudentName("张三");
        dto1.setCourseName("美术基础班");
        dto1.setSubjectName("美术");
        dto1.setAddTime(LocalDateTime.now());
        dto1.setAmount(new BigDecimal("3000.00"));
        dto1.setCountLessonTotal(30);
        dto1.setCountLessonComplete(10);
        dto1.setRemainingLessons(20);
        dto1.setVerifyState(1);
        dto1.setOperatorName("李老师");
        records.add(dto1);

        EnrollmentDTO dto2 = new EnrollmentDTO();
        dto2.setId(2L);
        dto2.setStudentName("李四");
        dto2.setCourseName("音乐启蒙班");
        dto2.setSubjectName("音乐");
        dto2.setAddTime(LocalDateTime.now());
        dto2.setAmount(new BigDecimal("2500.00"));
        dto2.setCountLessonTotal(20);
        dto2.setCountLessonComplete(5);
        dto2.setRemainingLessons(15);
        dto2.setVerifyState(1);
        dto2.setOperatorName("王老师");
        records.add(dto2);

        pageDTO.setRows(records);

        return JsonVO.success(pageDTO);
    }

    @Override
    @GetMapping("/enroll/{id}")
    @ApiOperation("获取报名记录详情")
    public JsonVO<EnrollmentDTO> getEnrollRecord(@PathVariable Long id) {
        // 参数校验
        if (id == null || id <= 0) {
            return JsonVO.fail("报名记录ID无效");
        }

        // TODO: 调用Service层获取报名记录详情
        // EnrollmentDTO enrollmentDTO = studentService.getEnrollRecord(id);

        // 模拟数据（实际开发中需要删除）
        EnrollmentDTO dto = new EnrollmentDTO();
        dto.setId(id);
        dto.setStudentName("张三");
        dto.setCourseName("美术基础班");
        dto.setSubjectName("美术");
        dto.setAddTime(LocalDateTime.now());
        dto.setAmount(new BigDecimal("3000.00"));
        dto.setCountLessonTotal(30);
        dto.setCountLessonComplete(10);
        dto.setRemainingLessons(20);
        dto.setVerifyState(1);
        dto.setOperatorName("李老师");

        return JsonVO.success(dto);
    }
    @ApiOperation(value = "审核退费申请")
    @PostMapping("/refund/audit")
    @Override
    public JsonVO<FinanceDTO> auditRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.auditRefund(financeDTO));
    }

    @ApiOperation(value = "完成退费")
    @PostMapping("/refund/complete")
    @Override
    public JsonVO<FinanceDTO> completeRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.completeRefund(financeDTO));
    }

    /**
     * 批量导入（JSON格式）
     * 可在Knife4j/Postman直接POST调用
     */
    @PostMapping("/batch/import")
    @ApiOperation(value = "结业学员批量导入（JSON）", notes = "传入JSON列表批量导入学员数据")
    public CommonResponseVO<GraduateStudentImportResultVO> batchImport(
            @ApiParam(value = "批量导入数据", required = true)
            @RequestBody GraduateStudentImportBatchDTO importDTO) {
        // 仅模拟返回结果，无业务逻辑，保证接口可调用
        GraduateStudentImportResultVO result = new GraduateStudentImportResultVO();
        result.setSuccessCount(importDTO.getStudentList().size());
        result.setFailCount(0);
        result.setFailDetails(new ArrayList<>());
        result.setBatchNo("B" + LocalDate.now().format(DateTimeFormatter.ofPattern("yyyyMMdd")) + "01");
        return CommonResponseVO.success(result);
    }

    /**
     * Excel文件导入
     * 可在Knife4j/Postman上传文件调用
     */
    @PostMapping("/graduation/import")
    @ApiOperation("结业学员导入Excel")
    @ApiImplicitParam(name = "file", value = "上传Excel", dataType = "__file", paramType = "formData")
    public JsonVO<String> importExcel(@RequestParam("file") MultipartFile file) {
        studentGraduationService.importGraduationStudent(file);
        return JsonVO.success("导入成功");
    }
    @GetMapping("/graduation/export")
    @ApiOperation("结业学员导出Excel")
    public void export(
            // 关键：去掉 @RequestBody！！！
            StudentQueryCondition condition,
            HttpServletResponse response) {
        try {
            // 设置下载头（自动弹出保存）
            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
            response.setCharacterEncoding("utf-8");
            String fileName = URLEncoder.encode("结业学员列表", "UTF-8");
            response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");
            // 执行导出
            studentGraduationService.exportGraduationStudent(condition, response);
        } catch (Exception e) {
            throw new RuntimeException("导出失败");
        }
    }
    @Override
    @PostMapping("/getCourseCounter")
    @ApiOperation(value = "获取课程统计")
    public JsonVO<PageDTO<CourseCounterVO>> getCourseCounter(StudentQuery studentQuery) {
        return null;
    }

    @Override
    @PostMapping("/getStudentSchedule")
    @ApiOperation(value = "获取课表")
    public JsonVO<StudentScheduleVO> getStudentSchedule(StudentQuery studentQuery) {
        return null;
    }
}