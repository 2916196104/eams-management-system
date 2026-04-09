/**
 * flowable:assignee属性的输入框扩展支持
 */

import { html } from "htm/preact";
import { TextFieldEntry, isTextFieldEntryEdited } from "@bpmn-io/properties-panel";
import { useService } from "bpmn-js-properties-panel";

function Assignee(props) {
	const { element, id } = props;
	const modeling = useService("modeling");
	const translate = useService("translate");
	const debounce = useService("debounceInput");

	const getValue = () => {
		return element.businessObject.assignee || "";
	};

	const setValue = (value) => {
		return modeling.updateProperties(element, {
			assignee: value,
		});
	};

	return html`
		<${TextFieldEntry}
			id=${id}
			element=${element}
			description=${translate("Assign this task assignee")}
			label=${translate("Assignee")}
			getValue=${getValue}
			setValue=${setValue}
			debounce=${debounce}
			tooltip=${translate("Assign this task assignee")}
		/>
	`;
}

export default function (element) {
	return {
		id: "assignee",
		element,
		component: Assignee,
		isEdited: isTextFieldEntryEdited,
	};
}
