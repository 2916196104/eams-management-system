package com.zeroone.star.project.j1.org.staff.service.Impl;

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
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.StaffSetDTO;
import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.j1.org.staff.mapper.StaffMapper;
import com.zeroone.star.project.j1.org.staff.mapper.StaffOrginfoMapper;
import com.zeroone.star.project.j1.org.staff.mapper.StaffPositionMapper;
import com.zeroone.star.project.j1.org.staff.service.StaffService;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class StaffServiceimpl extends ServiceImpl<StaffMapper, Staff> implements StaffService {
    // 新增注入关联表Mapper
    @Autowired
    private StaffOrginfoMapper staffOrginfoMapper;
    @Autowired
    private StaffPositionMapper staffPositionMapper;
@Autowired StaffMapper staffMapper;
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        long pageNo = condition.getPageIndex();
        long pageSize = condition.getPageSize();
        PageHelper.startPage((int)pageNo,(int)pageSize);

        // 【改动1】迁移Mapper的wrapper到Service层
        LambdaQueryWrapper<Staff> queryWrapper = new LambdaQueryWrapper<>();
        if (condition.getName() != null && !condition.getName().isEmpty()) {
            queryWrapper.like(Staff::getName, condition.getName());
        }
        if (condition.getId() != null) {
            queryWrapper.eq(Staff::getId, condition.getId());
        }
        if (condition.getAccount() != null) {
            queryWrapper.eq(Staff::getMobile, condition.getAccount());
        }
        if (condition.getStatue() != null) {
            queryWrapper.eq(Staff::getState, condition.getStatue());
        }
        queryWrapper.eq(Staff::getDeleted, 0);
        List<Staff> staff = staffMapper.selectList(queryWrapper); // 改用MP原生方法

        PageInfo<Staff> pageInfo = new PageInfo<>(staff);

        // 分页列表关联机构/职位表，补充职位名称
        List<StaffVO> voList = staff.stream()
                .map(staffDO -> {
                    StaffVO staffVO = new StaffVO();
                    BeanUtils.copyProperties(staffDO, staffVO);

                    // 新增：查机构表
                    StaffOrginfo orgInfoDO = staffOrginfoMapper.selectOne(
                            Wrappers.lambdaQuery(StaffOrginfo.class)
                                    .eq(StaffOrginfo::getStaffId, staffDO.getId())
                                    .eq(StaffOrginfo::getDeleted, 0)
                    );
                    if (orgInfoDO != null) {
                        staffVO.setOrgId(orgInfoDO.getOrgId());
                        staffVO.setPositionId(orgInfoDO.getPositionId());
                        // 新增：查职位名称
                        if (orgInfoDO.getPositionId() != null) {
                            StaffPosition positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
                            if (positionDO != null) {
                                staffVO.setPositionName(positionDO.getName()); // 补充职位名称
                            }
                        }
                    }
                    return staffVO;
                })
                .collect(Collectors.toList());

        Page<StaffVO> mpPage = new Page<>();
        mpPage.setCurrent(pageNo);
        mpPage.setSize(pageSize);
        mpPage.setTotal(pageInfo.getTotal());
        mpPage.setPages(pageInfo.getPages());
        mpPage.setRecords(voList);

        PageDTO<StaffVO> pageDTO = PageDTO.create(mpPage);
        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<StaffDetailsVO> queryStaff(StaffQuery condition) {
        if (condition.getId() == null) {
            return JsonVO.fail("员工ID不能为空");
        }

        // 迁移Mapper的wrapper到Service层
        LambdaQueryWrapper<Staff> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Staff::getId, condition.getId())
                .eq(Staff::getDeleted, 0);
        Staff staff = staffMapper.selectOne(queryWrapper); // 改用MP原生方法

        if (staff == null) {
            return JsonVO.fail("员工不存在");
        }

        StaffDetailsVO staffVO = new StaffDetailsVO();
        BeanUtils.copyProperties(staff, staffVO);

        // 【改动2】关联机构表+职位表，补充完整信息
        StaffOrginfo orgInfoDO = staffOrginfoMapper.selectOne(
                Wrappers.lambdaQuery(StaffOrginfo.class)
                        .eq(StaffOrginfo::getStaffId, staff.getId())
                        .eq(StaffOrginfo::getDeleted, 0)
        );
        if (orgInfoDO != null) {
            // 补充机构表字段
            staffVO.setOrgId(orgInfoDO.getOrgId());
            staffVO.setGroupId(orgInfoDO.getGroupId());
            staffVO.setComId(orgInfoDO.getComId());
            staffVO.setDptId(orgInfoDO.getDptId());
            staffVO.setPositionId(orgInfoDO.getPositionId());

            // 补充职位名称
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
        // 保留你的原有校验逻辑
        if(condition.getName() == null||condition.getName().equals("")){
            return JsonVO.fail("姓名不能为空");
        }
        if(condition.getMobile() == null||condition.getMobile().equals("")){
            return JsonVO.fail("账号不能为空");
        }
        if(condition.getOrgId() == null){
            return JsonVO.fail("机构不能为空");
        }
        if(condition.getGender() == null){
            return JsonVO.fail("性别不能为空");
        }

        // 校验职位ID合法性（如果传了职位ID）
        if (condition.getPositionId() != null) {
            StaffPosition positionDO = staffPositionMapper.selectById(condition.getPositionId());
            if (positionDO == null) {
                return JsonVO.fail("职位ID不存在，请选择合法职位");
            }
        }

        // 迁移Mapper的保存逻辑到Service层
        Staff staff = new Staff();
        BeanUtils.copyProperties(condition, staff);
        Long staffId;
        if (condition.getId() == null) {
            // 新增员工
            this.staffMapper.insert(staff);
            staffId = staff.getId();

            // 同步新增机构表
            StaffOrginfo orgInfoDO = new StaffOrginfo();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(condition.getOrgId());
            orgInfoDO.setGroupId(condition.getGroupId());
            orgInfoDO.setComId(condition.getComId());
            orgInfoDO.setDptId(condition.getDptId());
            orgInfoDO.setPositionId(condition.getPositionId());
            orgInfoDO.setDeleted(0);
            staffOrginfoMapper.insert(orgInfoDO);
        } else {
            // 修改员工
            this.staffMapper.updateById(staff);
            staffId = staff.getId();
            // 同步更新机构表
            StaffOrginfo orgInfoDO = new StaffOrginfo();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(condition.getOrgId());
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

        // 1. 逻辑删除员工主表
        Staff staff = new Staff();
        staff.setDeleted(1);
        LambdaUpdateWrapper<Staff> staffWrapper = Wrappers.lambdaUpdate();
        staffWrapper.in(Staff::getId, ids);
        int staffDeleteCount = staffMapper.update(staff, staffWrapper);

        // 2. 同步逻辑删除员工机构表
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
        Staff staff = new Staff();
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
        List<Long> staffIds = condition.getIds(); // 员工ID列表
        Long positionId = condition.getPositionId();   // 目标职位ID（角色对应职位）

        // 1. 基础校验
        if (staffIds == null || staffIds.isEmpty()) {
            return JsonVO.fail("请选择要设置角色的员工");
        }
        if (positionId == null) {
            return JsonVO.fail("请选择要设置的职位/角色");
        }
        // 校验职位ID合法性（必须存在于职位表）
        if (staffPositionMapper.selectById(positionId) == null) {
            return JsonVO.fail("所选职位/角色不存在，请选择合法职位");
        }

        // 2. 批量更新员工机构表的 positionId
        StaffOrginfo orgInfoDO = new StaffOrginfo();
        orgInfoDO.setPositionId(positionId); // 设置目标职位

        LambdaUpdateWrapper<StaffOrginfo> wrapper = Wrappers.lambdaUpdate();
        wrapper.in(StaffOrginfo::getStaffId, staffIds); // 批量匹配员工ID

        int updateCount = staffOrginfoMapper.update(orgInfoDO, wrapper);

        if (updateCount == 0) {
            return JsonVO.fail("设置失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) updateCount);
    }


}
