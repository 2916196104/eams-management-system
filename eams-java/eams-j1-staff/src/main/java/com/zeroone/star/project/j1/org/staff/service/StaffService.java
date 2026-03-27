package com.zeroone.star.project.j1.org.staff.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.Staff;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.StaffSetDTO;
import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;

import java.util.List;


public interface StaffService extends IService<Staff> {
    JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition);

    JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition);

    JsonVO<Long> saveStaff(StaffDTO condition);

    JsonVO<Long> removeStaff(List<Long> ids);

    JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition);


    JsonVO<Long> setStaff(StaffSetDTO condition);
}
