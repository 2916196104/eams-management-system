package com.zeroone.star.student.service.impl;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.student.config.RequestMetaUtil;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.entity.StudentCourse;
import com.zeroone.star.student.entity.SysLog;
import com.zeroone.star.student.entity.User;
import com.zeroone.star.project.vo.j4.student.StudentExportExcelVO;
import com.zeroone.star.project.vo.j4.student.StudentImportExcelVO;
import com.zeroone.star.student.mapper.StudentCourseMapper;
import com.zeroone.star.student.mapper.StudentMapper;
import com.zeroone.star.student.mapper.SysLogMapper;
import com.zeroone.star.student.service.IStudentService;
import com.zeroone.star.student.service.IUserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.Assert;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.net.URLEncoder;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

/**
 * <p>
 * 学生表 服务实现类
 * </p>
 */
@Slf4j
@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {

    @Resource
    private StudentMapper studentMapper;

    @Resource
    private StudentCourseMapper studentCourseMapper;

    @Resource
    private EasyExcelComponent easyExcelComponent;

    @Resource
    private IUserService userService;

    @Resource
    private SysLogMapper sysLogMapper;

    @Resource
    private HttpServletRequest httpRequest;

    // 注入框架自带的当前用户获取组件
    @Resource
    private UserHolder userHolder;

    // 手机号正则校验
    private static final Pattern PHONE_PATTERN = Pattern.compile("^1[3-9]\\d{9}$");
    // 日期格式化
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    /**
     * 获取当前登录用户ID
     */
    private Long getCurrentUserIdSafely() {
        try {
            if (userHolder.getCurrentUser() == null || StringUtils.isBlank(userHolder.getCurrentUser().getId())) {
                return null;
            }
            return Long.valueOf(userHolder.getCurrentUser().getId());
        } catch (Exception e) {
            log.error("获取当前登录用户ID失败", e);
            return null;
        }
    }

    @Override
    public void exportIntentionStudent(HttpServletResponse response) throws Exception {

        response.setHeader("Access-Control-Expose-Headers", "Content-Disposition");

        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("utf-8");

        String fileName = URLEncoder.encode("意向学员导出", "UTF-8").replaceAll("\\+", "%20");
        response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");

        // 4. 查询数据并导出
        List<StudentExportExcelVO> exportData = this.baseMapper.selectIntentionStudentExportData();
        easyExcelComponent.export("学员数据", response.getOutputStream(), StudentExportExcelVO.class, exportData);
    }

    @Override
    @Transactional(rollbackFor = Exception.class) // 开启事务，保证 user 和 student 表的强一致性
    public void importIntentionStudent(MultipartFile file, HttpServletResponse response) throws Exception {

        // ================= 获取当前登录用户 ID，作为跟进顾问 =================
        Long currentStaffId = null;
        try {
            currentStaffId = Long.valueOf(userHolder.getCurrentUser().getId());
        } catch (Exception e) {
            log.warn("无法获取当前登录用户信息，导入的意向学员顾问字段将为空", e);
        }

        List<StudentImportExcelVO> list = easyExcelComponent.parseExcel(file.getInputStream(), "Sheet1", StudentImportExcelVO.class);

        List<StudentImportExcelVO> errorList = new ArrayList<>();
        List<Student> studentsToSave = new ArrayList<>();


        for (StudentImportExcelVO vo : list) {

            if (StringUtils.isBlank(vo.getStudentName()) || vo.getStudentName().contains("学员导入模板") || "*姓名".equals(vo.getStudentName())) {
                continue; // 直接跳过，不纳入错误列表
            }


            if (StringUtils.isBlank(vo.getStudentName()) || StringUtils.isBlank(vo.getPassword())) {
                vo.setErrorMessage("姓名和登录密码不能为空");
                errorList.add(vo);
                continue;
            }


            if (StringUtils.isBlank(vo.getPhone()) || !PHONE_PATTERN.matcher(vo.getPhone()).matches()) {
                vo.setErrorMessage("手机号为空或格式不正确");
                errorList.add(vo);
                continue;
            }


            LocalDate birthDate = null;
            if (StringUtils.isNotBlank(vo.getBirthday())) {
                try {
                    String originDate = vo.getBirthday().trim().replace("/", "-");

                    String[] parts = originDate.split("-");
                    if (parts.length == 3) {
                        StringBuilder sb = new StringBuilder();
                        sb.append(parts[0]).append("-"); // 年
                        sb.append(parts[1].length() == 1 ? "0" + parts[1] : parts[1]).append("-"); // 月补零
                        sb.append(parts[2].length() == 1 ? "0" + parts[2] : parts[2]); // 日补零
                        originDate = sb.toString();
                    }


                    if (originDate.length() > 10) {
                        originDate = originDate.substring(0, 10);
                    }

                    birthDate = LocalDate.parse(originDate, DATE_FORMATTER);
                } catch (Exception e) {
                    vo.setErrorMessage("日期解析失败，请确保格式类似 2015-05-15");
                    errorList.add(vo);
                    continue;
                }
            }

            User user = userService.getOne(new LambdaQueryWrapper<User>().eq(User::getMobile, vo.getPhone()));
            if (user == null) {
                user = new User();
                user.setMobile(vo.getPhone());
                user.setName(vo.getParentName());
                user.setPassword(vo.getPassword());
                user.setState(true);
                userService.save(user);
            }


            Student existingStudent = this.getOne(new LambdaQueryWrapper<Student>()
                    .eq(Student::getUserId, user.getId())
                    .eq(Student::getName, vo.getStudentName())
                    .eq(Student::getDeleted, 0)); // 没被删除的才算重复

            if (existingStudent != null) {

                vo.setErrorMessage("该家长名下已存在名为【" + vo.getStudentName() + "】的学员，请勿重复导入");
                errorList.add(vo);
                continue;
            }
            // =======================================================


            Student student = new Student();
            student.setUserId(user.getId());
            student.setName(vo.getStudentName());
            student.setIdcard(vo.getIdcard());
            student.setBirthday(birthDate);


            if (currentStaffId != null) {
                student.setCounselor(currentStaffId);
            }


            student.setStage(0);
            student.setDeleted(0);
            student.setAsDefault(true);


            student.setGender("男".equals(vo.getGender()) ? 1 : ("女".equals(vo.getGender()) ? 2 : 0));
            // 因为导入模板里没有“亲属关系”这一列，这里默认给个0（或者如果以后加了可以像性别一样判断）
            student.setFamilyRel(0);

            studentsToSave.add(student);
        }

        if (!studentsToSave.isEmpty()) {
            this.saveBatch(studentsToSave);
        }

        if (!errorList.isEmpty()) {

            response.setHeader("Access-Control-Expose-Headers", "Content-Disposition");


            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
            response.setCharacterEncoding("utf-8");

            String fileName = URLEncoder.encode("导入错误报告", "UTF-8").replaceAll("\\+", "%20");

            response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");

            easyExcelComponent.export("错误数据", response.getOutputStream(), StudentImportExcelVO.class, errorList);
        } else {
            // 全部成功，返回标准的 JSON 提示
            response.setContentType("application/json;charset=utf-8");
            ObjectMapper mapper = new ObjectMapper();
            String jsonResult = mapper.writeValueAsString(JsonVO.success("导入成功，共添加 " + studentsToSave.size() + " 名意向学员"));
            response.getWriter().write(jsonResult);
        }
    }

    /**
     * 修改学员顾问
     * @param studentDTO
     * @return 修改是否成功
     */
    @Override
    @Transactional(rollbackFor = Exception.class) // 开启事务，保证 student 和 sys_log 表的强一致性
    public Boolean modifyConsultant(StudentDTO studentDTO) {
        if(studentDTO == null || studentDTO.getId() == null || studentDTO.getCounselor() == null) {
            return false;
        }

        long startNs = System.nanoTime(); // 方法开始计时

        Long currentUserId = getCurrentUserIdSafely();
        if (currentUserId == null) {
            log.warn("无法获取当前登录用户ID，修改学员顾问操作被拒绝");
            return false;
        }

        // 更新student表中的counselor字段
        Student student = new Student();
        student.setId(studentDTO.getId());
        student.setCounselor(studentDTO.getCounselor());
        student.setEditor(currentUserId);
        student.setEditTime(LocalDateTime.now());

        // 更新数据
        boolean updated = this.updateById(student);
        if(updated) {
            log.info("学员 {} 的顾问修改成功，新的顾问ID: {}", studentDTO.getId(), studentDTO.getCounselor());
        } else {
            log.warn("学员 {} 的顾问修改失败", studentDTO.getId());
            return false;
        }

        // 写入sys_log
        SysLog logEntity = new SysLog();
        logEntity.setOperator(currentUserId);
        logEntity.setStudentId(studentDTO.getId());
        logEntity.setType("UPDATE");
        logEntity.setInfo("修改学员顾问，新的顾问ID: " + student.getCounselor());
        logEntity.setPath("/j4/student/modifyConsultant");
        logEntity.setMethod("POST");
        logEntity.setAddTime(LocalDateTime.now());

        // 利用 RequestMetaUtil 补充 IP、浏览器、系统信息
        try {
            String userAgent = httpRequest.getHeader("User-Agent");
            RequestMetaUtil.UaInfo uaInfo = RequestMetaUtil.parseUa(userAgent);

            logEntity.setIp(RequestMetaUtil.getClientIp(httpRequest));
            logEntity.setBrowserName(uaInfo.getBrowserName());
            logEntity.setBrowserVer(uaInfo.getBrowserVer());
            logEntity.setOsName(uaInfo.getOsName());
            logEntity.setUrl(httpRequest.getRequestURL().toString());
            logEntity.setParam(new ObjectMapper().writeValueAsString(studentDTO));
            logEntity.setOrgId(currentUserId);
            int costMs = (int) (int) ((System.nanoTime() - startNs) / 1_000_000);
            logEntity.setTimeCost(costMs);
        } catch (Exception e) {
            log.warn("获取请求元数据失败", e);
        }

        // 更新数据
        int inserted = sysLogMapper.insert(logEntity);
        if (inserted <= 0) {
            log.error("写入操作日志失败，学员ID: {}", studentDTO.getId());
            throw new RuntimeException("写入操作日志失败");
        }

        return true;
    }

    /**
     * 导入在线学员
     * @param file
     * @return
     */
    @Override
    public Boolean importOnlineStudents(MultipartFile file) {
        return null;
    }

    /**
     * 导出在线学员
     * @return
     */
    @Override
    public byte[] exportOnlineStudent() {
        return new byte[0];
    }

    /**
     * 保存学员
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean saveStudent(Student student) {
        Assert.notNull(student, "学员信息不能为空");
        Assert.hasText(student.getName(), "学员姓名不能为空");

        // ===================== 强制补齐所有数据库必填字段 =====================
        // 家长ID（必须有）
        if (student.getUserId() == null) {
            student.setUserId(1L);
        }

        // 家庭关系
        if (student.getFamilyRel() == null) {
            student.setFamilyRel(1);
        }

        // 默认家长查看
        if (student.getAsDefault() == null) {
            student.setAsDefault(true);
        }

        // 组织ID
        if (student.getOrgId() == null) {
            student.setOrgId(1L);
        }

        // 系统字段
        student.setDeleted(0);
        student.setAddTime(LocalDateTime.now());
        student.setCreator(1L);
        student.setEditor(1L);
        student.setEditTime(LocalDateTime.now());

        // ====================================================================

        return save(student);
    }
    /**
     * 获取学员课次数据
     */
    @Override
    public List<StudentCourse> listCourseTimesByStudentId(Long studentId) {
        Assert.notNull(studentId, "学员ID不能为空");
        return studentCourseMapper.listCourseTimesByStudentId(studentId);
    }
    /**
     * 获取课时汇总列表
     */
    @Override
    public Page<StudentCourse> getLessonSummaryPage(Page<StudentCourse> page, StudentQuery query) {
        Assert.notNull(page, "分页参数不能为空");
        Assert.notNull(query, "查询条件不能为空");
        return (Page<StudentCourse>) studentCourseMapper.getLessonSummaryPage(page, query);
    }
}