package com.zeroone.star.project.j1.org.staff.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.StaffDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import org.springframework.stereotype.Service;


public interface StaffService extends IService<StaffDO> {
    JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition);

    JsonVO<StaffDetailsVO> queryStaff(StaffQuery condition);

    JsonVO<Long> saveStaff(StaffDTO condition);
}
