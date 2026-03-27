package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.student.entity.FinanceRecord;
import com.zeroone.star.student.entity.Refund;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.entity.StudentCourse;
import com.zeroone.star.student.mapper.FinanceRecordMapper;
import com.zeroone.star.student.mapper.RefundMapper;
import com.zeroone.star.student.mapper.StudentCourseMapper;
import com.zeroone.star.student.mapper.StudentFinanceMapper;
import com.zeroone.star.student.mapper.StudentMapper;
import com.zeroone.star.student.service.IStudentFinanceService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：学员财务服务实现
 * </p>
 */
@Service
public class StudentFinanceServiceImpl implements IStudentFinanceService {
    private static final int TYPE_PAYMENT = 1;
    private static final int TYPE_REFUND = 2;
    private static final int REFUND_STATE_APPLIED = 1;
    private static final int REFUND_STATE_APPROVED = 2;
    private static final int REFUND_STATE_REJECTED = 3;
    private static final int REFUND_STATE_COMPLETED = 4;

    @Resource
    private StudentFinanceMapper studentFinanceMapper;

    @Resource
    private FinanceRecordMapper financeRecordMapper;

    @Resource
    private RefundMapper refundMapper;

    @Resource
    private StudentCourseMapper studentCourseMapper;

    @Resource
    private StudentMapper studentMapper;

    @Override
    public PageDTO<FinanceDTO> queryFinancePage(FinanceQuery query) {
        FinanceQuery actualQuery = query == null ? new FinanceQuery() : query;
        long pageIndex = actualQuery.getPageIndex() > 0 ? actualQuery.getPageIndex() : 1L;
        long pageSize = actualQuery.getPageSize() > 0 ? actualQuery.getPageSize() : 10L;
        Page<FinanceDTO> page = new Page<>(pageIndex, pageSize);
        Page<FinanceDTO> result = studentFinanceMapper.selectFinancePage(page, actualQuery);
        return PageDTO.create(result);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public FinanceDTO payDebt(FinanceDTO financeDTO) {
        validateFinanceDTO(financeDTO, "缴费参数不能为空");
        if (financeDTO.getStudentCourseId() == null) {
            throw new IllegalArgumentException("[studentCourseId]签约记录ID不能为空");
        }
        if (financeDTO.getAmount() == null || financeDTO.getAmount().compareTo(BigDecimal.ZERO) <= 0) {
            throw new IllegalArgumentException("[amount]缴费金额必须大于0");
        }

        StudentCourse studentCourse = requireStudentCourse(financeDTO.getStudentCourseId());
        Student student = requireStudent(studentCourse.getStudentId());
        validateStudentMatch(financeDTO.getStudentId(), student.getId());

        BigDecimal amount = financeDTO.getAmount().abs();
        FinanceRecord financeRecord = new FinanceRecord();
        financeRecord.setTitle(defaultText(financeDTO.getTitle(), "学员补缴费用"));
        financeRecord.setAmount(amount);
        financeRecord.setItemType(TYPE_PAYMENT);
        financeRecord.setItemId(studentCourse.getId());
        financeRecord.setOperator(financeDTO.getOperator());
        financeRecord.setPayer(financeDTO.getPayer() != null ? financeDTO.getPayer() : student.getId());
        financeRecord.setRemark(financeDTO.getRemark());
        financeRecord.setAddTime(LocalDateTime.now());
        financeRecord.setVerifyState(REFUND_STATE_COMPLETED);
        financeRecord.setVerifyStaff(financeDTO.getOperator());
        financeRecord.setVerifyTime(LocalDateTime.now());
        financeRecordMapper.insert(financeRecord);

        studentCourse.setPaidAmount(defaultZero(studentCourse.getPaidAmount()).add(amount));
        if (financeDTO.getOperator() != null) {
            studentCourse.setOperator(financeDTO.getOperator());
        }
        refreshPayStatus(studentCourse);
        studentCourseMapper.updateById(studentCourse);
        return buildPaymentDTO(financeRecord, studentCourse, student);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public FinanceDTO applyRefund(FinanceDTO financeDTO) {
        validateFinanceDTO(financeDTO, "退费参数不能为空");
        if (financeDTO.getStudentCourseId() == null) {
            throw new IllegalArgumentException("[studentCourseId]签约记录ID不能为空");
        }
        if (financeDTO.getAmount() == null || financeDTO.getAmount().compareTo(BigDecimal.ZERO) == 0) {
            throw new IllegalArgumentException("[amount]退费金额不能为空且不能为0");
        }
        if (financeDTO.getRefundLessonCount() != null && financeDTO.getRefundLessonCount() < 0) {
            throw new IllegalArgumentException("[refundLessonCount]退费课时不能小于0");
        }

        StudentCourse studentCourse = requireStudentCourse(financeDTO.getStudentCourseId());
        Student student = requireStudent(studentCourse.getStudentId());
        validateStudentMatch(financeDTO.getStudentId(), student.getId());

        BigDecimal refundAmount = financeDTO.getAmount().abs().negate();
        if (defaultZero(studentCourse.getPaidAmount()).add(refundAmount).compareTo(BigDecimal.ZERO) < 0) {
            throw new IllegalArgumentException("[amount]退费金额不能大于当前实付金额");
        }

        Refund refund = new Refund();
        refund.setStudentId(student.getId());
        refund.setStudentCourseId(studentCourse.getId());
        refund.setOperator(financeDTO.getOperator());
        refund.setRefundAmount(refundAmount);
        refund.setRefundLessonCount(defaultInteger(financeDTO.getRefundLessonCount()));
        refund.setApplyTime(LocalDateTime.now());
        refund.setRemark(financeDTO.getRemark());
        refund.setTypeNum(TYPE_REFUND);
        refund.setVerifyState(REFUND_STATE_APPLIED);
        refundMapper.insert(refund);
        return buildRefundDTO(refund, studentCourse, student);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public FinanceDTO auditRefund(FinanceDTO financeDTO) {
        validateFinanceDTO(financeDTO, "审核参数不能为空");
        if (financeDTO.getId() == null) {
            throw new IllegalArgumentException("[id]退费单ID不能为空");
        }
        if (financeDTO.getVerifyState() == null ||
                (financeDTO.getVerifyState() != REFUND_STATE_APPROVED && financeDTO.getVerifyState() != REFUND_STATE_REJECTED)) {
            throw new IllegalArgumentException("[verifyState]审核状态仅支持2(通过)或3(驳回)");
        }

        Refund refund = requireRefund(financeDTO.getId());
        if (refund.getDoneTime() != null || Integer.valueOf(REFUND_STATE_COMPLETED).equals(refund.getVerifyState())) {
            throw new IllegalArgumentException("当前退费单已办结，不能重复审核");
        }

        refund.setVerifyState(financeDTO.getVerifyState());
        refund.setVerifyStaff(financeDTO.getVerifyStaff() != null ? financeDTO.getVerifyStaff() : financeDTO.getOperator());
        refund.setVerifyTime(LocalDateTime.now());
        if (StringUtils.hasText(financeDTO.getRemark())) {
            refund.setRemark(financeDTO.getRemark());
        }
        refundMapper.updateById(refund);

        StudentCourse studentCourse = requireStudentCourse(refund.getStudentCourseId());
        Student student = requireStudent(refund.getStudentId());
        return buildRefundDTO(refund, studentCourse, student);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public FinanceDTO completeRefund(FinanceDTO financeDTO) {
        validateFinanceDTO(financeDTO, "办结参数不能为空");
        if (financeDTO.getId() == null) {
            throw new IllegalArgumentException("[id]退费单ID不能为空");
        }

        Refund refund = requireRefund(financeDTO.getId());
        if (!Integer.valueOf(REFUND_STATE_APPROVED).equals(refund.getVerifyState())) {
            throw new IllegalArgumentException("当前退费单未审核通过，不能办理完成");
        }
        if (refund.getDoneTime() != null || Integer.valueOf(REFUND_STATE_COMPLETED).equals(refund.getVerifyState())) {
            throw new IllegalArgumentException("当前退费单已完成，无需重复办理");
        }

        StudentCourse studentCourse = requireStudentCourse(refund.getStudentCourseId());
        Student student = requireStudent(refund.getStudentId());
        BigDecimal newPaidAmount = defaultZero(studentCourse.getPaidAmount()).add(defaultZero(refund.getRefundAmount()));
        if (newPaidAmount.compareTo(BigDecimal.ZERO) < 0) {
            throw new IllegalArgumentException("退费后实付金额不能小于0");
        }

        LocalDateTime now = LocalDateTime.now();
        FinanceRecord financeRecord = new FinanceRecord();
        financeRecord.setTitle(defaultText(financeDTO.getTitle(), "线下退费完成"));
        financeRecord.setAmount(defaultZero(refund.getRefundAmount()));
        financeRecord.setItemType(TYPE_REFUND);
        financeRecord.setItemId(studentCourse.getId());
        financeRecord.setOperator(financeDTO.getOperator() != null ? financeDTO.getOperator() : refund.getOperator());
        financeRecord.setPayer(student.getId());
        financeRecord.setRemark(defaultText(financeDTO.getRemark(), refund.getRemark()));
        financeRecord.setAddTime(now);
        financeRecord.setVerifyState(REFUND_STATE_COMPLETED);
        financeRecord.setVerifyStaff(refund.getVerifyStaff());
        financeRecord.setVerifyTime(now);
        financeRecordMapper.insert(financeRecord);

        studentCourse.setPaidAmount(newPaidAmount);
        studentCourse.setCountLessonRefund(defaultInteger(studentCourse.getCountLessonRefund()) + defaultInteger(refund.getRefundLessonCount()));
        if (financeDTO.getOperator() != null) {
            studentCourse.setOperator(financeDTO.getOperator());
        }
        refreshPayStatus(studentCourse);
        studentCourseMapper.updateById(studentCourse);

        if (financeDTO.getOperator() != null) {
            refund.setOperator(financeDTO.getOperator());
        }
        refund.setDoneTime(now);
        refund.setVerifyState(REFUND_STATE_COMPLETED);
        refundMapper.updateById(refund);
        return buildRefundDTO(refund, studentCourse, student);
    }

    private void validateFinanceDTO(FinanceDTO financeDTO, String message) {
        if (financeDTO == null) {
            throw new IllegalArgumentException(message);
        }
    }

    private void validateStudentMatch(Long requestStudentId, Long actualStudentId) {
        if (requestStudentId != null && !requestStudentId.equals(actualStudentId)) {
            throw new IllegalArgumentException("[studentId]学员ID与签约记录不匹配");
        }
    }

    private StudentCourse requireStudentCourse(Long studentCourseId) {
        StudentCourse studentCourse = studentCourseMapper.selectById(studentCourseId);
        if (studentCourse == null || Integer.valueOf(1).equals(studentCourse.getDeleted())) {
            throw new IllegalArgumentException("签约记录不存在或已删除");
        }
        return studentCourse;
    }

    private Student requireStudent(Long studentId) {
//        Student student = studentMapper.selectById(studentId);
//        if (student == null || Integer.valueOf(1).equals(student.getDeleted())) {
//            throw new IllegalArgumentException("学员不存在或已删除");
//        }
//        return student;
        //我这里不知道为啥报错，组长看到不要整合，你们那边可以通过就行
        return null;
    }

    private Refund requireRefund(Long refundId) {
        Refund refund = refundMapper.selectById(refundId);
        if (refund == null) {
            throw new IllegalArgumentException("退费单不存在");
        }
        return refund;
    }

    private void refreshPayStatus(StudentCourse studentCourse) {
        BigDecimal contractAmount = defaultZero(studentCourse.getAmount());
        BigDecimal paidAmount = defaultZero(studentCourse.getPaidAmount());
        studentCourse.setPayOff(paidAmount.compareTo(contractAmount) >= 0 ? true : false);
    }

    private FinanceDTO buildPaymentDTO(FinanceRecord financeRecord, StudentCourse studentCourse, Student student) {
        FinanceDTO financeDTO = buildBaseDTO(studentCourse, student);
        financeDTO.setId(financeRecord.getId());
        financeDTO.setType(TYPE_PAYMENT);
        financeDTO.setTitle(financeRecord.getTitle());
        financeDTO.setAmount(financeRecord.getAmount());
        financeDTO.setOperator(financeRecord.getOperator());
        financeDTO.setPayer(financeRecord.getPayer());
        financeDTO.setRemark(financeRecord.getRemark());
        financeDTO.setVerifyState(financeRecord.getVerifyState());
        financeDTO.setVerifyStaff(financeRecord.getVerifyStaff());
        financeDTO.setVerifyTime(financeRecord.getVerifyTime());
        financeDTO.setOperateTime(financeRecord.getAddTime());
        return financeDTO;
    }

    private FinanceDTO buildRefundDTO(Refund refund, StudentCourse studentCourse, Student student) {
        FinanceDTO financeDTO = buildBaseDTO(studentCourse, student);
        financeDTO.setId(refund.getId());
        financeDTO.setType(TYPE_REFUND);
        financeDTO.setTitle("线下退费");
        financeDTO.setAmount(refund.getRefundAmount());
        financeDTO.setOperator(refund.getOperator());
        financeDTO.setPayer(student.getId());
        financeDTO.setRemark(refund.getRemark());
        financeDTO.setVerifyState(refund.getVerifyState());
        financeDTO.setVerifyStaff(refund.getVerifyStaff());
        financeDTO.setVerifyTime(refund.getVerifyTime());
        financeDTO.setRefundLessonCount(refund.getRefundLessonCount());
        financeDTO.setApplyTime(refund.getApplyTime());
        financeDTO.setDoneTime(refund.getDoneTime());
        financeDTO.setOperateTime(refund.getDoneTime() != null ? refund.getDoneTime() : refund.getApplyTime());
        return financeDTO;
    }

    private FinanceDTO buildBaseDTO(StudentCourse studentCourse, Student student) {
        FinanceDTO financeDTO = new FinanceDTO();
        financeDTO.setStudentId(student.getId());
        financeDTO.setStudentName(student.getName());
        financeDTO.setStudentCourseId(studentCourse.getId());
        financeDTO.setContractAmount(defaultZero(studentCourse.getAmount()));
        financeDTO.setPaidAmount(defaultZero(studentCourse.getPaidAmount()));
        financeDTO.setUnpaidAmount(defaultZero(studentCourse.getAmount()).subtract(defaultZero(studentCourse.getPaidAmount())));
        financeDTO.setPayOff(studentCourse.getPayOff());
        return financeDTO;
    }

    private BigDecimal defaultZero(BigDecimal value) {
        return value == null ? BigDecimal.ZERO : value;
    }

    private Integer defaultInteger(Integer value) {
        return value == null ? 0 : value;
    }

    private String defaultText(String value, String defaultValue) {
        return StringUtils.hasText(value) ? value : defaultValue;
    }
}
