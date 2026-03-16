package com.zeroone.star.project.j3.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;


import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * <p>
 * 描述：课程模块Api
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
public interface CourseApis {

    /**
     * 获取科目列表（条件 + 分页)
     * @param courseListQuery 查询参数
     * @return 查询结果
     */
    JsonVO<PageDTO<SubjectDTO>> queryCourseList(SubjectQuery courseListQuery);

    /**
     * 查询科目名称列表
     * @return 查询结果
     */
    JsonVO<List<String>> querySubjectNames();

    /**
     * 保存科目数据
     * @param subjectDto 科目数据
     */
    JsonVO<String> saveSubject(SubjectDTO subjectDto);

    /**
     * 删除科目(支持批量删除)
     * @param subjectIds 科目id列表
     */
    JsonVO<String> deleteSubjects( @NotEmpty(message = "列表不能为空") List<String> subjectIds);
}
