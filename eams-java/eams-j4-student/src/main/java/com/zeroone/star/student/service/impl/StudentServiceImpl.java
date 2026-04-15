package com.zeroone.star.student.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.alibaba.cloud.commons.lang.StringUtils;
import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.ClassDetailVO;
import com.zeroone.star.student.config.RequestMetaUtil;
import com.zeroone.star.student.entity.*;
import com.zeroone.star.project.vo.j4.student.StudentExportExcelVO;
import com.zeroone.star.project.vo.j4.student.StudentImportExcelVO;
import com.zeroone.star.student.mapper.*;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;
import com.zeroone.star.student.entity.ClassStudentDO;
import com.zeroone.star.student.entity.ContactRecordDO;
import com.zeroone.star.student.mapper.ClassMapper;
import com.zeroone.star.student.mapper.ClassStudentMapper;
import com.zeroone.star.student.mapper.ContactRecordMapper;
import com.zeroone.star.student.service.IStudentService;
import com.zeroone.star.student.service.IUserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.Assert;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
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
    private StudentCourseMapper studentCourseMapper;

    @Resource
    private EasyExcelComponent easyExcelComponent;

    @Resource
    private IUserService userService;

    @Resource
    private SysLogMapper sysLogMapper;

    @Resource
    private HttpServletRequest httpRequest;

    @Resource
    private ContactRecordMapper contactRecordMapper;

    @Resource
    private ClassMapper classMapper;

    @Autowired
    private StudentMapper studentMapper;

    @Resource
    private ClassStudentMapper classStudentMapper;

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
    @Transactional(rollbackFor = Exception.class) // 开启事务，保证整个导入过程的原子性
    public Boolean importOnlineStudents(MultipartFile file) throws IOException {

        // 当前用户ID作为顾问
        Long currentStaffId = null;
        try {
            currentStaffId = Long.valueOf(userHolder.getCurrentUser().getId());
        } catch (Exception e) {
            log.warn("无法获取当前登录用户信息，导入的意向学员顾问字段为空",e);
        }

        List<StudentImportExcelVO> list = easyExcelComponent.parseExcel(file.getInputStream(),"Sheet1",StudentImportExcelVO.class);

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

            Student student = new Student();
            student.setUserId(user.getId());
            student.setName(vo.getStudentName());
            student.setIdcard(vo.getIdcard());
            student.setBirthday(birthDate);


            if (currentStaffId != null) {
                student.setCounselor(currentStaffId);
            }

            student.setStage(1);
            student.setDeleted(0);
            student.setAsDefault(true);

            student.setGender("男".equals(vo.getGender()) ? 1 : ("女".equals(vo.getGender()) ? 2 : 0));
            // 亲属关系默认为0
            student.setFamilyRel(0);

            studentsToSave.add(student);
        }

        if (!studentsToSave.isEmpty()) {
            this.saveBatch(studentsToSave);
        }

        // 处理错误列表（如果你现在的接口定义只能返回 Boolean，那么抛出异常，或者建议修改接口返回类型/响应写出逻辑）
        if (!errorList.isEmpty()) {
            log.warn("在线学员导入有 {} 条失败记录", errorList.size());
            return false;
        }

        return true;
    }

    /**
     * 导出在线学员
     *
     * @param outputStream
     * @return
     */
    @Override
    public byte[] exportOnlineStudent(ServletOutputStream outputStream) {
        List<StudentExportExcelVO> exportData = this.baseMapper.selectOnlineStudentExportData();

        // 将装配好的 VO 列表使用 EasyExcel 写入输出流
        EasyExcel.write(outputStream, StudentExportExcelVO.class)
                .sheet("在线学员")
                .doWrite(exportData);
        return null;
    }

    @Override
    public PageDTO<ClassDTO> queryClassPage(ClassQuery condition) {
        long pageIndex = condition.getPageIndex();
        long pageSize = condition.getPageSize();

        if (pageIndex < 1) pageIndex = 1;
        if (pageSize < 1) pageSize = 10;

        Page<ClassDetailVO> pageParam = new Page<>(pageIndex, pageSize);
        IPage<ClassDetailVO> resultPage = classMapper.selectClassPage(pageParam, condition);

        List<ClassDTO> dtoList = new ArrayList<>();
        List<ClassDetailVO> records = resultPage.getRecords();
        if (records != null) {
            for (ClassDetailVO vo : records) {
                dtoList.add(convertToClassDTO(vo));
            }
        }

        PageDTO<ClassDTO> pageDTO = new PageDTO<>();
        pageDTO.setRows(dtoList);
        pageDTO.setTotal(resultPage.getTotal());
        pageDTO.setPageIndex(resultPage.getCurrent());
        pageDTO.setPageSize(resultPage.getSize());
        pageDTO.setPages(resultPage.getPages());

        return pageDTO;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long joinClass(ClassStudentDTO dto) {
        if (dto.getClassId() == null) {
            throw new IllegalArgumentException("班级ID不能为空");
        }
        if (dto.getStudentId() == null) {
            throw new IllegalArgumentException("学生ID不能为空");
        }

        com.zeroone.star.student.entity.ClassDO classDO = classMapper.selectById(dto.getClassId());
        if (classDO == null || (classDO.getDeleted() != null && classDO.getDeleted() == 1)) {
            throw new RuntimeException("班级不存在");
        }

        int count = classStudentMapper.countByClassAndStudent(dto.getClassId(), dto.getStudentId());
        if (count > 0) {
            throw new RuntimeException("该学员已在班级中");
        }

        int currentCount = classStudentMapper.countByClassId(dto.getClassId());
        if (classDO.getPlannedStudentCount() != null && currentCount >= classDO.getPlannedStudentCount()) {
            throw new RuntimeException("班级人数已满");
        }

        ClassStudentDO classStudentDO = new ClassStudentDO();
        classStudentDO.setClassId(dto.getClassId());
        classStudentDO.setStudentId(dto.getStudentId());
        classStudentDO.setAddTime(LocalDateTime.now());
        classStudentDO.setCreator(dto.getStudentId());
        classStudentDO.setDeleted(0);
        classStudentDO.setConsumeCourseId(classDO.getCourseId());

        classStudentMapper.insert(classStudentDO);

        return classStudentDO.getId();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> quitClass(Long classId, Long studentId) {
        if (classId == null || studentId == null) {
            throw new IllegalArgumentException("参数不能为空");
        }

        LambdaQueryWrapper<ClassStudentDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(ClassStudentDO::getClassId, classId)
                .eq(ClassStudentDO::getStudentId, studentId)
                .eq(ClassStudentDO::getDeleted, 0);

        List<ClassStudentDO> list = classStudentMapper.selectList(queryWrapper);

        if (list == null || list.isEmpty()) {
            throw new RuntimeException("学员不在该班级中");
        }

        List<Long> deletedIds = new ArrayList<>();
        for (ClassStudentDO record : list) {
            record.setDeleted(1);
            classStudentMapper.updateById(record);
            deletedIds.add(record.getId());
        }

        return deletedIds;
    }

    private ClassDTO convertToClassDTO(ClassDetailVO vo) {
        ClassDTO dto = new ClassDTO();
        BeanUtils.copyProperties(vo, dto);
        if (vo.getPlannedStudentCount() != null) {
            dto.setMaxStudentCount(vo.getPlannedStudentCount());
        }
        return dto;
    }

    @Override
    public PageDTO<FollowUpVO> queryFollowUpPage(FollowUpQuery condition) {
        // 1. 创建分页参数对象
        Page<FollowUpVO> pageParam = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2. 执行查询，返回 IPage
        pageParam.setOptimizeCountSql(false);
        IPage<FollowUpVO> iPage = contactRecordMapper.selectFollowUpPage(pageParam, condition);

        // 3. 转换成 PageDTO 返回
        return PageDTO.create((Page<FollowUpVO>) iPage);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveFollowUp(FollowUpDTO dto) {
        ContactRecordDO recordDO = new ContactRecordDO();

        // 1. 手动映射业务字段 (解决字段名不一致问题)
        recordDO.setStudentId(dto.getStudentId());
        recordDO.setStage(dto.getProgressStage());
        recordDO.setContactType(dto.getContactChannel());
        recordDO.setContactTime(dto.getContactTime());
        recordDO.setInfo(dto.getFollowUpContent());
        recordDO.setContactNextTime(dto.getNextContactTime());
        recordDO.setContactPhone(dto.getContactDetail());

        // 2. 自动填充系统字段 (请替换为实际获取逻辑)
        Long currentUserId = getCurrentUserId();
        Long currentOrgId = getCurrentUserOrgId();

        recordDO.setCreator(currentUserId);
        recordDO.setOrgId(currentOrgId);
        recordDO.setAddTime(LocalDateTime.now());
        recordDO.setDeleted(0);

        int result = contactRecordMapper.insert(recordDO);

        // 校验插入结果
        if (result <= 0) {
            throw new RuntimeException("跟进记录保存失败，受影响行数为: " + result);
        }

        // MyBatis-Plus 会在 insert 成功后自动将自增主键回填到 recordDO.getId()
        return recordDO.getId();
    }

    // 模拟获取当前用户信息的方法，请替换为你项目的实际实现 (如 StpUtil.getLoginId() 或 SecurityContextHolder)
    private Long getCurrentUserId() {
        // TODO: 从线程上下文或 Token 中解析真实用户ID
        return 1L;
    }

    private Long getCurrentUserOrgId() {
        // TODO: 从线程上下文或 Token 中解析真实组织ID
        return 1L;
    }

    @Override
    public Long removeFollowUp(Long id) {
        int rowsAffected = contactRecordMapper.deleteById(id);

        // 如果受影响行数为0，说明数据不存在，删除失败
        if (rowsAffected == 0) {
            throw new RuntimeException("删除失败，跟进记录不存在 (ID: " + id + ")");
        }
        return id;
    }

    @Override
    public FollowUpDTO getFollowUpDetail(Long id) {
        ContactRecordDO recordDO = contactRecordMapper.selectById(id);
        if (recordDO == null) return null;
        FollowUpDTO dto = new FollowUpDTO();
        BeanUtil.copyProperties(recordDO, dto);
        return dto;
    }

    @Override
    public PageDTO<ResponseDTO> listall(StudentQuery condition) {
        String name = condition.getName();
        String status = condition.getStage();

        // 1.构建分页查询对象
        Page<Student> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2.分页查询
        Page<Student> p = lambdaQuery()
                .like(!StringUtils.isEmpty(name), Student::getName, name)
                .eq(!StringUtils.isEmpty(status), Student::getStage, status)
                .page(page);

        // 3.封装成ResponsDTO
        PageDTO<ResponseDTO> result = new PageDTO<>();

        result.setTotal(p.getTotal());
        result.setPages(p.getPages());
        result.setPageIndex(condition.getPageIndex());
        result.setPageSize(condition.getPageSize());

        List<Student> records = p.getRecords();
        List<ResponseDTO> responseDTOS = BeanUtil.copyToList(records, ResponseDTO.class);
        result.setRows(responseDTOS);

        return result;
    }

    @Override
    public PageDTO<StudentDTO> queryCourseStu(CourseQuery condition) {
        // 1. 构建分页查询对象
        Page<ClassStudentDO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2. 构建查询条件
        QueryWrapper<ClassStudentDO> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("class_id", condition.getClassId());
        Page<ClassStudentDO> classStudentPage = classStudentMapper.selectPage(page, queryWrapper);

        // 3.封装成StudentDTO
        PageDTO<StudentDTO> result = new PageDTO<>();
        result.setTotal(classStudentPage.getTotal());
        result.setPages(classStudentPage.getPages());
        result.setPageIndex(condition.getPageIndex());
        result.setPageSize(condition.getPageSize());

        List<ClassStudentDO> records = classStudentPage.getRecords();
        List<StudentDTO> responseDTOS = BeanUtil.copyToList(records, StudentDTO.class);
        result.setRows(responseDTOS);

        return result;
    }

    /**
     * 学员阶段设置
     * @param studentDTO
     * @return
     */
    public boolean updateStudentStage(StudentDTO studentDTO) {
        // 判断 Mapper 受影响行数是否大于 0
        return studentMapper.updateStudentStage(studentDTO) > 0;
    }

    @Transactional(rollbackFor = Exception.class) // 保证两个表同时成功
    public boolean saveStudentEnroll(StudentEnrollDTO enrollDTO) {

        // 生成雪花算法 ID
        long id = cn.hutool.core.util.IdUtil.getSnowflakeNextId();
        enrollDTO.setId(id);
        // 1. 写入报名主表
        int count1 = studentMapper.insertStudentCourse(enrollDTO);
        // 2. 写入课时流水表
        int count2 = studentMapper.insertEnrollLog(enrollDTO);

        return count1 > 0 && count2 > 0;
    }


    /**
     * 获取学员信息
     * @param id
     * @return
     */
    public StudentDTO getStudentDetail(Integer id) {
        // 直接返回查询到的数据，不进行 Result 包装
        return studentMapper.selectStudentDetail(id);
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