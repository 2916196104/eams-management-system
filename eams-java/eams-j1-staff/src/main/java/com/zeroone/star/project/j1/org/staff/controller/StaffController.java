package com.zeroone.star.project.j1.org.staff.controller;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.*;
import com.zeroone.star.project.j1.org.staff.StaffMangerApis;
import com.zeroone.star.project.j1.org.staff.service.StaffService;
import com.zeroone.star.project.query.j1.org.LessonRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
//import com.zeroone.star.project.query.j1.org.TeachRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j1.org.LessonRecordVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
//import com.zeroone.star.project.vo.j1.org.TeachRecordVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
//import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import java.util.List;
//import java.util.Collections;

/**
 * <p>
 * 描述：员工操作controller层
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c chichu
 * @version 1.0.0
 */
@RestController()
@RequestMapping("j1/staff")
@Api(tags="员工管理")
@Slf4j
public class StaffController implements StaffMangerApis {
    @Autowired
    private StaffService staffService;
    @GetMapping("/getpage")
    @ApiOperation("获取员工列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        return staffService.queryPage(condition);
    }
    @GetMapping("/get")
    @Override
    @ApiOperation("获取员工详情")
    public JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition) {
        return staffService.queryStaff(condition);
    }
       @PostMapping("/save")
    @Override
    @ApiOperation("保存员工")
    public JsonVO<Long> saveStaff(@RequestBody  StaffDTO condition) {

        return  staffService.saveStaff(condition);
    }
@DeleteMapping("/delete")
    @Override
    @ApiOperation("删除员工（支持批量）")
    public JsonVO<Long> removeStaff(@RequestBody List<Long> ids) {
        return  staffService.removeStaff(ids);
    }

@PostMapping("/set")
    @Override
    @ApiOperation("设置角色（支持批量）")
    public JsonVO<Long> setStaff(@RequestBody StaffSetDTO condition) {
        return staffService.setStaff(condition);
    }

    @PostMapping("/update")
    @Override
    @ApiOperation("在职状态（支持批量）")
    public JsonVO<Long> updateStaffStatus(@RequestBody StaffUpdateDTO condition) {
        return staffService.updateStaffStatus(condition);
    }


    @Override
    public JsonVO<Void> batchTransferOrg(@Valid @RequestBody AdminTransferOrgDTO dto) {
        return staffService.batchTransferOrg(dto);
    }

    @Override
    public JsonVO<Void> resetPassword(@Valid ResetPasswordDTO resetPasswordDTO) {
        return staffService.resetPassword(resetPasswordDTO);
    }
    @Override
    public ResponseEntity<byte[]> exportStaffExcel(StaffQuery query) {
        return staffService.exportStaffExcel(query);
    }
    @Override
    public JsonVO<Void> updateStaffAvatarByUrl(@Valid @RequestBody AdminUpdateStaffAvatarDTO dto) {
        try {
            staffService.updateStaffAvatarByUrl(dto);
            return JsonVO.success(null);
        } catch (Exception e) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
        }
    }
    @Override
    public JsonVO<PageDTO<LessonRecordVO>> pageQueryLessonRecord(LessonRecordQuery query) {
        return staffService.getLessonRecord(query);
    }
    @Override
    public JsonVO<PageDTO<ClassRecordVO>> pageQueryClassRecord(ClassRecordQuery query) {
        return staffService.getClassRecord(query);
    }
}
