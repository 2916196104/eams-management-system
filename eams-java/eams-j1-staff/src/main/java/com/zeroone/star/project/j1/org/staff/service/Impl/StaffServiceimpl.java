package com.zeroone.star.project.j1.org.staff.service.Impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.zeroone.star.project.DO.StaffDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.StaffSetDTO;
import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.j1.org.staff.mapper.StaffMapper;
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
@Resource
StaffMapper staffMapper;
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        long pageNo = condition.getPageIndex();
        long pageSize = condition.getPageSize();
        PageHelper.startPage((int)pageNo,(int)pageSize);
        List<StaffDO> staff = staffMapper.queryPage(condition);
        PageInfo<StaffDO> pageInfo = new PageInfo<>(staff);
        List<StaffVO> voList = staff.stream()
                .map(staffDO -> {
                    StaffVO staffVO = new StaffVO();
                    BeanUtils.copyProperties(staffDO, staffVO);
                    return staffVO;
                })
                .collect(Collectors.toList());
        // 构建 Page<StaffVO>，填充分页元数据
        Page<StaffVO> mpPage = new Page<>();
        mpPage.setCurrent(pageNo);
        mpPage.setSize(pageSize);
        mpPage.setTotal(pageInfo.getTotal());
        mpPage.setPages(pageInfo.getPages());
        mpPage.setRecords(voList);
        //  调用 PageDTO 原有 create 方法
        PageDTO<StaffVO> pageDTO = PageDTO.create(mpPage);
        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<StaffDetailsVO> queryStaff(StaffQuery condition) {
        if (condition.getId() == null) {
            return JsonVO.fail("员工ID不能为空");
        }
        StaffDO staffDO = staffMapper.queryStaff(condition);
        if (staffDO == null) {
            return JsonVO.fail("员工不存在");
        }
        StaffDetailsVO staffVO = new StaffDetailsVO();
        BeanUtils.copyProperties(staffDO, staffVO);
        return JsonVO.success(staffVO);
    }

    @Override
    public JsonVO<Long> saveStaff(StaffDTO condition) {
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
        return JsonVO.success(staffMapper.saveStaff(condition));
    }

    @Override
    public JsonVO<Long> removeStaff(List<Long> ids) {
        return  JsonVO.success(staffMapper.removeStaff(ids));
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
        Long count= staffMapper.updateStaffStatus(condition);

        if (count == 0) {
            return JsonVO.fail("更新失败：所选员工不存在或状态无需变更");
        }
        return JsonVO.success((long)count);
    }

    @Override
    public JsonVO<Long> setStaff(StaffSetDTO condition) {
        return null;
    }


}
