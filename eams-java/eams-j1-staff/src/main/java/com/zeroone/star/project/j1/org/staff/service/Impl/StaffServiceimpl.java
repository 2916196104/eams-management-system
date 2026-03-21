package com.zeroone.star.project.j1.org.staff.service.Impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.github.pagehelper.PageHelper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.j1.org.staff.mapper.StaffMapper;
import com.zeroone.star.project.j1.org.staff.service.StaffService;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import org.springframework.beans.factory.annotation.Autowired;

public class StaffServiceimpl extends ServiceImpl<StaffMapper, StaffDTO> implements StaffService {
@Autowired
StaffMapper staffMapper;
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        long pageNo = condition.getPageIndex();
        long pageSize = condition.getPageSize();
        PageHelper.startPage((int)pageNo,(int)pageSize);
              staffMapper.queryPage(condition);
        return null;
    }
}
