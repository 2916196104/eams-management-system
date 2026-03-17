#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO) ///< Begin DTO codegen section

class GradeListDTO : public oatpp::DTO
{
	/* GradeDTO extends from DTO */
	DTO_INIT(GradeListDTO, DTO);

	/* grade fields */
	DTO_FIELD(Int64, id, "primary key");
	DTO_FIELD(String, title, "grade project title");
	DTO_FIELD(String, info, "grade project information");
	DTO_FIELD(Int64, creator, "creator id");
	DTO_FIELD(Boolean, deleted, "logic delete");
	DTO_FIELD(Int64, editor, "editor id");
	DTO_FIELD(Int64, org_id, "organization id");

	/* grade record fields */
	DTO_FIELD(Int64, grade_id, "grade id");
	DTO_FIELD(Int64, student_id, "student id");
	DTO_FIELD(Int8, score, "grade score");
};

class GradeListPageDTO : public PageDTO<GradeListDTO::Wrapper>
{
	DTO_INIT(GradeListPageDTO, PageDTO<GradeListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO) ///< End DTO codegen section