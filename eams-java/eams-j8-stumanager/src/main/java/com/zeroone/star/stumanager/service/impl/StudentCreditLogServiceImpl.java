package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.AdjustPointsDTO;
import com.zeroone.star.project.query.j8.stumanager.common.PointsRecordQuery;
import com.zeroone.star.project.vo.j8.stumanager.common.PointsRecordVO;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.StudentCreditLog;
import com.zeroone.star.stumanager.mapper.StudentCreditLogMapper;
import com.zeroone.star.stumanager.service.IStaffService;
import com.zeroone.star.stumanager.service.IStudentCreditLogService;
import com.zeroone.star.stumanager.service.IStudentService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;
/**
 * <p>
 * 学生积分变动记录 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentCreditLogServiceImpl extends ServiceImpl<StudentCreditLogMapper, StudentCreditLog> implements IStudentCreditLogService {

    @Resource
    private IStudentService studentService;

    @Resource
    private IStaffService staffService;

    @Override
    public PageDTO<PointsRecordVO> queryPointsRecords(PointsRecordQuery query) {
        validateTimeRange(query.getBeginTime(), query.getEndTime());

        Page<StudentCreditLog> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentCreditLog> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentCreditLog::getStudentId, query.getStudentId());
        wrapper.eq(Objects.nonNull(query.getChangeType()), StudentCreditLog::getChangeType, query.getChangeType());
        wrapper.ge(Objects.nonNull(query.getBeginTime()), StudentCreditLog::getAddTime, query.getBeginTime());
        wrapper.le(Objects.nonNull(query.getEndTime()), StudentCreditLog::getAddTime, query.getEndTime());
        wrapper.orderByDesc(StudentCreditLog::getAddTime, StudentCreditLog::getId);

        Page<StudentCreditLog> result = page(page, wrapper);
        return buildPageDTO(result, buildRows(result.getRecords()));
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean adjustPoints(AdjustPointsDTO dto) {
        Integer changeCredit = dto.getChangeCredit();
        if (Objects.isNull(changeCredit) || changeCredit == 0) {
            throw new IllegalArgumentException("changeCredit cannot be 0");
        }

        Student student = studentService.getById(dto.getStudentId());
        if (Objects.isNull(student)) {
            throw new IllegalArgumentException("student not found");
        }

        LocalDateTime now = LocalDateTime.now();
        LambdaUpdateWrapper<Student> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.eq(Student::getId, dto.getStudentId());
        updateWrapper.setSql("credit = IFNULL(credit, 0) + (" + changeCredit + ")");
        updateWrapper.set(Student::getEditTime, now);
        if (changeCredit < 0) {
            updateWrapper.apply("IFNULL(credit, 0) + {0} >= 0", changeCredit);
        }

        boolean updated = studentService.update(updateWrapper);
        if (!updated) {
            if (changeCredit < 0) {
                throw new IllegalArgumentException("insufficient credit");
            }
            throw new IllegalStateException("failed to update student credit");
        }

        Student refreshedStudent = studentService.getById(dto.getStudentId());
        if (Objects.isNull(refreshedStudent)) {
            throw new IllegalStateException("student missing after credit update");
        }

        StudentCreditLog log = new StudentCreditLog();
        log.setStudentId(student.getId());
        log.setUserId(student.getUserId());
        log.setCredit(changeCredit);
        log.setCurrentCredit(defaultZero(refreshedStudent.getCredit()));
        log.setChangeType(changeCredit > 0 ? 1 : 2);
        log.setAddTime(now);
        log.setRemark(dto.getRemark());
        log.setSchoolId(student.getSchoolId());
        if (!save(log)) {
            throw new IllegalStateException("failed to save credit log");
        }
        return true;
    }

    private List<PointsRecordVO> buildRows(List<StudentCreditLog> records) {
        if (Objects.isNull(records) || records.isEmpty()) {
            return Collections.emptyList();
        }

        Map<Long, Student> studentMap = toStudentMap(collectIds(records, StudentCreditLog::getStudentId));
        Map<Long, Staff> staffMap = toStaffMap(collectIds(records, StudentCreditLog::getStaffId));

        return records.stream().map(record -> {
            PointsRecordVO vo = new PointsRecordVO();
            vo.setId(record.getId());
            vo.setStudentId(record.getStudentId());
            vo.setCredit(record.getCredit());
            vo.setCurrentCredit(record.getCurrentCredit());
            vo.setChangeType(record.getChangeType());
            vo.setSourceId(record.getSourceId());
            vo.setStaffId(record.getStaffId());
            vo.setAddTime(record.getAddTime());
            vo.setRemark(record.getRemark());

            Student student = studentMap.get(record.getStudentId());
            if (Objects.nonNull(student)) {
                vo.setStudentName(student.getName());
            }

            Staff staff = staffMap.get(record.getStaffId());
            if (Objects.nonNull(staff)) {
                vo.setStaffName(staff.getName());
            }
            return vo;
        }).collect(Collectors.toList());
    }

    private Map<Long, Student> toStudentMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return studentService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Student::getId, Function.identity(), (left, right) -> left));
    }

    private Map<Long, Staff> toStaffMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return staffService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Staff::getId, Function.identity(), (left, right) -> left));
    }

    private <T> Set<Long> collectIds(List<T> list, Function<T, Long> getter) {
        return list.stream()
                .map(getter)
                .filter(Objects::nonNull)
                .collect(Collectors.toCollection(LinkedHashSet::new));
    }

    private <T> PageDTO<T> buildPageDTO(Page<?> page, List<T> rows) {
        PageDTO<T> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(page.getCurrent());
        pageDTO.setPageSize(page.getSize());
        pageDTO.setTotal(page.getTotal());
        pageDTO.setPages(page.getPages());
        pageDTO.setRows(rows);
        return pageDTO;
    }

    private void validateTimeRange(LocalDateTime beginTime, LocalDateTime endTime) {
        if (Objects.nonNull(beginTime) && Objects.nonNull(endTime) && beginTime.isAfter(endTime)) {
            throw new IllegalArgumentException("beginTime cannot be after endTime");
        }
    }

    private int defaultZero(Integer value) {
        return Objects.isNull(value) ? 0 : value;
    }
}
