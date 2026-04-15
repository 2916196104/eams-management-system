package com.zeroone.star.project.j1.org.staff;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j1.org.*;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.LessonRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
//import com.zeroone.star.project.query.j1.org.TeachRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
import com.zeroone.star.project.vo.j1.org.LessonRecordVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
//import com.zeroone.star.project.vo.j1.org.TeachRecordVO;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
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
    JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition);
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
     * 管理员批量转出员工机构
     * @param dto 转出机构请求参数（员工ID列表、目标机构ID）
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
     * 导出员工信息到Excel
     * @param query 查询条件
     */

    ResponseEntity<byte[]> exportStaffExcel(StaffQuery query);
    /**
     * 修改员工头像（URL方式，适配已有文件URL场景）
     * @param dto 头像修改DTO
     * @return 操作结果
     */

    JsonVO<Long> updateStaffAvatarByUrl(AdminUpdateStaffAvatarDTO dto);


    JsonVO<PageDTO<LessonRecordVO>> pageQueryLessonRecord(LessonRecordQuery query);


    JsonVO<PageDTO<ClassRecordVO>> pageQueryClassRecord(ClassRecordQuery query);

}
