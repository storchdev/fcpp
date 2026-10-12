import type { Classification } from "./data";

export const CLASS_INFO: Record<Classification, { label: string; hint: string; cls: string }> = {
  UB: { label: "UB", hint: "Undefined behavior", cls: "text-red-300 bg-red-400/10 border-red-400/20" },
  IF: { label: "IF", hint: "Ill-formed", cls: "text-orange-300 bg-orange-400/10 border-orange-400/20" },
  UNS: { label: "UNS", hint: "Unspecified / implementation-defined", cls: "text-yellow-200 bg-yellow-300/10 border-yellow-300/20" },
  LOGIC: { label: "LOGIC", hint: "Well-defined but surprising", cls: "text-sky-300 bg-sky-400/10 border-sky-400/20" },
  PERF: { label: "PERF", hint: "Performance footgun", cls: "text-emerald-300 bg-emerald-400/10 border-emerald-400/20" },
  CONC: { label: "CONC", hint: "Concurrency / memory model", cls: "text-violet-300 bg-violet-400/10 border-violet-400/20" },
};

export const DIFF: Record<string, { label: string; dot: string }> = {
  easy: { label: "Easy", dot: "bg-sky-400" },
  medium: { label: "Medium", dot: "bg-amber-400" },
  hard: { label: "Hard", dot: "bg-rose-400" },
};

export const shortCategory = (c: string) => c.split(",")[0].replace(/ and .*$/, "");
