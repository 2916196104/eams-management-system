/**
 * flowable条件表达式属性输入框支持
 */

import { html } from "htm/preact";
import { TextFieldEntry, isTextFieldEntryEdited } from "@bpmn-io/properties-panel";
import { useService } from "bpmn-js-properties-panel";

function ConditionExp(props) {
	const { element, id } = props;
	const modeling = useService("modeling");
	const moddle = useService("moddle");
	const translate = useService("translate");
	const debounce = useService("debounceInput");

	const getValue = () => {
		if (element.businessObject.conditionExpression) {
			return element.businessObject.conditionExpression.body;
		}
		return "";
	};

	const setValue = (value) => {
		let newCondition = moddle.create("bpmn:FormalExpression", {
			body: value,
		});
		return modeling.updateProperties(element, {
			conditionExpression: newCondition,
		});
	};

	return html`
		<${TextFieldEntry}
			id=${id}
			element=${element}
			description=${translate("Setting condition expression")}
			label=${translate("Condition expression")}
			getValue=${getValue}
			setValue=${setValue}
			debounce=${debounce}
			tooltip=${translate("Setting condition expression")}
		/>
	`;
}

export default function (element) {
	return {
		id: "conditionExp",
		element,
		component: ConditionExp,
		isEdited: isTextFieldEntryEdited,
	};
}
