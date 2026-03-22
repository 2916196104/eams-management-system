package com.zeroone.star.project.j1.org.staff.service.Impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.zeroone.star.project.DO.StaffDO;
import com.zeroone.star.project.DO.StaffOrginfoDO;
import com.zeroone.star.project.DO.StaffPositionDO;
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

import javax.annotation.Resource;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class StaffServiceimpl extends ServiceImpl<StaffMapper, StaffDO> implements StaffService {
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
        LambdaQueryWrapper<StaffDO> queryWrapper = new LambdaQueryWrapper<>();
        if (condition.getName() != null && !condition.getName().isEmpty()) {
            queryWrapper.like(StaffDO::getName, condition.getName());
        }
        if (condition.getId() != null) {
            queryWrapper.eq(StaffDO::getId, condition.getId());
        }
        if (condition.getAccount() != null) {
            queryWrapper.eq(StaffDO::getMobile, condition.getAccount());
        }
        if (condition.getStatue() != null) {
            queryWrapper.eq(StaffDO::getState, condition.getStatue());
        }
        queryWrapper.eq(StaffDO::getDeleted, 0);
        List<StaffDO> staff = staffMapper.selectList(queryWrapper); // 改用MP原生方法

        PageInfo<StaffDO> pageInfo = new PageInfo<>(staff);

        // 【改动2】分页列表关联机构/职位表，补充职位名称
        List<StaffVO> voList = staff.stream()
                .map(staffDO -> {
                    StaffVO staffVO = new StaffVO();
                    BeanUtils.copyProperties(staffDO, staffVO);

                    // 新增：查机构表
                    StaffOrginfoDO orgInfoDO = staffOrginfoMapper.selectOne(
                            Wrappers.lambdaQuery(StaffOrginfoDO.class)
                                    .eq(StaffOrginfoDO::getStaffId, staffDO.getId())
                                    .eq(StaffOrginfoDO::getDeleted, 0)
                    );
                    if (orgInfoDO != null) {
                        staffVO.setOrgId(orgInfoDO.getOrgId());
                        staffVO.setPositionId(orgInfoDO.getPositionId());
                        // 新增：查职位名称
                        if (orgInfoDO.getPositionId() != null) {
                            StaffPositionDO positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
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

        // 【改动1】迁移Mapper的wrapper到Service层
        LambdaQueryWrapper<StaffDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(StaffDO::getId, condition.getId())
                .eq(StaffDO::getDeleted, 0);
        StaffDO staffDO = staffMapper.selectOne(queryWrapper); // 改用MP原生方法

        if (staffDO == null) {
            return JsonVO.fail("员工不存在");
        }

        StaffDetailsVO staffVO = new StaffDetailsVO();
        BeanUtils.copyProperties(staffDO, staffVO);

        // 【改动2】关联机构表+职位表，补充完整信息
        StaffOrginfoDO orgInfoDO = staffOrginfoMapper.selectOne(
                Wrappers.lambdaQuery(StaffOrginfoDO.class)
                        .eq(StaffOrginfoDO::getStaffId, staffDO.getId())
                        .eq(StaffOrginfoDO::getDeleted, 0)
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
                StaffPositionDO positionDO = staffPositionMapper.selectById(orgInfoDO.getPositionId());
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

        // 【新增1】校验职位ID合法性（如果传了职位ID）
        if (condition.getPositionId() != null) {
            StaffPositionDO positionDO = staffPositionMapper.selectById(condition.getPositionId());
            if (positionDO == null) {
                return JsonVO.fail("职位ID不存在，请选择合法职位");
            }
        }

        // 【改动1】迁移Mapper的保存逻辑到Service层
        StaffDO staff = new StaffDO();
        BeanUtils.copyProperties(condition, staff);
        Long staffId;
        if (condition.getId() == null) {
            // 新增员工
            this.staffMapper.insert(staff);
            staffId = staff.getId();

            // 【新增2】同步新增机构表
            StaffOrginfoDO orgInfoDO = new StaffOrginfoDO();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(condition.getOrgId());
            orgInfoDO.setGroupId(condition.getGroupId()); // 如果DTO有该字段
            orgInfoDO.setComId(condition.getComId());     // 如果DTO有该字段
            orgInfoDO.setDptId(condition.getDptId());     // 如果DTO有该字段
            orgInfoDO.setPositionId(condition.getPositionId());
            orgInfoDO.setDeleted(0); // 未删除
            staffOrginfoMapper.insert(orgInfoDO);
        } else {
            // 修改员工
            this.staffMapper.updateById(staff);
            staffId = staff.getId();

            // 【新增3】同步更新机构表
            StaffOrginfoDO orgInfoDO = new StaffOrginfoDO();
            orgInfoDO.setStaffId(staffId);
            orgInfoDO.setOrgId(condition.getOrgId());
            orgInfoDO.setPositionId(condition.getPositionId());
            orgInfoDO.setGroupId(condition.getGroupId());
            orgInfoDO.setComId(condition.getComId());
            orgInfoDO.setDptId(condition.getDptId());

            LambdaUpdateWrapper<StaffOrginfoDO> updateWrapper = new LambdaUpdateWrapper<>();
            updateWrapper.eq(StaffOrginfoDO::getStaffId, staffId);
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
        StaffDO staffDO = new StaffDO();
        staffDO.setDeleted(1);
        LambdaUpdateWrapper<StaffDO> staffWrapper = Wrappers.lambdaUpdate();
        staffWrapper.in(StaffDO::getId, ids);
        int staffDeleteCount = staffMapper.update(staffDO, staffWrapper);

        // 2. 同步逻辑删除员工机构表
        StaffOrginfoDO orgInfoDO = new StaffOrginfoDO();
        orgInfoDO.setDeleted(1);
        LambdaUpdateWrapper<StaffOrginfoDO> orgWrapper = Wrappers.lambdaUpdate();
        orgWrapper.in(StaffOrginfoDO::getStaffId, ids);
        staffOrginfoMapper.update(orgInfoDO, orgWrapper);

        if (staffDeleteCount == 0) {
            return JsonVO.fail("删除失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) staffDeleteCount);
    }

    @Override
    public JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition) {
        StaffDO staff = new StaffDO();
        List<Long> ids = condition.getIds();
        Integer status = condition.getStatus();
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要操作的员工");
        }
        if (status == null || (status != 0 && status != 1)) {
            return JsonVO.fail("状态值不合法，只能是 0(离职) 或 1(在职)");
        }

        LambdaUpdateWrapper<StaffDO> wrapper = Wrappers.lambdaUpdate();
        wrapper.in(StaffDO::getId, ids)
                .set(StaffDO::getState, status);
        int updateCount = staffMapper.update(new StaffDO(), wrapper);

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
        StaffOrginfoDO orgInfoDO = new StaffOrginfoDO();
        orgInfoDO.setPositionId(positionId); // 设置目标职位

        LambdaUpdateWrapper<StaffOrginfoDO> wrapper = Wrappers.lambdaUpdate();
        wrapper.in(StaffOrginfoDO::getStaffId, staffIds); // 批量匹配员工ID

        int updateCount = staffOrginfoMapper.update(orgInfoDO, wrapper);

        if (updateCount == 0) {
            return JsonVO.fail("设置失败：所选员工不存在或已被删除");
        }
        return JsonVO.success((long) updateCount);
    }


}
