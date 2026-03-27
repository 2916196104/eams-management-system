package com.zeroone.star.project.j1.org.staff.service.Impl;

import cn.hutool.json.JSONObject;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.zeroone.star.project.DO.Staff;
import com.zeroone.star.project.DO.StaffOrginfo;
import com.zeroone.star.project.DO.StaffPosition;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.StaffSetDTO;
import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.j1.org.staff.mapper.StaffMapper;
import com.zeroone.star.project.j1.org.staff.mapper.StaffOrginfoMapper;
import com.zeroone.star.project.j1.org.staff.mapper.StaffPositionMapper;
import com.zeroone.star.project.j1.org.staff.service.StaffService;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import io.swagger.annotations.ApiModelProperty;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;
import cn.hutool.core.convert.Convert;

import javax.servlet.http.HttpServletRequest;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class StaffServiceimpl extends ServiceImpl<StaffMapper, Staff> implements StaffService {

    @Autowired
    private StaffOrginfoMapper staffOrginfoMapper;
    @Autowired
    private StaffPositionMapper staffPositionMapper;
    @Autowired
    private StaffMapper staffMapper;

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
        PageHelper.startPage((int)pageNo, (int)pageSize);

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

                    // ====================== 【修复】先复制，再安全赋值 ======================
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
                        staffVO.setPositionId(orgInfoDO.getPositionId());

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
        if (condition.getId() == null) {
            return JsonVO.fail("员工ID不能为空");
        }

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
            staffVO.setGroupId(orgInfoDO.getGroupId());
            staffVO.setComId(orgInfoDO.getComId());
            staffVO.setDptId(orgInfoDO.getDptId());
            staffVO.setPositionId(orgInfoDO.getPositionId());

            // 设置职位名称
            if (orgInfoDO.getPositionId() != null) {
                StaffPosition positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
                if (positionDO != null) {
                    staffVO.setPositionName(positionDO.getName());
                }
            }
        }

        return JsonVO.success(staffVO);
    }

    @Override
    public JsonVO<Long> saveStaff(StaffDTO condition) {
        Long orgId = getSafeOrgId();

        if(condition.getName() == null||condition.getName().equals("")){
            return JsonVO.fail("姓名不能为空");
        }
        if(condition.getMobile() == null||condition.getMobile().equals("")){
            return JsonVO.fail("账号不能为空");
        }
        if(condition.getGender() == null){
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
        if (condition.getId() == null) {
            this.staffMapper.insert(staff);
            staffId = staff.getId();

            StaffOrginfo orgInfoDO = new StaffOrginfo();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(orgId);
            orgInfoDO.setGroupId(condition.getGroupId());
            orgInfoDO.setComId(condition.getComId());
            orgInfoDO.setDptId(condition.getDptId());
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
            orgInfoDO.setGroupId(condition.getGroupId());
            orgInfoDO.setComId(condition.getComId());
            orgInfoDO.setDptId(condition.getDptId());

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

        Staff staff = new Staff();
        staff.setDeleted(1);
        LambdaUpdateWrapper<Staff> staffWrapper = Wrappers.lambdaUpdate();
        staffWrapper.in(Staff::getId, ids);
        int staffDeleteCount = staffMapper.update(staff, staffWrapper);

        StaffOrginfo orgInfoDO = new StaffOrginfo();
        orgInfoDO.setDeleted(1);
        LambdaUpdateWrapper<StaffOrginfo> orgWrapper = Wrappers.lambdaUpdate();
        orgWrapper.in(StaffOrginfo::getStaffId, ids);
        staffOrginfoMapper.update(orgInfoDO, orgWrapper);

        if (staffDeleteCount == 0) {
            return JsonVO.fail("删除失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) staffDeleteCount);
    }

    @Override
    public JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition) {
        List<Long> ids = condition.getIds();
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
        List<Long> staffIds = condition.getIds();
        Long positionId = condition.getPositionId();

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
}