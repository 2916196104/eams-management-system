package com.zeroone.star.course.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.course.entity.SubjectDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.subject.SubjectDTO;
import com.zeroone.star.project.query.j9.subject.SubjectQuery;
import com.zeroone.star.project.vo.j9.subject.SubjectNameVO;
import com.zeroone.star.project.vo.j9.subject.SubjectVO;

import java.util.List;

public interface ISubjectService extends IService<SubjectDO> {
    List<SubjectNameVO> listSubjectNames();

    PageDTO<SubjectVO> listSubjectPage(SubjectQuery condition);

    Long saveSubject(SubjectDTO subjectDTO);

    boolean removeSubjects(List<Long> ids);
}
