package com.zeroone.star.project.j9.subject;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.subject.SubjectDTO;
import com.zeroone.star.project.query.j9.subject.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.subject.SubjectNameVO;
import com.zeroone.star.project.vo.j9.subject.SubjectVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * 描述：科目接口声明
 * @author Fhc1m
 * @version 1.0.0
 */
public interface SubjectApis {

    /**
     * 获取科目名称列表
     * @return 科目名称列表
     */
    JsonVO<List<SubjectNameVO>> querySubjectNames();

    /**
     * 分页查询科目列表
     * @param condition 查询条件
     * @return 当前页信息
     */
    JsonVO<PageDTO<SubjectVO>> querySubjectPage(SubjectQuery condition);

    /**
     * 保存科目信息
     * @param subjectDTO 科目对象
     * @return 科目唯一id
     */
    JsonVO<Long> addSubject(@RequestBody SubjectDTO subjectDTO);

    /**
     * 批量删除科目
     * @param ids 科目id列表
     * @return 删除结果
     */
    JsonVO<String> removeSubjects(
            @ApiParam(value = "科目ID列表", required = true) @RequestBody List<Long> ids);
}
