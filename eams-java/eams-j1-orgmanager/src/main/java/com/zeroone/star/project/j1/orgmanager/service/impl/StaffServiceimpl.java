package com.zeroone.star.project.j1.orgmanager.service.impl;

import cn.hutool.core.convert.Convert;
import cn.hutool.core.date.DateUtil;
import cn.hutool.core.util.StrUtil;
import cn.hutool.json.JSONObject;
import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.core.toolkit.CollectionUtils;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
//import com.github.pagehelper.PageHelper;
//import com.github.pagehelper.PageInfo;
import com.zeroone.star.project.DO.Class;
import com.zeroone.star.project.DO.*;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.*;
import com.zeroone.star.project.j1.orgmanager.mapper.staff.*;
import com.zeroone.star.project.j1.orgmanager.service.StaffService;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.LessonRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j1.org.*;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import cn.hutool.core.convert.Convert;
import javax.servlet.http.HttpServletRequest;
import java.io.ByteArrayOutputStream;
import java.net.URLEncoder;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

@Service
@Slf4j
public class StaffServiceimpl extends ServiceImpl<StaffMapper, Staff> implements StaffService {

    @Autowired
    private StaffOrginfoMapper staffOrginfoMapper;
    @Autowired
    private StaffPositionMapper staffPositionMapper;
    @Autowired
    private StaffMapper staffMapper;
    @Autowired
    private LessonTeacherMapper lessonTeacherMapper;
    @Autowired
    private LessonMapper lessonMapper;
    @Autowired
    private CourseMapper courseMapper;
    @Autowired
    private ClassMapper classMapper;
    @Autowired
    private ClassroomMapper classroomMapper;
    @Autowired
    private SubjectMapper subjectMapper;

    // 从请求头token获取用户（真实、不伪造、不使用UserHolder）
    private UserDTO getCurrentUserDTO() {
        try {
            ServletRequestAttributes attributes = (ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
            if (attributes == null) return null;
            HttpServletRequest request = attributes.getRequest();

            String userStr = request.getHeader("user");
            if (userStr == null) return null;

            userStr = java.net.URLDecoder.decode(userStr, "UTF-8");
            JSONObject userJson = new JSONObject(userStr);

            return UserDTO.builder()
                    .id(Convert.toStr(userJson.get("id")))
                    .username(userJson.getStr("user_name"))
                    .orgId(Convert.toLong(userJson.get("org_id")))
                    .build();

        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    // 安全获取orgId，永远不会null
    private Long getSafeOrgId() {
        UserDTO dto = getCurrentUserDTO();
        return dto != null ? dto.getOrgId() : 1L; // 兜底1L，绝对不空
    }
/**
分页查询

 **/
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        Long orgId = getSafeOrgId();

        // 1. 构建 MP 分页对象
        Page<Staff> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2. 构建条件
        LambdaQueryWrapper<Staff> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Staff::getDeleted, 0);

        // 动态条件
        if (condition.getName() != null && !condition.getName().trim().isEmpty()) {
            queryWrapper.like(Staff::getName, condition.getName().trim());
        }
        if (condition.getAccount() != null && !condition.getAccount().trim().isEmpty()) {
            queryWrapper.eq(Staff::getMobile, condition.getAccount().trim());
        }
        if (condition.getStatue() != null) {
            queryWrapper.eq(Staff::getState, condition.getStatue());
        }
        staffMapper.selectPage(page, queryWrapper);

        // 4. 转 VO
        List<StaffVO> voList = page.getRecords().stream().map(staffDO -> {
            StaffVO staffVO = new StaffVO();
            try {
                BeanUtils.copyProperties(staffDO, staffVO);
            } catch (Exception e) {
            }

            StaffOrginfo orgInfoDO = staffOrginfoMapper.selectOne(
                    Wrappers.lambdaQuery(StaffOrginfo.class)
                            .eq(StaffOrginfo::getStaffId, staffDO.getId())
                            .eq(StaffOrginfo::getDeleted, 0)
            );

            if (orgInfoDO != null) {
                staffVO.setOrgId(orgId);
                if (orgInfoDO.getPositionId() != null) {
                    StaffPosition positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
                    if (positionDO != null) {
                        staffVO.setPositionName(positionDO.getName());
                    }
                }
            }
            return staffVO;
        }).collect(Collectors.toList());

        // 5. 封装返回
        PageDTO<StaffVO> pageDTO = PageDTO.create(new Page<StaffVO>()
                .setCurrent(page.getCurrent())
                .setSize(page.getSize())
                .setTotal(page.getTotal())
                .setRecords(voList)
        );

        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition) {

        LambdaQueryWrapper<Staff> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Staff::getId, condition.getId())
                .eq(Staff::getDeleted, 0);

        Staff staff = staffMapper.selectOne(queryWrapper);
        if (staff == null) {
            return JsonVO.fail("员工不存在");
        }

        // ========== 3. 封装VO ==========
        StaffDetailsVO staffVO = new StaffDetailsVO();
        BeanUtils.copyProperties(staff, staffVO);

        // ========== 4. 查询机构信息（正确写法） ==========
        StaffOrginfo orgInfoDO = staffOrginfoMapper.selectOne(
                Wrappers.lambdaQuery(StaffOrginfo.class)
                        .eq(StaffOrginfo::getStaffId, staff.getId())
                        .eq(StaffOrginfo::getDeleted, 0)
        );

        Long orgId = getSafeOrgId(); // 安全获取当前用户机构

        if (orgInfoDO != null) {
            staffVO.setOrgId(orgId);
            staffVO.setPositionId(orgInfoDO.getPositionId());

            // 设置职位名称
            if (orgInfoDO.getPositionId() != null) {
                StaffPosition positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());

            }
        }

        return JsonVO.success(staffVO);
    }

    @Override
    public JsonVO<Long> saveStaff(StaffDTO condition) {
        Long orgId = getSafeOrgId();

        if (condition.getName() == null || condition.getName().equals("")) {
            return JsonVO.fail("姓名不能为空");
        }
        if (condition.getMobile() == null || condition.getMobile().equals("")) {
            return JsonVO.fail("账号不能为空");
        }
        if (condition.getGender() == null) {
            return JsonVO.fail("性别不能为空");
        }

        if (condition.getPositionId() != null) {
            StaffPosition positionDO = staffPositionMapper.selectById(condition.getPositionId());
            if (positionDO == null) {
                return JsonVO.fail("职位ID不存在，请选择合法职位");
            }
        }

        Staff staff = new Staff();
        BeanUtils.copyProperties(condition, staff);
        Long staffId;
        if (condition.getMobile() == null) {
            this.staffMapper.insert(staff);
            staffId = staff.getId();
            StaffOrginfo orgInfoDO = new StaffOrginfo();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(orgId);
            orgInfoDO.setPositionId(condition.getPositionId());
            orgInfoDO.setDeleted(0);
            staffOrginfoMapper.insert(orgInfoDO);
        } else {
            this.staffMapper.updateById(staff);
            staffId = staff.getId();
            StaffOrginfo orgInfoDO = new StaffOrginfo();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(orgId);
            orgInfoDO.setPositionId(condition.getPositionId());
            LambdaUpdateWrapper<StaffOrginfo> updateWrapper = new LambdaUpdateWrapper<>();
            updateWrapper.eq(StaffOrginfo::getStaffId, staffId);
            staffOrginfoMapper.update(orgInfoDO, updateWrapper);
        }
        return JsonVO.success(staffId);
    }
    @Override
    public JsonVO<Long> removeStaff(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的员工");
        }

        // 1. 先查询要删除的员工，判断是否已经被删除
        LambdaQueryWrapper<Staff> queryWrapper = Wrappers.lambdaQuery();
        queryWrapper.in(Staff::getId, ids).eq(Staff::getDeleted, 1);
        List<Staff> deletedStaff = staffMapper.selectList(queryWrapper);

        if (!deletedStaff.isEmpty()) {
            return JsonVO.fail("所选员工中已有已被删除的记录");
        }

        // 2. 逻辑删除员工
        Staff staff = new Staff();
        staff.setDeleted(1);
        LambdaUpdateWrapper<Staff> staffWrapper = Wrappers.lambdaUpdate();
        staffWrapper.in(Staff::getId, ids);
        int staffDeleteCount = staffMapper.update(staff, staffWrapper);

        // 3. 逻辑删除员工机构信息
        StaffOrginfo orgInfoDO = new StaffOrginfo();
        orgInfoDO.setDeleted(1);
        LambdaUpdateWrapper<StaffOrginfo> orgWrapper = Wrappers.lambdaUpdate();
        orgWrapper.in(StaffOrginfo::getStaffId, ids);
        staffOrginfoMapper.update(orgInfoDO, orgWrapper);

        // 4. 判断删除结果
        if (staffDeleteCount == 0) {
            return JsonVO.fail("删除失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) staffDeleteCount);
    }

    @Override
    public JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition) {
        List<Long> ids = condition.getStaffIds();
        Integer status = condition.getStatus();
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要操作的员工");
        }
        if (status == null || (status != 0 && status != 1)) {
            return JsonVO.fail("状态值不合法，只能是 0(离职) 或 1(在职)");
        }

        LambdaUpdateWrapper<Staff> wrapper = Wrappers.lambdaUpdate();
        wrapper.in(Staff::getId, ids)
                .set(Staff::getState, status);
        int updateCount = staffMapper.update(new Staff(), wrapper);

        if (updateCount == 0) {
            return JsonVO.fail("更新失败：所选员工不存在或状态无需变更");
        }
        return JsonVO.success((long) updateCount);
    }

    @Override
    public JsonVO<Long> setStaff(StaffSetDTO condition) {
        List<Long> staffIds = condition.getStaffIds(); // 从 getIds() 改为 getStaffIds()
        Long positionId = condition.getPositionId();
        Long roleId = condition.getRoleId(); // 新增：获取 roleId

        // 新增 roleId 校验
        if (roleId == null) {
            return JsonVO.fail("请选择要设置的角色");
        }
        if (staffIds == null || staffIds.isEmpty()) {
            return JsonVO.fail("请选择要设置角色的员工");
        }
        if (positionId == null) {
            return JsonVO.fail("请选择要设置的职位/角色");
        }
        if (staffPositionMapper.selectById(positionId) == null) {
            return JsonVO.fail("所选职位/角色不存在，请选择合法职位");
        }

        StaffOrginfo orgInfoDO = new StaffOrginfo();
        orgInfoDO.setPositionId(positionId);

        LambdaUpdateWrapper<StaffOrginfo> wrapper = Wrappers.lambdaUpdate();
        wrapper.in(StaffOrginfo::getStaffId, staffIds);

        int updateCount = staffOrginfoMapper.update(orgInfoDO, wrapper);

        if (updateCount == 0) {
            return JsonVO.fail("设置失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) updateCount);
    }


    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<Long> batchTransferOrg(AdminTransferOrgDTO dto) {
        List<Long> staffIds = dto.getStaffIds();
        Long targetOrgId = dto.getTargetOrgId();

        if (staffIds == null || staffIds.isEmpty()) {
            return JsonVO.fail("请选择要转出的员工");
        }
        if (targetOrgId == null || targetOrgId <= 0) {
            return JsonVO.fail("目标机构ID不合法");
        }

        // 检查员工是否存在或已被删除
        LambdaQueryWrapper<Staff> staffCheckWrapper = new LambdaQueryWrapper<>();
        staffCheckWrapper.in(Staff::getId, staffIds).eq(Staff::getDeleted, 0);
        List<Staff> existingStaff = staffMapper.selectList(staffCheckWrapper);
        if (existingStaff.size() != staffIds.size()) {
            return JsonVO.fail("部分员工不存在或已被删除");
        }

        // 检查目标机构是否存在（假设存在机构表，此处需要根据实际情况调整）
        // 这里需要根据实际的机构表结构进行检查，暂时跳过具体实现

        LambdaUpdateWrapper<Staff> staffUpdate = new LambdaUpdateWrapper<>();
        staffUpdate.in(Staff::getId, staffIds)
                .set(Staff::getOrgId, targetOrgId);
        int staffUpdateCount = staffMapper.update(new Staff(), staffUpdate);

        // 处理员工转移后的职位信息 - 直接修改职位
        // 这里假设我们有一个默认的职位分配策略，或者可以根据目标机构的默认职位来设置
        // 由于不能修改DTO，我们可以为每个员工设置一个默认职位，或者保持原职位不变
        LambdaUpdateWrapper<StaffOrginfo> orgUpdate = new LambdaUpdateWrapper<>();
        orgUpdate.in(StaffOrginfo::getStaffId, staffIds)
                .set(StaffOrginfo::getOrgId, targetOrgId);
        
        // 注意：由于DTO中没有目标职位字段，这里我们保持原职位不变
        // 如果需要直接修改职位，需要在DTO中添加目标职位字段
        
        int orgUpdateCount = staffOrginfoMapper.update(null, orgUpdate);

        if (staffUpdateCount == 0 && orgUpdateCount == 0) {
            return JsonVO.fail("转出失败：所选员工不存在或机构无需变更");
        }
        return JsonVO.success((long) staffUpdateCount);
    }

    @Override
    @Transactional(rollbackFor = Exception.class) // 事务控制，异常回滚
    public JsonVO<Long> resetPassword(ResetPasswordDTO resetPasswordDTO) {
        if (resetPasswordDTO == null || resetPasswordDTO.getStaffId() == null) {
            return JsonVO.fail("员工ID不能为空");
        }
        if (!StringUtils.hasText(resetPasswordDTO.getNewPassword())) {
            return JsonVO.fail("新密码不能为空");
        }
        if (resetPasswordDTO.getNewPassword().length() < 6 || resetPasswordDTO.getNewPassword().length() > 20) {
            return JsonVO.fail("新密码长度必须在6-20位之间");
        }

        // 检查员工是否存在或已被删除
        LambdaQueryWrapper<Staff> staffCheckWrapper = new LambdaQueryWrapper<>();
        staffCheckWrapper.eq(Staff::getId, resetPasswordDTO.getStaffId()).eq(Staff::getDeleted, 0);
        Staff staff = staffMapper.selectOne(staffCheckWrapper);
        if (staff == null) {
            return JsonVO.fail("员工不存在或已被删除");
        }

        // 检查员工状态，只允许在职员工重置密码
        if (staff.getState() != 1) {
            return JsonVO.fail("只有在职员工才能重置密码");
        }

        LambdaUpdateWrapper<Staff> passwordUpdate = new LambdaUpdateWrapper<>();
        passwordUpdate.eq(Staff::getId, resetPasswordDTO.getStaffId())
                .set(Staff::getPassword, resetPasswordDTO.getNewPassword());
        int updateCount = staffMapper.update(new Staff(), passwordUpdate);

        if (updateCount == 0) {
            return JsonVO.fail("密码重置失败");
        }
        return JsonVO.success((long) updateCount);
    }


    @Override
    public ResponseEntity<byte[]> exportStaffExcel(StaffQuery query) {
        try {
            if (query == null) {
                query = new StaffQuery();
            }

            LambdaQueryWrapper<Staff> qw = new LambdaQueryWrapper<>();
            if (StrUtil.isNotBlank(query.getName())) {
                qw.like(Staff::getName, query.getName());
            }
            if (StrUtil.isNotBlank(query.getAccount())) {
                qw.eq(Staff::getMobile, query.getAccount());
            }
            if (query.getStatue() != null) {
                qw.eq(Staff::getState, query.getStatue());
            }
            qw.eq(Staff::getDeleted, 0);

            List<Staff> staffList = staffMapper.selectList(qw);
            if (CollectionUtils.isEmpty(staffList)) {
                log.warn("导出失败：暂无员工数据");
                return ResponseEntity.badRequest().body(null);
            }

            List<StaffExportVO> exportList = new ArrayList<>();
            for (Staff staff : staffList) {
                StaffExportVO vo = new StaffExportVO();
                BeanUtils.copyProperties(staff, vo);

                if (staff.getGender() != null) {
                    vo.setGender(staff.getGender() == 1 ? "男" : "女");
                }

                StaffOrginfo orgInfo = staffOrginfoMapper.selectOne(
                        Wrappers.lambdaQuery(StaffOrginfo.class)
                                .eq(StaffOrginfo::getStaffId, staff.getId())
                                .eq(StaffOrginfo::getDeleted, 0)
                );
                if (orgInfo != null && orgInfo.getPositionId() != null) {
                    StaffPosition position = staffPositionMapper.selectById(orgInfo.getPositionId());
                    if (position != null) {
                        vo.setPositionName(position.getName());
                    }
                }

                exportList.add(vo);
            }

            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            EasyExcel.write(outputStream, StaffExportVO.class)
                    .autoCloseStream(Boolean.FALSE)
                    .sheet("员工信息")
                    .doWrite(exportList);

            byte[] bytes = outputStream.toByteArray();
            outputStream.close();

            String fileName = URLEncoder.encode("员工信息表.xlsx", "UTF-8");
            HttpHeaders headers = new HttpHeaders();
            headers.add("Content-Disposition", "attachment;filename=" + fileName);
            headers.add("Access-Control-Expose-Headers", "Content-Disposition");
            headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);

            log.info("员工导出成功 → 条数：{}", exportList.size());
            return new ResponseEntity<>(bytes, headers, HttpStatus.OK);

        } catch (Exception e) {
            log.error("员工导出异常", e);
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(null);
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<Long> updateStaffAvatarByUrl(AdminUpdateStaffAvatarDTO dto) {
        if (dto == null || dto.getStaffId() == null) {
            return JsonVO.fail("员工ID不能为空");
        }
        if (StrUtil.isBlank(dto.getAvatarUrl())) {
            return JsonVO.fail("头像URL不能为空");
        }
        if (!dto.getAvatarUrl().startsWith("http")) {
            return JsonVO.fail("头像URL格式不合法");
        }

        LambdaQueryWrapper<Staff> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Staff::getId, dto.getStaffId())
                .eq(Staff::getDeleted, 0);
        Staff staff = staffMapper.selectOne(queryWrapper);

        if (staff == null) {
            return JsonVO.fail("员工不存在或已被删除");
        }
        if (staff.getState() != 1) {
            return JsonVO.fail("员工非在职状态，不允许修改头像");
        }

        LambdaUpdateWrapper<Staff> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.eq(Staff::getId, dto.getStaffId())
                .set(Staff::getHeadImg, dto.getAvatarUrl());
        int updateCount = staffMapper.update(new Staff(), updateWrapper);

        if (updateCount == 0) {
            return JsonVO.fail("更新头像失败");
        }

        log.info("员工[{}]头像URL更新成功：{}", dto.getStaffId(), dto.getAvatarUrl());
        return JsonVO.success((long) updateCount);
    }


    // ... existing code ...

    @Override
    public JsonVO<PageDTO<LessonRecordVO>> getLessonRecord(LessonRecordQuery condition) {
        try {
            // ===================== 1. 基础参数校验 =====================
            if (condition.getStaffId() == null || condition.getStaffId() <= 0) {
                return JsonVO.fail("员工 ID 不能为空或格式错误");
            }
            if (condition.getPageIndex() < 1) {
                return JsonVO.fail("页码不能小于 1");
            }
            if (condition.getPageSize() < 1 || condition.getPageSize() > 100) {
                return JsonVO.fail("每页条数必须在 1~100 之间");
            }

            Long staffId = Long.valueOf(condition.getStaffId());

            // ===================== 2. 日期校验 =====================
            LocalDate startDate = condition.getStartDate();
            LocalDate endDate = condition.getEndDate();
            if (startDate != null && endDate != null && startDate.isAfter(endDate)) {
                return JsonVO.fail("开始日期不能晚于结束日期");
            }

            // ===================== 3. 分页设置 =====================
            long pageNo = condition.getPageIndex();
            long pageSize = condition.getPageSize();

            // ===================== 4. 查询老师关联的课次 ID =====================
            LambdaQueryWrapper<LessonTeacher> ltWrapper = new LambdaQueryWrapper<>();
            ltWrapper.eq(LessonTeacher::getTeacherId, staffId);
            List<LessonTeacher> lessonTeachers = lessonTeacherMapper.selectList(ltWrapper);

            if (CollectionUtils.isEmpty(lessonTeachers)) {
                PageDTO<LessonRecordVO> emptyPage = new PageDTO<>();
                emptyPage.setRows(Collections.emptyList());
                emptyPage.setPageIndex(pageNo);
                emptyPage.setPageSize(pageSize);
                emptyPage.setTotal(0L);
                emptyPage.setPages(0L);
                return JsonVO.success(emptyPage);
            }

            List<Long> lessonIds = lessonTeachers.stream()
                    .map(LessonTeacher::getLessonId)
                    .collect(Collectors.toList());

            // ===================== 5. 查询课次（带日期过滤） =====================
            LambdaQueryWrapper<Lesson> lessonWrapper = new LambdaQueryWrapper<>();
            lessonWrapper.in(Lesson::getId, lessonIds)
                    .eq(Lesson::getDeleted, 0)
                    .orderByDesc(Lesson::getDate);

            if (startDate != null) {
                lessonWrapper.ge(Lesson::getDate, java.sql.Date.valueOf(startDate));
            }
            if (endDate != null) {
                lessonWrapper.le(Lesson::getDate, java.sql.Date.valueOf(endDate));
            }

            Page<Lesson> lessonPage = lessonMapper.selectPage(new Page<>(pageNo, pageSize), lessonWrapper);
            List<Lesson> lessonList = lessonPage.getRecords();

            // ===================== 6. 批量加载关联数据（避免 N+1 查询） =====================
            Map<Long, Course> courseMap = new HashMap<>();
            Map<Long, Class> classMap = new HashMap<>();
            Map<Long, Classroom> classroomMap = new HashMap<>();
            Map<Long, List<LessonTeacher>> lessonTeacherMap = new HashMap<>();
            Map<Long, Staff> staffMap = new HashMap<>();
            Long totalCanceledCount = 0L;

            if (!CollectionUtils.isEmpty(lessonList)) {
                // 批量查询课程信息
                List<Long> courseIds = lessonList.stream().map(Lesson::getCourseId).distinct().collect(Collectors.toList());
                courseMap = courseMapper.selectBatchIds(courseIds).stream()
                        .collect(Collectors.toMap(Course::getId, c -> c));

                // 批量查询班级信息
                List<Long> classIds = lessonList.stream().map(Lesson::getClassId).distinct().collect(Collectors.toList());
                classMap = classMapper.selectBatchIds(classIds).stream()
                        .collect(Collectors.toMap(Class::getId, c -> c));

                // 批量查询教室信息
                List<Long> roomIds = lessonList.stream().map(Lesson::getRoomId).distinct().collect(Collectors.toList());
                classroomMap = classroomMapper.selectBatchIds(roomIds).stream()
                        .collect(Collectors.toMap(Classroom::getId, c -> c));

                // 批量查询课次关联的老师/助教信息
                List<Long> lessonIdsForTeacher = lessonList.stream().map(Lesson::getId).collect(Collectors.toList());
                LambdaQueryWrapper<LessonTeacher> ltQuery = new LambdaQueryWrapper<>();
                ltQuery.in(LessonTeacher::getLessonId, lessonIdsForTeacher);
                List<LessonTeacher> allLessonTeachers = lessonTeacherMapper.selectList(ltQuery);

                // 按课次 ID 分组，方便后续快速查找
                lessonTeacherMap = allLessonTeachers.stream()
                        .collect(Collectors.groupingBy(LessonTeacher::getLessonId));

                // 批量查询所有老师/助教的详细信息
                List<Long> teacherIds = allLessonTeachers.stream()
                        .map(LessonTeacher::getTeacherId)
                        .distinct()
                        .collect(Collectors.toList());
                if (!teacherIds.isEmpty()) {
                    staffMap = staffMapper.selectBatchIds(teacherIds).stream()
                            .collect(Collectors.toMap(Staff::getId, s -> s));
                }

                // 统计该老师的总取消课数
                LambdaQueryWrapper<Lesson> canceledQuery = new LambdaQueryWrapper<>();
                canceledQuery.in(Lesson::getId, lessonIds)
                        .eq(Lesson::getState, 3);
                totalCanceledCount = lessonMapper.selectCount(canceledQuery);
            }

            // ===================== 7. 转 VO =====================
            List<LessonRecordVO> voList = new ArrayList<>();
            for (Lesson lesson : lessonList) {
                LessonRecordVO vo = new LessonRecordVO();
                BeanUtils.copyProperties(lesson, vo);

                // 拼接上课时间：2026-03-19(四) 20:53~20:53
                String dateStr = lesson.getDate() != null ? DateUtil.format(lesson.getDate(), "yyyy-MM-dd(E)") : "";
                String timeStr = (lesson.getStartTime() != null ? DateUtil.format(lesson.getStartTime(), "HH:mm") : "")
                        + "~" + (lesson.getEndTime() != null ? DateUtil.format(lesson.getEndTime(), "HH:mm") : "");
                vo.setLessonTime(dateStr + " " + timeStr);

                // 填充课程名称
                Course course = courseMap.get(lesson.getCourseId());
                if (course != null) vo.setCourseName(course.getName());

                // 填充班级名称
                Class cls = classMap.get(lesson.getClassId());
                if (cls != null) vo.setClassName(cls.getName());

                // 填充教室名称
                Classroom classroom = classroomMap.get(lesson.getRoomId());
                if (classroom != null) vo.setClassroomName(classroom.getName());

                // 从 Map 中获取老师和助教，避免循环查库
                List<LessonTeacher> teacherList = lessonTeacherMap.getOrDefault(lesson.getId(), Collections.emptyList());
                List<String> teacherNames = new ArrayList<>();
                List<String> assistantNames = new ArrayList<>();

                for (LessonTeacher lt : teacherList) {
                    Staff t = staffMap.get(lt.getTeacherId());
                    if (t == null) continue;

                    if (lt.getTypeNum() == 1) {
                        teacherNames.add(t.getName());
                    } else if (lt.getTypeNum() == 2) {
                        assistantNames.add(t.getName());
                    }
                }
                vo.setTeacherNames(String.join(",", teacherNames));
                vo.setAssistantNames(String.join(",", assistantNames));

                // 状态映射
                if (lesson.getState() == 1) {
                    vo.setStateName("未上课");
                } else if (lesson.getState() == 2) {
                    vo.setStateName("已上课");
                } else {
                    vo.setStateName("已取消");
                }
                vo.setLessonStatus(vo.getStateName());

                // 设置该老师的总取消课数
                vo.setCanceledCount(totalCanceledCount.intValue());

                voList.add(vo);
            }

            // ===================== 8. 构建分页响应 =====================
            PageDTO<LessonRecordVO> pageDTO = PageDTO.create(new Page<LessonRecordVO>()
                    .setCurrent(pageNo)
                    .setSize(pageSize)
                    .setTotal(lessonPage.getTotal())
                    .setRecords(voList)
            );

            return JsonVO.success(pageDTO);

        } catch (Exception e) {
            log.error("员工授课记录查询异常", e);
            return JsonVO.fail(ResultStatus.SERVER_ERROR.getMessage());
        }
    }


    @Override
    public JsonVO<PageDTO<ClassRecordVO>> getClassRecord(ClassRecordQuery condition) {
        try {
            // ===================== 1. 基础参数校验 =====================
            if (condition.getStaffId() == null || condition.getStaffId() <= 0) {
                return JsonVO.fail("员工 ID 不能为空或格式错误");
            }
            if (condition.getPageIndex() < 1) {
                return JsonVO.fail("页码不能小于 1");
            }
            if (condition.getPageSize() < 1 || condition.getPageSize() > 100) {
                return JsonVO.fail("每页条数必须在 1~100 之间");
            }

            Long staffId = Long.valueOf(condition.getStaffId());

            // ===================== 2. 日期校验 =====================
            LocalDate startDate = condition.getStartDate();
            LocalDate endDate = condition.getEndDate();
            if (startDate != null && endDate != null && startDate.isAfter(endDate)) {
                return JsonVO.fail("开始日期不能晚于结束日期");
            }

            // ===================== 3. 分页设置 =====================
            long pageNo = condition.getPageIndex();
            long pageSize = condition.getPageSize();

            // ===================== 4. 查询老师负责的班级 =====================
            LambdaQueryWrapper<Class> classWrapper = new LambdaQueryWrapper<>();
            classWrapper.eq(Class::getTeacherId, staffId)
                    .eq(Class::getDeleted, 0)
                    .orderByDesc(Class::getAddTime);

            if (startDate != null) {
                classWrapper.ge(Class::getStartDate, java.sql.Date.valueOf(startDate));
            }
            if (endDate != null) {
                classWrapper.le(Class::getEndDate, java.sql.Date.valueOf(endDate));
            }

            Page<Class> classPage = classMapper.selectPage(new Page<>(pageNo, pageSize), classWrapper);
            List<Class> classList = classPage.getRecords();

            // ===================== 5. 批量加载关联数据（避免 N+1 查询） =====================
            Map<Long, Course> courseMap = new HashMap<>();
            Map<Long, Subject> subjectMap = new HashMap<>();
            Map<Long, Classroom> classroomMap = new HashMap<>();
            Map<Long, Staff> teacherMap = new HashMap<>();
            Map<Long, Integer> studentCountMap = new HashMap<>();
            Map<Long, Integer> finishedLessonsMap = new HashMap<>();
            Map<Long, Integer> scheduledLessonsMap = new HashMap<>();

            if (!CollectionUtils.isEmpty(classList)) {
                // 批量查询课程信息
                List<Long> courseIds = classList.stream()
                        .map(Class::getCourseId)
                        .filter(Objects::nonNull)
                        .distinct().collect(Collectors.toList());
                courseMap = courseMapper.selectBatchIds(courseIds).stream()
                        .collect(Collectors.toMap(Course::getId, c -> c));

                // 批量查询科目信息（通过课程关联的科目 ID）
                if (!courseMap.isEmpty()) {
                    List<Long> subjectIds = courseMap.values().stream()
                            .map(Course::getSubjectId)
                            .filter(Objects::nonNull)
                            .distinct().collect(Collectors.toList());
                    subjectMap = subjectMapper.selectBatchIds(subjectIds).stream()
                            .collect(Collectors.toMap(Subject::getId, s -> s));
                }

                // 批量查询教室信息
                List<Long> roomIds = classList.stream()
                        .map(Class::getClassroomId)
                        .filter(Objects::nonNull)
                        .distinct().collect(Collectors.toList());
                classroomMap = classroomMapper.selectBatchIds(roomIds).stream()
                        .collect(Collectors.toMap(Classroom::getId, c -> c));

                // 批量查询班主任信息
                List<Long> teacherIds = classList.stream()
                        .map(Class::getTeacherId)
                        .filter(Objects::nonNull)
                        .distinct().collect(Collectors.toList());
                if (!teacherIds.isEmpty()) {
                    teacherMap = staffMapper.selectBatchIds(teacherIds).stream()
                            .collect(Collectors.toMap(Staff::getId, s -> s));
                }

                // 批量统计各班级的已上课次和已排课次
                List<Long> classIds = classList.stream().map(Class::getId).collect(Collectors.toList());

                // 统计已上课次（state=2）
                LambdaQueryWrapper<Lesson> finishedQuery = new LambdaQueryWrapper<>();
                finishedQuery.in(Lesson::getClassId, classIds)
                        .eq(Lesson::getState, 2);
                List<Lesson> finishedLessons = lessonMapper.selectList(finishedQuery);
                finishedLessonsMap = finishedLessons.stream()
                        .collect(Collectors.groupingBy(Lesson::getClassId, Collectors.summingInt(l -> 1)));

                // 统计已排课次（state≠3，即排除已取消的）
                LambdaQueryWrapper<Lesson> scheduledQuery = new LambdaQueryWrapper<>();
                scheduledQuery.in(Lesson::getClassId, classIds)
                        .ne(Lesson::getState, 3);
                List<Lesson> scheduledLessons = lessonMapper.selectList(scheduledQuery);
                scheduledLessonsMap = scheduledLessons.stream()
                        .collect(Collectors.groupingBy(Lesson::getClassId, Collectors.summingInt(l -> 1)));
            }

            // ===================== 6. 转 VO =====================
            List<ClassRecordVO> voList = new ArrayList<>();
            for (Class cls : classList) {
                ClassRecordVO vo = new ClassRecordVO();

                // 班级名称
                vo.setClassName(cls.getName());

                // 课程名称
                if (cls.getCourseId() != null) {
                    Course course = courseMap.get(cls.getCourseId());
                    if (course != null) {
                        vo.setCourseName(course.getName());

                        // 科目名称
                        if (course.getSubjectId() != null) {
                            Subject subject = subjectMap.get(course.getSubjectId());
                            if (subject != null) {
                                vo.setSubjectName(subject.getName());
                            }
                        }
                    }
                }

                // 教室名称
                if (cls.getClassroomId() != null) {
                    Classroom classroom = classroomMap.get(cls.getClassroomId());
                    if (classroom != null) {
                        vo.setClassroomName(classroom.getName());
                    }
                }

                // 班主任姓名（从 Map 获取，避免循环查库）
                if (cls.getTeacherId() != null) {
                    Staff teacher = teacherMap.get(cls.getTeacherId());
                    if (teacher != null) {
                        vo.setTeacherName(teacher.getName());
                    }
                }

                // 学生人数（待补充：需根据 class_student 表统计）
                vo.setStudentCount(studentCountMap.getOrDefault(cls.getId(), 0));
                vo.setPlannedStudentCount(cls.getPlannedStudentCount() != null ? cls.getPlannedStudentCount() : 0);
                vo.setPlannedLessonCount(cls.getPlannedLessonCount() != null ? cls.getPlannedLessonCount() : 0);

                // 已上/已排课进度
                Integer finishedLessons = finishedLessonsMap.getOrDefault(cls.getId(), 0);
                Integer scheduledLessons = scheduledLessonsMap.getOrDefault(cls.getId(), 0);
                vo.setLessonSchedule(finishedLessons + "/" + scheduledLessons);

                // 计算上课进度百分比
                if (cls.getPlannedLessonCount() != null && cls.getPlannedLessonCount() > 0) {
                    int progress = (finishedLessons * 100) / cls.getPlannedLessonCount();
                    vo.setLessonProgress(progress + "%");
                } else {
                    vo.setLessonProgress("0%");
                }

                // 排课备注
                vo.setRemark(cls.getRemark());

                // 开班时间（Date 转 LocalDate）
                if (cls.getStartDate() != null) {
                    vo.setStartDate(cls.getStartDate().toInstant()
                            .atZone(java.time.ZoneId.systemDefault())
                            .toLocalDate());
                }

                // 结业时间（Date 转 LocalDate）
                if (cls.getEndDate() != null) {
                    vo.setEndDate(cls.getEndDate().toInstant()
                            .atZone(java.time.ZoneId.systemDefault())
                            .toLocalDate());
                }

                // 班级状态
                if (cls.getBeOver() != null && cls.getBeOver() == 1) {
                    vo.setStatusName("已完结");
                } else {
                    vo.setStatusName("正常");
                }

                voList.add(vo);
            }

            // ===================== 7. 构建分页响应 =====================
            PageDTO<ClassRecordVO> resultPage = PageDTO.create(new Page<ClassRecordVO>()
                    .setCurrent(classPage.getCurrent())
                    .setSize(classPage.getSize())
                    .setTotal(classPage.getTotal())
                    .setRecords(voList)
            );

            return JsonVO.success(resultPage);

        } catch (Exception e) {
            log.error("员工带班记录查询异常", e);
            return JsonVO.fail(ResultStatus.SERVER_ERROR.getMessage());
        }
    }
}
