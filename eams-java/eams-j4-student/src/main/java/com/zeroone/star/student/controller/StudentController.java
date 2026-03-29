package com.zeroone.star.student.controller;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.*;
import com.zeroone.star.project.vo.j4.student.*;
import com.zeroone.star.student.entity.ClassDO;
import com.zeroone.star.student.entity.ClassroomDO;
import com.zeroone.star.student.entity.CourseDO;
import com.zeroone.star.student.entity.LessonDO;
import com.zeroone.star.student.entity.LessonStudentDO;
import com.zeroone.star.student.entity.Staff;
import com.zeroone.star.student.entity.StudentCourse;
import com.zeroone.star.student.entity.SubjectDO;
import com.zeroone.star.student.mapper.ClassMapper;
import com.zeroone.star.student.mapper.ClassroomMapper;
import com.zeroone.star.student.mapper.LessonMapper;
import com.zeroone.star.student.mapper.LessonStudentMapper;
import com.zeroone.star.student.mapper.StaffMapper;
import com.zeroone.star.student.service.*;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.seata.core.model.Result;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;
import com.zeroone.star.student.service.IStudentService;
import com.zeroone.star.student.mapper.MsStudentMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.bind.annotation.RestController;
import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.math.BigDecimal;
import java.net.URLEncoder;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

import java.util.stream.Collectors;

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
    private IStudentCourseService studentCourseService;
    @Resource
    private MsStudentMapper msStudentMapper;
    @Resource
    private ICourseService courseService;
    @Resource
    private ISubjectService subjectService;

    @Resource
    private LessonStudentMapper lessonStudentMapper;
    @Resource
    private LessonMapper lessonMapper;
    @Resource
    private StaffMapper staffMapper;
    @Resource
    private ClassMapper classMapper;
    @Resource
    private ClassroomMapper classroomMapper;

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
    public JsonVO<PageDTO<FollowUpVO>> queryFollowUpPage(@Validated FollowUpQuery condition) {
        return JsonVO.success(studentService.queryFollowUpPage(condition));
    }


    @PostMapping("/follow-up")
    @ApiOperation("添加跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody @Validated FollowUpDTO followUpDTO) {
        if (followUpDTO.getStudentId() == null) {
            return JsonVO.fail("学生ID不能为空");
        }
        if (followUpDTO.getContactTime() == null) {
            return JsonVO.fail("联系时间不能为空");
        }

        // 调用 Service 进行新增
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
            @RequestParam Long classId,
            @ApiParam(value = "学生 ID", required = true, example = "2008418408985583617")
            @RequestParam Long studentId) {
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
        if(file.isEmpty()) {
            return JsonVO.fail("上传的Excel不能为空");
        }
        try {
            studentService.importOnlineStudents(file);
            return JsonVO.success("在学学员导入成功");
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.fail("在线学员导入失败L:"+e.getMessage());
        }

    }

    @GetMapping("/exportOnlineStudents")
    @ApiOperation("导出在学学员")
    public void exportOnlineStudents(HttpServletResponse response) {
        try {
            // 1. 设置响应头，告诉浏览器这是一个下载文件的响应
            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
            response.setCharacterEncoding("utf-8");

            // 为了防止中文文件名乱码，手动进行URLEncoder编码
            String fileName = URLEncoder.encode("在线学员列表", "UTF-8").replaceAll("\\+", "%20");
            response.setHeader("Content-disposition", "attachment;filename*=utf-8''" + fileName + ".xlsx");

            // 2. 调用 Service 层进行查询和直接使用写流的方式导出
            studentService.exportOnlineStudent(response.getOutputStream());
        } catch (Exception e) {
            // 发生异常时可以重置 response 后返回 JSON 提示信息
            response.reset();
            response.setContentType("application/json");
            response.setCharacterEncoding("utf-8");
            try {
                response.getWriter().println("{\"code\": 500, \"msg\": \"导出Excel失败\"}");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
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
        // 1. 安全处理：防止传入的 studentId 为空
        String targetStudentId = (studentId == null || studentId.trim().isEmpty()) ? "1" : studentId;

        // 2. 构造 VO 对象，严格匹配 StudentDetailVO 的所有字段
        StudentDetailVO vo = new StudentDetailVO();
        vo.setStudentId(targetStudentId);
        vo.setStudentName("sdadadsdsadd");
        vo.setCountLessonTotal(20);          // 总课时数
        vo.setCountLessonComplet(12);        // 已完成课时数
        vo.setCountLessonRefund(2);          // 已退款课时数
        vo.setRemainingTimes(6);             // 剩余课时数
        vo.setStartDate(LocalDate.of(2025, 3, 1)); // 课程开始日期
        vo.setExpireDate(LocalDate.of(2026, 3, 1)); // 课程过期日期
        vo.setCourseAmount(new BigDecimal("2000.00")); // 课程总金额
        vo.setPaidAmount(new BigDecimal("1800.00"));   // 实付金额

        // 3. 返回成功结果
        return JsonVO.success(vo);
    }

    /**
     * 分页查询学员课时汇总
     * @param query 查询条件（包含学员ID+分页参数）
     * @return 分页课时汇总数据
     */
    @Override
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 1. 构造课时汇总数据
        LessonSummaryVO summary = new LessonSummaryVO();
        summary.setId(1L);
        summary.setLessonId(1001L);
        summary.setClassId(2001);

        // 处理空值
        summary.setStudentId(query == null || query.getStudentId() == null ? "1" : query.getStudentId());
        summary.setName(query == null || query.getName() == null ? "sdadadsdsadd" : query.getName());
        summary.setMobile(query == null || query.getMobile() == null ? "18864216425" : query.getMobile());

        summary.setDecLessonCount(1);
        summary.setLessonCount(10);
        summary.setTeacherId(3001L);
        summary.setSignTime(LocalDateTime.of(2025, 3, 18, 14, 30));
        summary.setSignType(1);
        summary.setSignState(1);

        // 2. 构造分页数据
        List<LessonSummaryVO> rows = Collections.singletonList(summary);
        PageDTO<LessonSummaryVO> pageDTO = new PageDTO<>();

        // 处理分页参数（变量类型改为 long，和返回类型一致）
        long pageIndex = (query == null) ? 1L : query.getPageIndex();
        long pageSize = (query == null) ? 30L : query.getPageSize();

        pageDTO.setPageIndex(pageIndex);
        pageDTO.setPageSize(pageSize);
        pageDTO.setTotal(1L);
        pageDTO.setPages(1L);
        pageDTO.setRows(rows);

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
     * 结业学员导入（Excel文件）
     * @param file Excel文件（非空校验）
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
        String studentId = studentQuery.getStudentId();
        if(studentId.isEmpty()){
            return JsonVO.fail("学生id为空");
        }
        // 根据学生id查找表student_course
        Page<StudentCourse> page = new Page<>(studentQuery.getPageIndex(), studentQuery.getPageSize());
        Page<StudentCourse> studentCoursePage = studentCourseService.lambdaQuery()
                .eq(StudentCourse::getStudentId, studentId)
                .page(page);

        List<StudentCourse> records = studentCoursePage.getRecords();
        if (records == null || records.isEmpty()) {
            // 如果没有数据，直接利用您之前的静态方法返回空的分页对象
            return JsonVO.success(null);
        }

        // 提取当前页所有的 courseId 和 subjectId
        Set<Long> courseIds = records.stream().map(StudentCourse::getCourseId).collect(Collectors.toSet());
        Set<Long> subjectIds = records.stream().map(StudentCourse::getSubjectId).collect(Collectors.toSet());

        // 一次性查出当前页涉及的所有课程和科目
        Map<Long, String> courseNameMap = courseService.listByIds(courseIds).stream()
                .collect(Collectors.toMap(CourseDO::getId, CourseDO::getName));
        Map<Long, String> subjectNameMap = subjectService.listByIds(subjectIds).stream()
                .collect(Collectors.toMap(SubjectDO::getId, SubjectDO::getName));

        // ================= 组装数据并返回 =================
        PageDTO<CourseCounterVO> pageDTO = PageDTO.create(studentCoursePage, entity -> {
            // 先用 Mapper 做基础转换
            CourseCounterVO vo = msStudentMapper.toCourseCounterVO(entity);

            // 再补全缺失的名称字段 (直接从内存 Map 中取，极快)
            vo.setCourseName(courseNameMap.getOrDefault(entity.getCourseId(), "未知课程"));
            vo.setSubjectName(subjectNameMap.getOrDefault(entity.getSubjectId(), "未知科目"));

            return vo;
        });

        return JsonVO.success(pageDTO);
    }

    @Override
    @PostMapping("/getStudentSchedule")
    @ApiOperation(value = "获取课表")
    public JsonVO<List<StudentScheduleVO>> getStudentSchedule(StudentQuery studentQuery) {
        if (studentQuery == null || StringUtils.isBlank(studentQuery.getStudentId())) {
            return JsonVO.fail("学生id为空");
        }

        Long studentId;
        try {
            studentId = Long.valueOf(studentQuery.getStudentId());
        } catch (NumberFormatException e) {
            return JsonVO.fail("学生id格式错误");
        }

        // 根据学生id从 lesson_student 中查询全部记录
        List<LessonStudentDO> lessonStudentList = lessonStudentMapper.selectList(
                new LambdaQueryWrapper<LessonStudentDO>()
                        .eq(LessonStudentDO::getStudentId, studentId)
                        .orderByDesc(LessonStudentDO::getAddTime)
                .orderByDesc(LessonStudentDO::getId)
        );
        if (lessonStudentList == null || lessonStudentList.isEmpty()) {
            return JsonVO.success(Collections.emptyList());
        }

        Set<Long> lessonIds = lessonStudentList.stream()
            .map(LessonStudentDO::getLessonId)
            .filter(Objects::nonNull)
            .collect(Collectors.toSet());
        if (lessonIds.isEmpty()) {
            return JsonVO.success(Collections.emptyList());
        }

        Map<Long, LessonDO> lessonMap = lessonMapper.selectBatchIds(lessonIds).stream()
            .collect(Collectors.toMap(LessonDO::getId, lesson -> lesson, (a, b) -> a));
        if (lessonMap.isEmpty()) {
            return JsonVO.success(Collections.emptyList());
        }

        Set<Long> courseIds = lessonMap.values().stream()
            .map(LessonDO::getCourseId)
            .filter(Objects::nonNull)
            .collect(Collectors.toSet());
        Set<Long> teacherIds = lessonMap.values().stream()
            .map(LessonDO::getTeacherId)
            .filter(Objects::nonNull)
            .collect(Collectors.toSet());
        Set<Long> classIds = lessonMap.values().stream()
            .map(LessonDO::getClassId)
            .filter(Objects::nonNull)
            .collect(Collectors.toSet());
        Set<Long> roomIds = lessonMap.values().stream()
            .map(LessonDO::getRoomId)
            .filter(Objects::nonNull)
            .collect(Collectors.toSet());

        Map<Long, String> courseNameMap = courseIds.isEmpty()
            ? Collections.emptyMap()
            : courseService.listByIds(courseIds).stream()
                .collect(Collectors.toMap(CourseDO::getId, CourseDO::getName, (a, b) -> a));

        Map<Long, String> teacherNameMap = teacherIds.isEmpty()
            ? Collections.emptyMap()
            : staffMapper.selectBatchIds(teacherIds).stream()
                .collect(Collectors.toMap(Staff::getId, Staff::getName, (a, b) -> a));

        Map<Long, String> classNameMap = classIds.isEmpty()
            ? Collections.emptyMap()
            : classMapper.selectBatchIds(classIds).stream()
                .collect(Collectors.toMap(ClassDO::getId, ClassDO::getName, (a, b) -> a));

        Map<Long, String> classroomNameMap = roomIds.isEmpty()
            ? Collections.emptyMap()
            : classroomMapper.selectBatchIds(roomIds).stream()
                .collect(Collectors.toMap(ClassroomDO::getId, ClassroomDO::getName, (a, b) -> a));

        List<StudentScheduleVO> scheduleList = lessonStudentList.stream()
            .map(lessonStudent -> {
                LessonDO lesson = lessonMap.get(lessonStudent.getLessonId());
                if (lesson == null) {
                return null;
                }

                StudentScheduleVO scheduleVO = new StudentScheduleVO();
                scheduleVO.setDate(lesson.getDate());
                scheduleVO.setStartTime(lesson.getStartTime());
                scheduleVO.setEndTime(lesson.getEndTime());
                scheduleVO.setTeachType(mapTeachType(lesson.getTeachType()));
                scheduleVO.setDecLessonCount(lessonStudent.getDecLessonCount() == null
                    ? BigDecimal.ZERO
                    : BigDecimal.valueOf(lessonStudent.getDecLessonCount()));
                scheduleVO.setSignState(mapSignState(lessonStudent.getSignState()));
                scheduleVO.setCourseName(courseNameMap.getOrDefault(lesson.getCourseId(), "未知课程"));
                scheduleVO.setTeacherName(teacherNameMap.getOrDefault(lesson.getTeacherId(), "未知教师"));
                scheduleVO.setClassName(classNameMap.getOrDefault(lesson.getClassId(), "未知班级"));
                scheduleVO.setClassroomName(classroomNameMap.getOrDefault(lesson.getRoomId(), "未知教室"));
                return scheduleVO;
            })
            .filter(Objects::nonNull)
            .collect(Collectors.toList());

        return JsonVO.success(scheduleList);
    }

    private String mapTeachType(Integer teachType) {
        if (teachType == null) {
            return "未知方式";
        }
        switch (teachType) {
            case 1:
                return "面授";
            case 2:
                return "线上";
            case 3:
                return "录播";
            default:
                return "未知方式";
        }
    }

    private String mapSignState(Integer signState) {
        if (signState == null) {
            return "未知状态";
        }
        switch (signState) {
            case 0:
                return "未签到";
            case 1:
                return "已签到";
            case 2:
                return "请假";
            case 3:
                return "旷课";
            default:
                return "未知状态";
        }
    }

    /**
     * 学员阶段设置
     */
    @PutMapping("/modify-stage")
    @ApiOperation(value = "设置学员阶段状态", notes = "修改学员当前学习阶段")
    public Result<Boolean> modifyStudentStage(@RequestBody StudentDTO studentDTO) {
        // Service 返回原始 boolean
        boolean success = studentService.updateStudentStage(studentDTO);
        // 在 Controller 层进行 Result 包装
        return success ? Result.ok() : Result.build(false, "阶段更新失败");
    }

    @PostMapping("/add-enroll")
    @ApiOperation(value = "新增学员报名", notes = "关联课程并初始化课时流水")
    public Result<Boolean> addStudentEnroll(@RequestBody StudentEnrollDTO enrollDTO) {
        // 基础校验
        if (enrollDTO.getStudentId() == null || enrollDTO.getCourseId() == null) {
            return Result.build(false, "报名失败：学员ID和课程ID不能为空");
        }

        boolean isSuccess = studentService.saveStudentEnroll(enrollDTO);
        return isSuccess ? Result.ok() : Result.build(false, "报名存入数据库失败");
    }

    /**
     * 获取学员详情
     */
    @GetMapping("/query-detail/id")
    @ApiOperation(value = "获取学员详细资料", notes = "根据ID查询单条详情")
    public Result<StudentDTO> queryStudentDetail(Integer id) {
        // Service 返回原始 DTO 对象
        StudentDTO detail = studentService.getStudentDetail(id);
        // 包装进 Result 的 result 字段
        return Result.build(detail);
    }
}
