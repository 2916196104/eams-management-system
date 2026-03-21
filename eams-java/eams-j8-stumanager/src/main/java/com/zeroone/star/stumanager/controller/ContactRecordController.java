package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddContactRecordDTO;
import com.zeroone.star.project.j8.stumanager.ContactRecordApis;
import com.zeroone.star.project.query.j8.stumanager.ContactRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ContactRecordListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * 跟进记录控制器
 */
@Api(tags = "跟进记录")
@RequestMapping("/stu/contact-record")
@RestController
public class ContactRecordController implements ContactRecordApis {

    /**
     * 查询跟进记录列表
     */
    @GetMapping("/list")
    @ApiOperation(value = "查询跟进记录列表", notes = "支持按学员、跟进人、日期范围、进展阶段筛选")
    @Override
    public JsonVO<ExtendPageDTO<ContactRecordListVO>> getContactRecords(ContactRecordQuery query) {
        // 返回测试数据
        ExtendPageDTO<ContactRecordListVO> pageDTO = new ExtendPageDTO<>();
        pageDTO.setPageIndex(query.getPageIndex());
        pageDTO.setPageSize(query.getPageSize());
        pageDTO.setTotal(96L);
        pageDTO.setPages(5L);

        List<ContactRecordListVO> list = new ArrayList<>();
        ContactRecordListVO vo = new ContactRecordListVO();
        vo.setId(1L);
        vo.setStudentId(1L);
        vo.setStudentName("张三");
        vo.setCreator(1L);
        vo.setCreatorName("管理员");
        vo.setContactTime(LocalDateTime.of(2026, 3, 21, 0, 0));
        vo.setContactNextTime(LocalDateTime.of(2026, 3, 21, 0, 0));
        vo.setContactTypeName("电话");
        vo.setContactPhone("13800138000");
        vo.setStageName("目标客户阶段");
        vo.setInfo("客户有意向，需要跟进");
        vo.setAddTime(LocalDateTime.of(2026, 3, 21, 13, 47));
        list.add(vo);

        pageDTO.setRows(list);

        JsonVO<ExtendPageDTO<ContactRecordListVO>> jsonVO = new JsonVO<>();
        jsonVO.setData(pageDTO);
        jsonVO.setCode(10000);
        jsonVO.setMessage("success");
        return jsonVO;
    }

    /**
     * 添加跟进记录
     */
    @PostMapping("/add")
    @ApiOperation(value = "添加跟进记录", notes = "为指定学员添加跟进记录")
    @Override
    public JsonVO<Void> addContactRecord(@Validated @RequestBody AddContactRecordDTO dto) {
        JsonVO<Void> jsonVO = new JsonVO<>();
        jsonVO.setCode(10000);
        jsonVO.setMessage("添加成功");
        return jsonVO;
    }

    /**
     * 删除跟进记录
     */
    @DeleteMapping("/delete/{id}")
    @ApiOperation(value = "删除跟进记录", notes = "根据ID删除跟进记录")
    @Override
    public JsonVO<Void> deleteContactRecord(@PathVariable Long id) {
        JsonVO<Void> jsonVO = new JsonVO<>();
        jsonVO.setCode(10000);
        jsonVO.setMessage("删除成功");
        return jsonVO;
    }
}
