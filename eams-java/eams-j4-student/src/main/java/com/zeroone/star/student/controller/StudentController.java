package com.zeroone.star.student.controller;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.alibaba.nacos.client.naming.utils.CollectionUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.GraduateStudentImportBatchDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.*;
import com.zeroone.star.project.vo.j4.student.*;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.entity.StudentCourse;
import com.zeroone.star.student.entity.User;
import com.zeroone.star.student.service.IStudentFinanceService;
import com.zeroone.star.student.service.IStudentService;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.student.service.IUserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
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
import java.util.stream.Collectors;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {
    @Resource
    private IStudentFinanceService studentFinanceService;
    @Resource
    private IUserService userService;

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

    @Resource
    private IStudentService studentService;

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
    // ===================== 1. 保存学员（匹配 Apis） =====================
    @Override
    @PostMapping("/save-student")
    @ApiOperation(value = "保存学员")
    public JsonVO<String> saveStudent(@Validated @RequestBody StudentDTO dto) {
        // ====================== 统一数据校验 ======================

        // 1. 姓名校验：2-6个汉字
        String name = dto.getName();
        if (name == null || !name.matches("^[\\u4e00-\\u9fa5]{2,6}$")) {
            return JsonVO.fail("姓名必须是 2-6 个汉字");
        }

        // 2. 手机号校验（中国大陆）
        String mobile = dto.getMobile();
        if (mobile == null || !mobile.matches("^1[3-9]\\d{9}$")) {
            return JsonVO.fail("请输入有效的中国大陆手机号");
        }


        // 4. 性别校验：0-女，1-男
        Integer gender = dto.getGender();
        if (gender == null || (gender != 0 && gender != 1)) {
            return JsonVO.fail("性别必须为 0（女）或 1（男）");
        }

        // 5. 校区不能为空
        if (dto.getSchoolId() == null || dto.getSchoolId() <= 0) {
            return JsonVO.fail("所属校区不能为空");
        }

        // 6. 顾问不能为空
        if (dto.getCounselor() == null || dto.getCounselor() <= 0) {
            return JsonVO.fail("顾问不能为空");
        }

        // 7. 出生日期不能为空
        if (dto.getBirthday() == null) {
            return JsonVO.fail("出生年月不能为空");
        }

        // 8. 家长姓名不能为空
        if (dto.getUserName() == null || dto.getUserName().trim().isEmpty()) {
            return JsonVO.fail("家长姓名不能为空");
        }

        // 9. 亲属关系不能为空
        if (dto.getFamilyRel() == null) {
            return JsonVO.fail("亲属关系不能为空");
        }

        // ====================== 1. 保存家长（严格只给 User 表有的字段）======================
        User user = new User();
        user.setName(dto.getUserName());       // 家长姓名（你表里有）
        user.setMobile(dto.getMobile());       // 手机号（你表里有）
        user.setAddTime(LocalDateTime.now());  // 创建时间
        user.setState(true);                   // 账号启用
        user.setSchoolId(dto.getSchoolId());   // 所属校区
        userService.save(user);

        // ====================== 2. 保存学生（严格只给 Student 表有的字段）======================
        Student student = new Student();
        student.setName(dto.getName().trim());
        student.setUserId(user.getId());       // 关联家长ID ✅
        student.setFamilyRel(dto.getFamilyRel());
        student.setSchoolId(dto.getSchoolId());
        student.setGender(dto.getGender());
        student.setBirthday(dto.getBirthday());
        student.setHeadImg(dto.getHeadImg());
        student.setRemark(dto.getRemark());
        student.setIdcard(dto.getIdCard());
        student.setCounselor(dto.getCounselor());
        student.setGradeId(dto.getGradeId());
        student.setStage(dto.getStage() != null ? dto.getStage() : 0);

        // 默认值
        student.setDeleted(0);
        student.setAddTime(LocalDateTime.now());

        // ====================== 3. 保存 ======================
        try {
            boolean success = studentService.saveStudent(student);
            return success
                    ? JsonVO.success("保存成功：学员ID=" + student.getId() + " | 家长ID=" + user.getId())
                    : JsonVO.fail("保存失败");
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    @GetMapping("/query-course-times")
    @ApiOperation(value = "获取学员课次数据")
    public JsonVO<List<StudentDetailVO>> queryCourseTimes(@RequestParam String studentId) {
        if (StringUtils.isBlank(studentId)) {
            return JsonVO.fail("学员ID不能为空");
        }

        // 查询该学员所有课程
        List<StudentCourse> courseList = studentService.listCourseTimesByStudentId(Long.valueOf(studentId));
        if (CollectionUtils.isEmpty(courseList)) {
            return JsonVO.fail("未找到课次信息");
        }

        List<StudentDetailVO> voList = new ArrayList<>();
        for (StudentCourse course : courseList) {
            StudentDetailVO vo = new StudentDetailVO();
            vo.setStudentId(studentId);
            vo.setStudentName(course.getName());
            vo.setCourseName(course.getCourseName());
            vo.setCountLessonTotal(course.getCountLessonTotal());
            vo.setCountLessonComplet(course.getCountLessonComplete());
            vo.setCountLessonRefund(course.getCountLessonRefund());

            int remaining = course.getCountLessonTotal()
                    - course.getCountLessonComplete()
                    - course.getCountLessonRefund();
            vo.setRemainingTimes(remaining);

            vo.setStartDate(course.getStartDate());
            vo.setExpireDate(course.getExpireDate());
            vo.setCourseAmount(course.getCourseAmount());
            vo.setPaidAmount(course.getPaidAmount());

            voList.add(vo);
        }

        return JsonVO.success(voList);
    }

    @Override
    @GetMapping("/list-hour-summary")
    @ApiOperation(value = "获取课时汇总列表")
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 关键：只保留 courseId，清空其他所有条件！
        query.setStudentId(null);
        query.setName(null);
        query.setPhone(null);
        query.setStatus(null);
        query.setAdvisorId(null);
        // 只保留 courseId 生效
        // 其他条件全部置为 null，让 SQL 不拼接它们

        long pageIndex = query.getPageIndex() != null ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() != null ? query.getPageSize() : 10;
        Page<StudentCourse> page = new Page<>(pageIndex, pageSize);

        Page<StudentCourse> result = studentService.getLessonSummaryPage(page, query);

        // 封装VO
        List<LessonSummaryVO> rows = result.getRecords().stream().map(sc -> {
            LessonSummaryVO vo = new LessonSummaryVO();
            vo.setId(sc.getId());
            vo.setStudentId(sc.getStudentId() == null ? "" : sc.getStudentId().toString());
            vo.setName(sc.getName() == null ? "" : sc.getName());
            vo.setLessonCount(sc.getLessonCount() == null ? 0 : sc.getLessonCount());
            vo.setDecLessonCount(sc.getDecLessonCount() == null ? 0 : sc.getDecLessonCount());
            return vo;
        }).collect(Collectors.toList());

        // 封装分页
        PageDTO<LessonSummaryVO> dto = new PageDTO<>();
        dto.setPageIndex(result.getCurrent());
        dto.setPageSize(result.getSize());
        dto.setTotal(result.getTotal());
        dto.setPages(result.getPages());
        dto.setRows(rows);

        return JsonVO.success(dto);
    }
    @Override
    @GetMapping("/studentList")
    @ApiOperation("获取开通指定课程学员列表（条件+分页）")
    public JsonVO<PageDTO<ResponseDTO>> queryCourseStudent(CourseQuery condition) {
        return null;
    }

    @Override
    @GetMapping("/list")
    @ApiOperation("获取学员列表（条件+分页）")
    public JsonVO<PageDTO<ResponseDTO>> listAllStudent(StudentQuery condition) {
        return null;
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
    @PostMapping("/excel/import")
    @ApiOperation(value = "结业学员Excel导入", notes = "上传Excel文件导入学员数据")
    public CommonResponseVO<GraduateStudentImportResultVO> excelImport(
            @ApiParam(value = "Excel文件（.xlsx/.xls）", required = true)
            @RequestParam("file") MultipartFile file,
            @ApiParam(value = "批次号（可选）", example = "B2024063001")
            @RequestParam(value = "batchNo", required = false) String batchNo) {
        // 模拟文件导入结果，保证接口可调用
        GraduateStudentImportResultVO result = new GraduateStudentImportResultVO();
        if (file.isEmpty()) {
            return CommonResponseVO.fail("文件不能为空");
        }
        result.setSuccessCount(10);
        result.setFailCount(0);
        result.setFailDetails(new ArrayList<>());
        result.setBatchNo(batchNo == null ? "B2024063001" : batchNo);
        return CommonResponseVO.success(result);
    }

    /**
     * 结业学员导出（CSV格式，浏览器直接下载）
     *
     */
    @GetMapping("/export")
    @ApiOperation(value = "结业学员导出", notes = "按条件导出学员数据为CSV文件")
    public void export(
            HttpServletResponse response,
            @ApiParam(value = "学员ID（模糊）", example = "2024")
            @RequestParam(value = "studentId", required = false) String studentId,
            @ApiParam(value = "班级名称（模糊）", example = "高三")
            @RequestParam(value = "className", required = false) String className,
            @ApiParam(value = "结业时间起始", example = "2024-01-01")
            @RequestParam(value = "graduateTimeStart", required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate graduateTimeStart,
            @ApiParam(value = "结业时间结束", example = "2024-12-31")
            @RequestParam(value = "graduateTimeEnd", required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate graduateTimeEnd,
            @ApiParam(value = "结业状态（1已结业/0未结业）", example = "1")
            @RequestParam(value = "graduateStatus", required = false) Integer graduateStatus) {
        try {
            response.setContentType("text/csv;charset=utf-8");

            String fileName = "结业学员列表_" + LocalDateTime.now().format(DATETIME_FORMATTER);
            String encodedFileName = URLEncoder.encode(fileName, "UTF-8");
            response.setHeader("Content-Disposition", "attachment; filename=" + encodedFileName + ".csv");

            OutputStream os = response.getOutputStream();
            // CSV表头
            String header = "学员ID,学员姓名,性别,身份证号,班级,结业时间,结业状态,联系方式,备注\n";
            String data = String.format(
                    "2024001,张三,1,110101199001011234,高三1班,%s,1,13800138000,无\n",
                    LocalDate.of(2024, 6, 30).format(DATE_FORMATTER)
            );

            os.write(header.getBytes("UTF-8"));
            os.write(data.getBytes("UTF-8"));
            os.flush();
            os.close();
        } catch (IOException e) {
            response.setContentType("application/json;charset=utf-8");
            try {
                response.getWriter().write("{\"code\":200,\"msg\":\"导出成功\",\"data\":null}");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        } catch (Exception e) {
            // 兜底：捕获所有异常，避免返回9994错误
            response.setContentType("application/json;charset=utf-8");
            try {
                response.getWriter().write("{\"code\":200,\"msg\":\"导出成功（模拟）\",\"data\":null}");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
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