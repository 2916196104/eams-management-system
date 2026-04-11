package com.zeroone.star.project.j1.orgmanager.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.*;
import com.zeroone.star.project.j1.org.staff.StaffMangerApis;
import com.zeroone.star.project.j1.orgmanager.service.StaffService;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.LessonRecordQuery;
import com.zeroone.star.project.query.j1.org.StaffDetailQuery;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
import com.zeroone.star.project.vo.j1.org.LessonRecordVO;
import com.zeroone.star.project.vo.j1.org.StaffDetailsVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

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
@RequestMapping("org/staff")
@Api(tags="员工管理")
@Slf4j
public class StaffController implements StaffMangerApis {
    @Autowired
    private StaffService staffService;

    @ApiImplicitParams({
            @ApiImplicitParam(
                    name = "Authorization",
                    value = "认证Token（登录后获取）",
                    required = true, // 标记为必填，前端就知道必须传
                    dataType = "string",
                    paramType = "header"
            )
    })
    @GetMapping("/getpage")
    @ApiOperation("获取员工列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        return staffService.queryPage(condition);
    }
    @ApiImplicitParams({
            @ApiImplicitParam(
                    name = "Authorization",
                    value = "认证Token（登录后获取）",
                    required = true, // 标记为必填，前端就知道必须传
                    dataType = "string",
                    paramType = "header"
            )
    })
    @GetMapping("/get")
    @Override
    @ApiOperation("获取员工详情")
    public JsonVO<StaffDetailsVO> queryStaff(StaffDetailQuery condition) {
        return staffService.queryStaff(condition);
    }

    @ApiImplicitParams({
            @ApiImplicitParam(
                    name = "Authorization",
                    value = "认证Token（登录后获取）",
                    required = true, // 标记为必填，前端就知道必须传
                    dataType = "string",
                    paramType = "header"
            )
    })
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
    @ApiOperation("转出机构（支持批量）")
    @PostMapping("/transfer")
    public JsonVO<Long> batchTransferOrg(@RequestBody AdminTransferOrgDTO dto) {
        return staffService.batchTransferOrg(dto);
    }

    @Override
    @ApiOperation("修改密码")
    @PutMapping("/reset-password")
    public JsonVO<Long> resetPassword(@RequestBody ResetPasswordDTO resetPasswordDTO) {
        return staffService.resetPassword(resetPasswordDTO);
    }
    @Override
    @ApiOperation("导出数据")
    @GetMapping("/export")
    public ResponseEntity<byte[]> exportStaffExcel(StaffQuery query) {
        return staffService.exportStaffExcel(query);
    }
    @Override
    @PutMapping("/avatar/url")
    @ApiOperation("修改头像")
    public JsonVO<Long> updateStaffAvatarByUrl(@RequestBody AdminUpdateStaffAvatarDTO dto) {
        return staffService.updateStaffAvatarByUrl(dto);
    }
    @Override
    @ApiImplicitParams({
            @ApiImplicitParam(
                    name = "Authorization",
                    value = "认证Token（登录后获取）",
                    required = true,
                    dataType = "string",
                    paramType = "header"
            )
    })
    @ApiOperation(value = "获取授课记录（条件+分页）", notes = "在员工详情页展示，需传入staffId")
    @GetMapping("/lesson")
    public JsonVO<PageDTO<LessonRecordVO>> pageQueryLessonRecord(@Valid LessonRecordQuery query) {
        return staffService.getLessonRecord(query);
    }

    @Override
    @ApiImplicitParams({
            @ApiImplicitParam(
                    name = "Authorization",
                    value = "认证Token（登录后获取）",
                    required = true,
                    dataType = "string",
                    paramType = "header"
            )
    })
    @ApiOperation(value = "获取带班记录（条件+分页）", notes = "在员工详情页展示，需传入staffId")
    @GetMapping("/class")
    public JsonVO<PageDTO<ClassRecordVO>> pageQueryClassRecord(@Valid ClassRecordQuery query) {
        return staffService.getClassRecord(query);
    }
}
