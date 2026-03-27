package com.zeroone.star.eamsj3class.service;

import com.zeroone.star.eamsj3class.entity.Subject;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.query.j3.course.SubjectQuery;

import java.util.List;

/**
 * <p>
 * 科目 服务类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
public interface ISubjectService extends IService<Subject> {

    PageDTO<SubjectDTO> querySubjectList(SubjectQuery query);

    List<String> querySubjectNames();

    boolean saveSubject(SubjectDTO subjectDTO);

    boolean deleteSubjects(List<String> subjectIds);

}
