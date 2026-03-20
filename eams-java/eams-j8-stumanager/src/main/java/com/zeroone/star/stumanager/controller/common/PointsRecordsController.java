package com.zeroone.star.stumanager.controller.common;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.AdjustPointsDTO;
import com.zeroone.star.project.j8.stumanager.common.PointsRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.common.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.PointsRecordVO;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.StudentCreditLog;
import com.zeroone.star.stumanager.service.IStaffService;
import com.zeroone.star.stumanager.service.IStudentCreditLogService;
import com.zeroone.star.stumanager.service.IStudentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.Objects;
import java.util.Optional;

/**
 * 积分记录
 */
@RestController
@Validated
@RequestMapping("/stu/common/points-records")
@Api(tags = "共用接口-积分记录")
public class PointsRecordsController implements PointsRecordsApis {
    @Resource
    private IStudentCreditLogService studentCreditLogService;

    @Resource
    private IStudentService studentService;

    @Resource
    private IStaffService staffService;

    @ApiOperation("获取积分记录")
    @GetMapping("/query-points-records")
    @Override
    public JsonVO<PageDTO<PointsRecordVO>> queryPointsRecords(@Validated PointsRecordQuery query) {
        Page<StudentCreditLog> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentCreditLog> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentCreditLog::getStudentId, query.getStudentId());
        wrapper.eq(Objects.nonNull(query.getChangeType()), StudentCreditLog::getChangeType, query.getChangeType());
        wrapper.ge(Objects.nonNull(query.getBeginTime()), StudentCreditLog::getAddTime, query.getBeginTime());
        wrapper.le(Objects.nonNull(query.getEndTime()), StudentCreditLog::getAddTime, query.getEndTime());
        wrapper.orderByDesc(StudentCreditLog::getAddTime, StudentCreditLog::getId);
        Page<StudentCreditLog> result = studentCreditLogService.page(page, wrapper);
        return JsonVO.success(PageDTO.create(result, this::toPointsRecordVO));
    }

    @ApiOperation("调整积分")
    @PostMapping("/adjust-points")
    @Transactional(rollbackFor = Exception.class)
    @Override
    public JsonVO<Boolean> adjustPoints(@Validated @RequestBody AdjustPointsDTO dto) {
        if (dto.getChangeCredit() == 0) {
            return JsonVO.fail("change credit cannot be 0");
        }

        Student student = studentService.getById(dto.getStudentId());
        if (Objects.isNull(student)) {
            return JsonVO.fail("student not found");
        }

        int currentCredit = Optional.ofNullable(student.getCredit()).orElse(0);
        int newCredit = currentCredit + dto.getChangeCredit();
        if (newCredit < 0) {
            return JsonVO.fail("credit after adjustment cannot be negative");
        }

        student.setCredit(newCredit);
        student.setEditTime(LocalDateTime.now());
        boolean updated = studentService.updateById(student);
        if (!updated) {
            return JsonVO.fail("adjust points failed");
        }

        StudentCreditLog log = new StudentCreditLog();
        log.setStudentId(student.getId());
        log.setUserId(student.getUserId());
        log.setCredit(dto.getChangeCredit());
        log.setCurrentCredit(newCredit);
        log.setChangeType(1);
        log.setAddTime(LocalDateTime.now());
        log.setRemark(dto.getRemark());
        log.setSchoolId(student.getSchoolId());
        boolean saved = studentCreditLogService.save(log);
        if (!saved) {
            throw new IllegalStateException("save points log failed");
        }

        return JsonVO.success(Boolean.TRUE);
    }

    private PointsRecordVO toPointsRecordVO(StudentCreditLog log) {
        PointsRecordVO vo = new PointsRecordVO();
        vo.setId(log.getId());
        vo.setStudentId(log.getStudentId());
        vo.setCredit(log.getCredit());
        vo.setCurrentCredit(log.getCurrentCredit());
        vo.setChangeType(log.getChangeType());
        vo.setSourceId(log.getSourceId());
        vo.setStaffId(log.getStaffId());
        vo.setAddTime(log.getAddTime());
        vo.setRemark(log.getRemark());
        Student student = studentService.getById(log.getStudentId());
        if (Objects.nonNull(student)) {
            vo.setStudentName(student.getName());
        }
        if (Objects.nonNull(log.getStaffId())) {
            Staff staff = staffService.getById(log.getStaffId());
            if (Objects.nonNull(staff)) {
                vo.setStaffName(staff.getName());
            }
        }
        return vo;
    }
}
