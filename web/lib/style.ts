import type { Classification } from "./data";

export const CLASS_INFO: Record<Classification, { label: string; hint: string; cls: string }> = {
  UB: { label: "UB", hint: "Undefined behavior", cls: "text-red-300" },
  IF: { label: "IF", hint: "Ill-formed", cls: "text-orange-300" },
  UNS: { label: "UNS", hint: "Unspecified / implementation-defined", cls: "text-yellow-200" },
  LOGIC: { label: "LOGIC", hint: "Well-defined but surprising", cls: "text-sky-300" },
  PERF: { label: "PERF", hint: "Performance footgun", cls: "text-emerald-300" },
  CONC: { label: "CONC", hint: "Concurrency / memory model", cls: "text-violet-300" },
};

export const DIFF: Record<string, { label: string; cls: string; rank: number }> = {
  easy: { label: "Easy", cls: "text-sky-300", rank: 0 },
  medium: { label: "Medium", cls: "text-amber-300", rank: 1 },
  hard: { label: "Hard", cls: "text-rose-300", rank: 2 },
};

export const shortCategory = (c: string) => c.split(",")[0].replace(/ and .*$/, "");
