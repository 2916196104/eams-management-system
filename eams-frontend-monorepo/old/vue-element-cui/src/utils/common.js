import dataJs from "@/data/data.js";

// 码值取出
export const getEnumData = () => {
	return dataJs.enumData;
};

// 码值按code取出项
export const getEnumItem = (findCode) => {
	const data = getEnumData();
	if (typeof data[findCode] != "undefined") return data[findCode];
	else return [];
};
