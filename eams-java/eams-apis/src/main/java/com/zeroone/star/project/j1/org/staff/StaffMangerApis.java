package com.zeroone.star.project.j1.org.staff;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;

import java.util.List;

/**
 * <p>
 * 描述：员工查询操作相关接口
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c
 * @version 1.0.0
 */
public interface StaffMangerApis {
    /**
    *分页查询员工信息
     * @param condition
     * @return 员工信息
     **/
    JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition);
    /**
     *获取员工详情
     * @param condition
     * @return 员工信息
     **/
    JsonVO<StaffVO> queryStaff(StaffQuery condition);
    /**
     *保存员工
     * @param condition
     * @return 员工信息
     **/
    JsonVO<Long> saveStaff(StaffDTO condition);
    /**
     *删除员工
     * @param ids
     * @return 员工信息
     **/
    JsonVO<List<Long>> removeStaff(List<Long> ids);
    /**
     *设置员工
     * @param ids
     * @return 员工信息
     **/
    JsonVO<List<Long>> setStaff(List<Long> ids);
    /**
     *修改员工状态员工
     * @param ids
     * @return 员工信息
     **/
    JsonVO<List<Long>> updateStaffStatus(List<Long> ids);

}
