import type apiDefinitions from "@/api/apiDefinitions";

type MeApiKey = Extract<keyof typeof apiDefinitions, `me.${string}`>;

type MeApis = {
  [K in MeApiKey as K extends `me.${infer Name}` ? Name : never]: (...args: any[]) => any;
};

declare global {
  interface Apis {
    me: MeApis;
  }
}

export {};
