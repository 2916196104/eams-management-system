package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.CreditLogDTO;
import com.zeroone.star.project.dto.j4.student.LessonCountDTO;
import com.zeroone.star.project.query.j4.student.ChangeCreditQuery;
import com.zeroone.star.project.query.j4.student.CreditSelectQuery;
import com.zeroone.star.student.entity.StudentCreditLog;
import com.zeroone.star.student.mapper.ISclMapper;
import com.zeroone.star.student.service.ISclServcie;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
public class ISclServcieImpl implements ISclServcie {

    @Resource
    ISclMapper iSclMapper;

    @Override
    public PageDTO<CreditLogDTO> PageCreditLog(CreditSelectQuery creditSelectQuery) {
        //使用QueryWrapperl查询
        QueryWrapper<StudentCreditLog> wrapper = new QueryWrapper<>();
        if(!creditSelectQuery.getStudent_Name().isEmpty()){
            //查询对应学生的id，并且使用对应的id来查询
            String id = iSclMapper.SelectIdByName(creditSelectQuery.getStudent_Name());
            wrapper.eq("student_id", id);
        }
        //筛选时间
        if(!creditSelectQuery.getBegin_time().isEmpty()) {
            wrapper.ge("add_time",creditSelectQuery.getBegin_time());
        }
        if(!creditSelectQuery.getEnd_time().isEmpty()){
            wrapper.le("add_time",creditSelectQuery.getEnd_time());
        }
        //时间倒序
        wrapper.orderByDesc("add_time");
        List<StudentCreditLog> list = iSclMapper.selectList(wrapper);

        //填充DTO数据
        List<CreditLogDTO> creditLogDTOS = new ArrayList<>();
        int i = 1;
        for(StudentCreditLog scl : list){
            CreditLogDTO creditLogDTO = new CreditLogDTO();
            creditLogDTO.setId(String.valueOf(i));
            creditLogDTO.setStudent_name(creditSelectQuery.getStudent_Name());
            creditLogDTO.setChange_credit(String.valueOf(scl.getCredit()));
            creditLogDTO.setRemain_credit(String.valueOf(scl.getCurrent_credit()));
            creditLogDTO.setRemain_credit(scl.getRemark());
            creditLogDTO.setChange_time(String.valueOf(scl.getAdd_time()));
            creditLogDTOS.add(creditLogDTO);
        }

        //组装数据
        Page<CreditLogDTO> page = new Page<>(1, 10);
        page.setRecords(creditLogDTOS);
        page.setTotal(creditLogDTOS.size());
        page.setCurrent(1);
        page.setSize(10);
        page.setPages((long) Math.ceil((double) creditLogDTOS.size() / 10));

        //转换PageDTO
        PageDTO<CreditLogDTO> pageDTO = PageDTO.create(page, CreditLogDTO.class);
        return pageDTO;
    }

    @Override
    public boolean saveCreditLog(ChangeCreditQuery changeCreditQuery) {
        //首先从student表中查询对应剩下的积分，再修改并且打log
        int remainCredit = iSclMapper.SelectCreditById(changeCreditQuery.getStudent_id());
        int changeCredit = Integer.parseInt(changeCreditQuery.getChange_credit());
        int currentCredit = remainCredit + changeCredit;
        //修改student对应积分
        iSclMapper.UpdateCreditById(currentCredit, Integer.parseInt(changeCreditQuery.getStudent_id()));

        StudentCreditLog studentCreditLog = new StudentCreditLog();
        studentCreditLog.setStudent_id(Integer.parseInt(changeCreditQuery.getStudent_id()));
        studentCreditLog.setCredit(changeCredit);
        studentCreditLog.setCurrent_credit(currentCredit);
//        studentCreditLog.setChange_yype();变动类型
//        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        studentCreditLog.setAdd_time(now);
        studentCreditLog.setRemark(changeCreditQuery.getRemark());
//        studentCreditLog.setSource_id();记录来源id
//        studentCreditLog.setStaff_id();记录来源人
//        studentCreditLog.setSchool_id();学生所属学校ID
        int insert = iSclMapper.insert(studentCreditLog);
        return insert > 0;
    }
}
