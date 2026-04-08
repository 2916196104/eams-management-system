package com.zeroone.star.project.j1.orgmanager.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.Staff;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.*;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.LessonRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
import com.zeroone.star.project.vo.j1.org.LessonRecordVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import org.springframework.http.ResponseEntity;

import java.util.List;


public interface StaffService extends IService<Staff> {
    JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition);

    JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition);

    JsonVO<Long> saveStaff(StaffDTO condition);

    JsonVO<Long> removeStaff(List<Long> ids);

    JsonVO<Long> updateStaffStatus(StaffUpdateDTO condition);


    JsonVO<Long> setStaff(StaffSetDTO condition);

    /**
     * 批量转出员工机构
     * @param dto 转出机构请求参数
     * @return 操作结果
     */
    JsonVO<Long> batchTransferOrg(AdminTransferOrgDTO dto);
    /**
     * 重置员工密码
     * @param resetPasswordDTO 重置密码参数
     * @return 操作结果
     */
    JsonVO<Long> resetPassword(ResetPasswordDTO resetPasswordDTO);
    /**
     * 导出员工数据
     */
    // 导出用：获取导出列表
    ResponseEntity<byte[]> exportStaffExcel(StaffQuery query);
    /**
     * 修改员工头像（URL方式）
     * @param dto 头像修改DTO
     * @throws Exception 业务异常
     */
    JsonVO<Long> updateStaffAvatarByUrl(AdminUpdateStaffAvatarDTO dto);


    JsonVO<PageDTO<LessonRecordVO>> getLessonRecord(LessonRecordQuery condition);

    JsonVO<PageDTO<ClassRecordVO>> getClassRecord(ClassRecordQuery condition);

}
