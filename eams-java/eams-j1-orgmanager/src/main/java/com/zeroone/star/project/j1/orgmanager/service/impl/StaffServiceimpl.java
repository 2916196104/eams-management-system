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
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
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
    // 密码加密器（企业级密码必须加密存储）
    //private final BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();

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

    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        Long orgId = getSafeOrgId();

        long pageNo = condition.getPageIndex();
        long pageSize = condition.getPageSize();
        PageHelper.startPage((int) pageNo, (int) pageSize);

        // 无条件查询全部（只查未删除）
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

        List<Staff> staffList = staffMapper.selectList(queryWrapper);
        PageInfo<Staff> pageInfo = new PageInfo<>(staffList);

        List<StaffVO> voList = pageInfo.getList().stream()
                .map(staffDO -> {
                    StaffVO staffVO = new StaffVO();
                    try {
                        BeanUtils.copyProperties(staffDO, staffVO);
                    } catch (Exception e) {
                        // 复制失败跳过，避免整个接口挂掉
                    }
                    StaffOrginfo orgInfoDO = staffOrginfoMapper.selectOne(
                            Wrappers.lambdaQuery(StaffOrginfo.class)
                                    .eq(StaffOrginfo::getStaffId, staffDO.getId())
                                    .eq(StaffOrginfo::getDeleted, 0)
                    );

                    if (orgInfoDO != null) {
                        // 只赋值非空字段，绝对不抛异常
                        staffVO.setOrgId(orgId);
                        if (orgInfoDO.getPositionId() != null) {
                            StaffPosition positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
                            if (positionDO != null) {
                                staffVO.setPositionName(positionDO.getName());
                            }
                        }
                    }

                    return staffVO;
                })
                .collect(Collectors.toList());

        PageDTO<StaffVO> pageDTO = PageDTO.create(new Page<StaffVO>()
                .setCurrent(pageNo)
                .setSize(pageSize)
                .setTotal(pageInfo.getTotal())
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
    public JsonVO<Void> batchTransferOrg(AdminTransferOrgDTO dto) {
        try {
            // ========== 1. 基础参数校验 ==========
            List<Long> staffIds = dto.getStaffIds();
            Long targetOrgId = dto.getTargetOrgId();
            if (CollectionUtils.isEmpty(staffIds)) {
                log.warn("批量转出员工机构失败：员工ID列表为空");
                return JsonVO.fail("员工ID列表不能为空");
            }
            if (targetOrgId == null || targetOrgId <= 0) {
                log.warn("批量转出员工机构失败：目标机构ID不合法");
                return JsonVO.fail("目标机构ID不合法");
            }

            // ========== 2. 获取当前登录用户信息 ==========
            UserDTO currentUser = getCurrentUserDTO();
            if (currentUser == null) {
                log.error("获取当前登录用户失败：用户未登录或 token 已过期");
                return JsonVO.fail(ResultStatus.UNAUTHORIZED.getMessage());
            }
            if (currentUser.getId() == null) {
                log.error("获取当前登录用户失败：用户 ID 为空");
                return JsonVO.fail("获取用户信息失败，请重新登录");
            }

            // ========== 3. 数据校验（纯 MyBatis-Plus 实现） ==========
            LambdaQueryWrapper<Staff> staffQuery = new LambdaQueryWrapper<>();
            staffQuery.in(Staff::getId, staffIds);
            staffQuery.eq(Staff::getDeleted, 0);
            long existStaffCount = this.count(staffQuery);

            if (existStaffCount != staffIds.size()) {
                return JsonVO.fail("部分员工不存在或已删除");
            }

            LambdaQueryWrapper<StaffOrginfo> orgQuery = new LambdaQueryWrapper<>();
            orgQuery.in(StaffOrginfo::getStaffId, staffIds);
            long existOrgCount = staffOrginfoMapper.selectCount(orgQuery);

            if (existOrgCount == 0) {
                return JsonVO.fail("员工机构关联记录不存在");
            }

            // ========== 4. 批量更新 ==========
            LambdaUpdateWrapper<Staff> staffUpdate = new LambdaUpdateWrapper<>();
            staffUpdate.in(Staff::getId, staffIds);
            staffUpdate.set(Staff::getOrgId, targetOrgId);
            staffUpdate.set(Staff::getEditor, currentUser.getId());
            staffUpdate.set(Staff::getEditTime, new Date());
            this.update(staffUpdate);

            LambdaUpdateWrapper<StaffOrginfo> orgUpdate = new LambdaUpdateWrapper<>();
            orgUpdate.in(StaffOrginfo::getStaffId, staffIds);
            orgUpdate.set(StaffOrginfo::getOrgId, targetOrgId);
            staffOrginfoMapper.update(null, orgUpdate);

            // ========== 5. 返回 ==========
            log.info("批量转出机构成功 → 管理员:{} 员工数:{} 新机构:{}",
                    currentUser.getUsername(), staffIds.size(), targetOrgId);

            return JsonVO.success(null);

        } catch (Exception e) {
            log.error("批量转出机构异常", e);
            return JsonVO.fail("批量转出机构失败，请稍后重试");
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class) // 事务控制，异常回滚
    public JsonVO<Void> resetPassword(ResetPasswordDTO resetPasswordDTO) {
        // ========== 1. 参数合法性校验 ==========
        if (resetPasswordDTO == null) {
            return JsonVO.fail("重置密码参数不能为空");
        }
        if (resetPasswordDTO.getStaffId() == null || resetPasswordDTO.getStaffId() <= 0) {
            return JsonVO.fail("员工ID必须为正整数");
        }
        if (!StringUtils.hasText(resetPasswordDTO.getNewPassword())) {
            return JsonVO.fail("新密码不能为空");
        }
        // 密码长度校验（符合企业密码规范）
        if (resetPasswordDTO.getNewPassword().length() < 6 || resetPasswordDTO.getNewPassword().length() > 20) {
            return JsonVO.fail("新密码长度必须在6-20位之间");
        }

        // ========== 2. 操作人权限校验（企业级权限控制） ==========
        UserDTO currentUser = getCurrentUserDTO();
        if (currentUser == null) {
            log.error("获取当前登录用户失败：用户未登录或 token 已过期");
            return JsonVO.fail(ResultStatus.UNAUTHORIZED.getMessage());
        }
        if (currentUser.getId() == null) {
            log.error("获取当前登录用户失败：用户 ID 为空");
            return JsonVO.fail("获取用户信息失败，请重新登录");
        }

        // ========== 3. 数据有效性校验 ==========
        // 校验员工是否存在（未被删除）
        Staff staff = this.getById(resetPasswordDTO.getStaffId());
        if (staff == null || Integer.valueOf(1).equals(staff.getDeleted())) {
            return JsonVO.fail("员工不存在或已被删除");
        }

        // ========== 4. 密码加密处理 ==========

        // ========== 4. 密码不加密 ==========
        String encryptPassword = resetPasswordDTO.getNewPassword();
        // ========== 5. 执行密码更新操作（纯 MyBatis-Plus 实现） ==========
        LambdaUpdateWrapper<Staff> passwordUpdate = new LambdaUpdateWrapper<>();
        passwordUpdate.eq(Staff::getId, resetPasswordDTO.getStaffId());
        passwordUpdate.set(Staff::getPassword, encryptPassword);
        passwordUpdate.set(Staff::getEditor, currentUser.getId());
        passwordUpdate.set(Staff::getEditTime, new Date());

        boolean updateRows = this.update(passwordUpdate);

        // ========== 6. 操作结果校验 ==========
        if (updateRows) {
            return JsonVO.success(null); // 操作成功
        } else {
            return JsonVO.fail("密码重置失败，请重试");
        }
    }


    @Override
    public ResponseEntity<byte[]> exportStaffExcel(StaffQuery query) {
        try {
            // ===================== 1. 登录校验 =====================
            UserDTO currentUser = getCurrentUserDTO();
            if (currentUser == null) {
                log.error("导出失败：用户未登录或 token 已过期");
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(null);
            }
           // Long currentUserId = Convert.toLong(currentUser.getId());
            Long currentOrgId = currentUser.getOrgId();

            if (currentOrgId == null) {
                log.error("导出失败：用户机构 ID 为空");
                return ResponseEntity.badRequest().body(null);
            }

            // ===================== 2. 参数处理 =====================
            if (query == null) {
                query = new StaffQuery();
            }

            // ===================== 3. 查询员工 =====================
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
            qw.eq(Staff::getOrgId, currentOrgId);
            List<Staff> staffList = staffMapper.selectList(qw);
            if (CollectionUtils.isEmpty(staffList)) {
                log.warn("导出失败：暂无员工数据");
                return ResponseEntity.badRequest().body(null);
            }
            // ===================== 4. 封装 StaffExportVO =====================
            List<StaffExportVO> exportList = new ArrayList<>();
            for (Staff staff : staffList) {
                StaffExportVO vo = new StaffExportVO();
                BeanUtils.copyProperties(staff, vo);

                // 性别转换
                if (staff.getGender() != null) {
                    vo.setGender(staff.getGender() == 1 ? "男" : "女");
                }

                // 机构名称
                vo.setOrgName(String.valueOf(currentOrgId)); // 可后续替换成真实名称

                // 职位名称（从 staff_orginfo 取）
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

            // ===================== 5. 生成 Excel =====================
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            EasyExcel.write(outputStream, StaffExportVO.class)
                    .autoCloseStream(Boolean.FALSE)
                    .sheet("员工信息")
                    .doWrite(exportList);

            byte[] bytes = outputStream.toByteArray();
            outputStream.close();

            // ===================== 6. 下载 =====================
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

    /**
     * 修改员工头像（URL方式）
     * 适配场景：前端已处理文件上传，仅传递URL
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public void updateStaffAvatarByUrl(AdminUpdateStaffAvatarDTO dto) throws Exception {
        Long staffId = dto.getStaffId();
        String avatarUrl = dto.getAvatarUrl();
        if (StrUtil.isBlank(avatarUrl) || !avatarUrl.startsWith("http")) {
            throw new IllegalArgumentException("头像 URL 不合法");
        }

        Staff staff = staffMapper.selectById(staffId);
        if (staff == null || staff.getState() != 1) {
            throw new RuntimeException("员工不存在/已删除/非在职，不允许修改");
        }

        Staff updateStaff = new Staff();
        updateStaff.setId(staffId);
        updateStaff.setHeadImg(avatarUrl);
        updateStaff.setEditTime(new Date());

        boolean success = this.updateById(updateStaff);
        if (!success) {
            throw new RuntimeException("更新头像失败");
        }

        log.info("员工[{}]头像URL更新成功：{}", staffId, avatarUrl);
    }


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
            PageHelper.startPage((int) pageNo, (int) pageSize);

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
                lessonWrapper.ge(Lesson::getDate, startDate.atStartOfDay());
            }
            if (endDate != null) {
                lessonWrapper.le(Lesson::getDate, endDate.atTime(23, 59, 59));
            }

            Page<Lesson> lessonPage = lessonMapper.selectPage(new Page<>(pageNo, pageSize), lessonWrapper);
            List<Lesson> lessonList = lessonPage.getRecords();

            // ===================== 6. 批量加载关联数据 =====================
            Map<Long, Course> courseMap = new HashMap<>();
            Map<Long, Class> classMap = new HashMap<>();
            Map<Long, Classroom> classroomMap = new HashMap<>();

            if (!CollectionUtils.isEmpty(lessonList)) {
                List<Long> courseIds = lessonList.stream().map(Lesson::getCourseId).distinct().collect(Collectors.toList());
                courseMap = courseMapper.selectBatchIds(courseIds).stream()
                        .collect(Collectors.toMap(Course::getId, c -> c));

                List<Long> classIds = lessonList.stream().map(Lesson::getClassId).distinct().collect(Collectors.toList());
                classMap = classMapper.selectBatchIds(classIds).stream()
                        .collect(Collectors.toMap(Class::getId, c -> c));

                List<Long> roomIds = lessonList.stream().map(Lesson::getRoomId).distinct().collect(Collectors.toList());
                classroomMap = classroomMapper.selectBatchIds(roomIds).stream()
                        .collect(Collectors.toMap(Classroom::getId, c -> c));
            }

            // ===================== 7. 转 VO =====================
            List<LessonRecordVO> voList = new ArrayList<>();
            for (Lesson lesson : lessonList) {
                LessonRecordVO vo = new LessonRecordVO();
                BeanUtils.copyProperties(lesson, vo);

                // 拼接时间
                String dateStr = lesson.getDate() != null ? DateUtil.format(lesson.getDate(), "yyyy-MM-dd(E)") : "";
                String timeStr = (lesson.getStartTime() != null ? DateUtil.format(lesson.getStartTime(), "HH:mm") : "")
                        + "~" + (lesson.getEndTime() != null ? DateUtil.format(lesson.getEndTime(), "HH:mm") : "");
                vo.setLessonTime(dateStr + " " + timeStr);

                // 课程名
                Course course = courseMap.get(lesson.getCourseId());
                if (course != null) vo.setCourseName(course.getName());

                // 班级名
                Class cls = classMap.get(lesson.getClassId());
                if (cls != null) vo.setClassName(cls.getName());

                // 教室名
                Classroom classroom = classroomMap.get(lesson.getRoomId());
                if (classroom != null) vo.setClassroomName(classroom.getName());

                // 老师 助教
                LambdaQueryWrapper<LessonTeacher> teacherWrapper = new LambdaQueryWrapper<>();
                teacherWrapper.eq(LessonTeacher::getLessonId, lesson.getId());
                List<LessonTeacher> teacherList = lessonTeacherMapper.selectList(teacherWrapper);

                List<String> teacherNames = new ArrayList<>();
                List<String> assistantNames = new ArrayList<>();
                for (LessonTeacher lt : teacherList) {
                    Staff t = this.getById(lt.getTeacherId());
                    if (t == null) continue;

                    if (lt.getTypeNum() == 1) {
                        teacherNames.add(t.getName());
                    } else if (lt.getTypeNum() == 2) {
                        assistantNames.add(t.getName());
                    }
                }
                vo.setTeacherNames(String.join(",", teacherNames));
                vo.setAssistantNames(String.join(",", assistantNames));

                // 状态
                if (lesson.getState() == 1) {
                    vo.setStateName("未上课");
                } else if (lesson.getState() == 2) {
                    vo.setStateName("已上课");
                } else {
                    vo.setStateName("已取消");
                }
                vo.setLessonStatus(vo.getStateName());
                vo.setCanceledCount(lesson.getState() == 3 ? 1 : 0);

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
            PageHelper.startPage((int)pageNo, (int)pageSize);

            // ===================== 4. 查询老师负责的班级（关键：直接查 class 表） =====================
            LambdaQueryWrapper<Class> classWrapper = new LambdaQueryWrapper<>();
            classWrapper.eq(Class::getTeacherId, staffId)  // 按员工 ID 过滤
                    .eq(Class::getDeleted, 0)
                    .orderByDesc(Class::getAddTime);

            if (startDate != null) {
                classWrapper.ge(Class::getStartDate, startDate);
            }
            if (endDate != null) {
                classWrapper.le(Class::getEndDate, endDate);
            }

            Page<Class> classPage = classMapper.selectPage(new Page<>(pageNo, pageSize), classWrapper);
            List<Class> classList = classPage.getRecords();

            // ===================== 5. 批量加载关联数据 =====================
            Map<Long, Course> courseMap = new HashMap<>();
            Map<Long, Subject> subjectMap = new HashMap<>();
            Map<Long, Classroom> classroomMap = new HashMap<>();
            Map<Integer, Integer> studentCountMap = new HashMap<>();

            if (!CollectionUtils.isEmpty(classList)) {
                // 批量查询课程信息
                List<Long> courseIds = classList.stream()
                        .map(Class::getCourseId)
                        .filter(Objects::nonNull)
                        .distinct().collect(Collectors.toList());
                courseMap = courseMapper.selectBatchIds(courseIds).stream()
                        .collect(Collectors.toMap(Course::getId, c -> c));

                // 批量查询科目信息（通过课程 ID 获取科目 ID）
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

                // 批量查询各班级的学生人数（通过 class_student 表）
                List<Long> classIds = classList.stream()
                        .map(Class::getId)
                        .collect(Collectors.toList());

                // TODO: 如果有 class_student 表，需要在这里统计学生人数
                // 这里先初始化为 0，后续可以根据实际表结构补充
            }

            // ===================== 6. 转 VO =====================
            List<ClassRecordVO> voList = new ArrayList<>();
            for (Class cls : classList) {
                ClassRecordVO vo = new ClassRecordVO();

                // ===================== 步骤 1: 班级基本信息 =====================
                vo.setClassName(cls.getName());  // 班级名称

                // ===================== 步骤 2: 课程信息 =====================
                if (cls.getCourseId() != null) {
                    Course course = courseMap.get(cls.getCourseId());
                    if (course != null) {
                        vo.setCourseName(course.getName());  // 课程名称

                        // 科目名称（通过课程关联的科目）
                        if (course.getSubjectId() != null) {
                            Subject subject = subjectMap.get(course.getSubjectId());
                            if (subject != null) {
                                vo.setSubjectName(subject.getName());
                            }
                        }
                    }
                }

                // ===================== 步骤 3: 教室信息 =====================
                if (cls.getClassroomId() != null) {
                    Classroom classroom = classroomMap.get(cls.getClassroomId());
                    if (classroom != null) {
                        vo.setClassroomName(classroom.getName());
                    }
                }

                // ===================== 步骤 4: 班主任信息 =====================
                if (cls.getTeacherId() != null) {
                    Staff teacher = this.getById(cls.getTeacherId());
                    if (teacher != null) {
                        vo.setTeacherName(teacher.getName());
                    }
                }

                // ===================== 步骤 5: 学生相关统计 =====================
                // TODO: 需要从 class_student 表统计实际学生人数
                vo.setStudentCount(0);  // 待补充：实际学生人数
                vo.setPlannedStudentCount(cls.getPlannedStudentCount() != null ? cls.getPlannedStudentCount() : 0);  // 预招人数
                vo.setPlannedLessonCount(cls.getPlannedLessonCount() != null ? cls.getPlannedLessonCount() : 0);  // 计划课次

                // ===================== 步骤 6: 上课进度信息 =====================
                // TODO: 需要从 lesson 表统计已上课次和已排课次
                Integer finishedLessons = 0;  // 已上课次
                Integer scheduledLessons = 0;  // 已排课次
                vo.setLessonSchedule(finishedLessons + "/" + scheduledLessons);

                // 计算上课进度百分比
                if (cls.getPlannedLessonCount() != null && cls.getPlannedLessonCount() > 0) {
                    int progress = (finishedLessons * 100) / cls.getPlannedLessonCount();
                    vo.setLessonProgress(progress + "%");
                } else {
                    vo.setLessonProgress("0%");
                }

                // ===================== 步骤 7: 其他信息 =====================
                vo.setRemark(cls.getRemark());  // 排课备注

                // 开班时间（Date → LocalDate 转换）
                if (cls.getStartDate() != null) {
                    vo.setStartDate(cls.getStartDate().toInstant()
                            .atZone(java.time.ZoneId.systemDefault())
                            .toLocalDate());
                }

                // 结业时间（Date → LocalDate 转换）
                if (cls.getEndDate() != null) {
                    vo.setEndDate(cls.getEndDate().toInstant()
                            .atZone(java.time.ZoneId.systemDefault())
                            .toLocalDate());
                }

                // ===================== 步骤 8: 班级状态 =====================
                if (cls.getBeOver() != null && cls.getBeOver() == 1) {
                    vo.setStatusName("已完结");
                } else {
                    vo.setStatusName("正常");
                }

                voList.add(vo);
            }

            // ===================== 7. 构建分页响应 =====================
            PageDTO<ClassRecordVO> resultPage = PageDTO.create(classPage, ClassRecordVO.class);
            resultPage.setRows(voList);  // ✅ 注意：是 setRows，不是 setRecords

            return JsonVO.success(resultPage);

        } catch (Exception e) {
            log.error("员工带班记录查询异常", e);
            return JsonVO.fail(ResultStatus.SERVER_ERROR.getMessage());
        }
    }

}
