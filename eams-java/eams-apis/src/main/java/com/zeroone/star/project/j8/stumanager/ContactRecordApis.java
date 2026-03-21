package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddContactRecordDTO;
import com.zeroone.star.project.query.j8.stumanager.ContactRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ContactRecordListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

/**
 * 跟进记录API接口
 */
@Api(tags = "跟进记录")
public interface ContactRecordApis {

    /**
     * 分页查询跟进记录列表
     *
     * @param query 查询参数
     * @return 分页结果
     */
    @ApiOperation(value = "查询跟进记录列表", notes = "支持按学员、跟进人、日期范围、进展阶段筛选")
    JsonVO<ExtendPageDTO<ContactRecordListVO>> getContactRecords(ContactRecordQuery query);

    /**
     * 添加跟进记录
     *
     * @param dto 跟进记录参数
     * @return 操作结果
     */
    @ApiOperation(value = "添加跟进记录", notes = "为指定学员添加跟进记录")
    JsonVO<Void> addContactRecord(@Validated @RequestBody AddContactRecordDTO dto);

    /**
     * 删除跟进记录
     *
     * @param id 记录ID
     * @return 操作结果
     */
    @ApiOperation(value = "删除跟进记录", notes = "根据ID删除跟进记录")
    JsonVO<Void> deleteContactRecord(@PathVariable Long id);
}
