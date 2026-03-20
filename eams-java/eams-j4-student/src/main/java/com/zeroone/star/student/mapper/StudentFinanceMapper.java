package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 描述：学员财务聚合查询接口
 * </p>
 */
@Mapper
public interface StudentFinanceMapper {
    @Select({
            "<script>",
            "SELECT * FROM (",
            "  SELECT fr.id AS id,",
            "         1 AS type,",
            "         sc.student_id AS studentId,",
            "         s.name AS studentName,",
            "         sc.id AS studentCourseId,",
            "         fr.title AS title,",
            "         fr.amount AS amount,",
            "         sc.amount AS contractAmount,",
            "         sc.paid_amount AS paidAmount,",
            "         IFNULL(sc.amount, 0) - IFNULL(sc.paid_amount, 0) AS unpaidAmount,",
            "         sc.pay_off AS payOff,",
            "         fr.operator AS operator,",
            "         fr.payer AS payer,",
            "         fr.remark AS remark,",
            "         fr.verify_state AS verifyState,",
            "         fr.verify_staff AS verifyStaff,",
            "         fr.verify_time AS verifyTime,",
            "         NULL AS refundLessonCount,",
            "         NULL AS applyTime,",
            "         NULL AS doneTime,",
            "         fr.add_time AS operateTime",
            "    FROM finance_record fr",
            "    LEFT JOIN student_course sc ON sc.id = fr.item_id",
            "    LEFT JOIN student s ON s.id = sc.student_id",
            "   WHERE fr.amount &gt;= 0",
            "  UNION ALL",
            "  SELECT r.id AS id,",
            "         2 AS type,",
            "         r.student_id AS studentId,",
            "         s.name AS studentName,",
            "         r.student_course_id AS studentCourseId,",
            "         '线下退费' AS title,",
            "         r.refund_amount AS amount,",
            "         sc.amount AS contractAmount,",
            "         sc.paid_amount AS paidAmount,",
            "         IFNULL(sc.amount, 0) - IFNULL(sc.paid_amount, 0) AS unpaidAmount,",
            "         sc.pay_off AS payOff,",
            "         r.operator AS operator,",
            "         r.student_id AS payer,",
            "         r.remark AS remark,",
            "         r.verify_state AS verifyState,",
            "         r.verify_staff AS verifyStaff,",
            "         r.verify_time AS verifyTime,",
            "         r.refund_lesson_count AS refundLessonCount,",
            "         r.apply_time AS applyTime,",
            "         r.done_time AS doneTime,",
            "         IFNULL(r.done_time, r.apply_time) AS operateTime",
            "    FROM refund r",
            "    LEFT JOIN student_course sc ON sc.id = r.student_course_id",
            "    LEFT JOIN student s ON s.id = r.student_id",
            ") t",
            "<where>",
            "  <if test='query.type != null'>",
            "    AND t.type = #{query.type}",
            "  </if>",
            "  <if test='query.studentName != null and query.studentName != \"\"'>",
            "    AND t.studentName LIKE CONCAT('%', #{query.studentName}, '%')",
            "  </if>",
            "  <if test='query.studentCourseId != null'>",
            "    AND t.studentCourseId = #{query.studentCourseId}",
            "  </if>",
            "  <if test='query.startTime != null'>",
            "    AND t.operateTime &gt;= #{query.startTime}",
            "  </if>",
            "  <if test='query.endTime != null'>",
            "    AND t.operateTime &lt;= #{query.endTime}",
            "  </if>",
            "  <if test='query.verifyState != null'>",
            "    AND t.verifyState = #{query.verifyState}",
            "  </if>",
            "</where>",
            "ORDER BY t.operateTime DESC",
            "</script>"
    })
    Page<FinanceDTO> selectFinancePage(Page<FinanceDTO> page, @Param("query") FinanceQuery query);
}
