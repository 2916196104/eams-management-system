package com.zeroone.star.project.j1.org.staff;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j1.org.ResetPasswordDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.StaffSetDTO;
import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.query.j1.org.TeachRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import com.zeroone.star.project.vo.j1.org.TeachRecordVO;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

/**
 * <p>
 * 描述：员工查询操作相关接口
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c chichu
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
    JsonVO<StaffDetailsVO> queryStaff(StaffQuery condition);
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
    JsonVO<Long> removeStaff(List<Long> ids);
    /**
     *设置员工
     * @param condition
     * @return 员工信息
     **/
    JsonVO<Long> setStaff(StaffSetDTO condition);
    /**
     *修改员工状态员工
     * @param condition
     * @return 员工信息
     **/
    JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition);
    /**
     * 批量转出员工机构
     * @param staffIds 员工ID集合
     * @param orgId 目标机构ID
     * @return 操作结果
     **/
    JsonVO<List<Long>> transferStaffOrg(List<Long> staffIds, Long orgId);

    /**
     * 重置员工密码
     * @param dto 重置参数
     * @return 结果
     **/
    JsonVO<Boolean> resetStaffPassword(ResetPasswordDTO dto);

    /**
     * 导出员工列表
     * @param condition 查询条件
     * @return 导出结果
     **/
    JsonVO<Void> exportStaffList(StaffQuery condition);

    /**
     * 修改员工头像
     * @param staffId 员工ID
     * @param file 头像文件
     * @return 头像地址
     **/
    JsonVO<String> updateStaffAvatar(Long staffId, MultipartFile file);

    /**
     * 获取授课记录
     * @param query 查询条件
     * @return 记录列表
     **/
    JsonVO<PageDTO<TeachRecordVO>> getTeachRecord(TeachRecordQuery query);

    /**
     * 获取带班记录
     * @param query 查询条件
     * @return 记录列表
     **/
    JsonVO<PageDTO<ClassRecordVO>> getClassRecord(ClassRecordQuery query);
}
