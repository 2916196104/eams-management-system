package com.zeroone.star.project.j4.academic;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：学员模块缴欠费与退费接口
 * </p>
 */

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

// 学员相关接口
public interface AcademicApis {
    /**
     * 分页查询缴欠费与退费记录。
     *
     * @param query 查询条件
     * @return 分页结果
     */
    JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query);

    /**
     * 办理缴欠费。
     *
     * @param financeDTO 缴费参数
     * @return 缴费结果
     */
    JsonVO<FinanceDTO> payDebt(FinanceDTO financeDTO);

    /**
     * 发起退费申请。
     *
     * @param financeDTO 退费参数
     * @return 退费申请结果
     */
    JsonVO<FinanceDTO> applyRefund(FinanceDTO financeDTO);

    /**
     * 审核退费申请。
     *
     * @param financeDTO 审核参数
     * @return 审核结果
     */
    JsonVO<FinanceDTO> auditRefund(FinanceDTO financeDTO);

    /**
     * 完成退费。
     *
     * @param financeDTO 办结参数
     * @return 办结结果
     */
    JsonVO<FinanceDTO> completeRefund(FinanceDTO financeDTO);
/**
 * 分页查询学生信息的方法
 * @param condition 学生查询条件对象，包含查询参数
 * @return JsonVO<PageDTO<StudentDTO>> 返回分页数据结果，包含学生信息的分页对象
 */
    JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition);

    //保存学生信息

    JsonVO<Long>saveStudents(StudentDTO studentDTO);
    //删除学生信息
    JsonVO<Long>deleteStudents(Long id);
    //更新学生信息
    JsonVO<Long>updateStudents(StudentDTO studentDTO);
    //根据id查询学生信息
    JsonVO<StudentDTO>queryStudents(Long id);
    //查询所有学生信息
    JsonVO<List<StudentDTO>>queryStudents();
}
