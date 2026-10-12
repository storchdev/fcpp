import fs from "node:fs";
import path from "node:path";

const ROOT = process.env.DATA_ROOT ?? path.resolve(process.cwd(), "..");

export type Classification = "UB" | "IF" | "UNS" | "LOGIC" | "PERF" | "CONC";

export type Case = {
  name: string;
  classification: Classification;
  detection: string[];
  dir: string;
  badCpp?: string;
  goodCpp?: string;
  goodRust?: string;
  explanation?: string;
  compilers?: string;
  headers: { std?: string; sanitize?: string; expect?: string };
};

export type Entry = {
  id: number;
  category: string;
  title: string;
  description: string;
  classification: Classification;
  difficulty: "easy" | "medium" | "hard";
  cppStandard: number | null;
  urls: string[];
  readme?: string;
  cases: Case[];
};

export type Summary = Pick<Entry, "id" | "category" | "title" | "description" | "classification" | "difficulty" | "cppStandard"> & {
  caseCount: number;
};

const read = (rel?: string) => {
  if (!rel) return undefined;
  try {
    return fs.readFileSync(path.join(ROOT, rel), "utf8");
  } catch {
    return undefined;
  }
};

const header = (src: string | undefined, key: string) => {
  const m = src?.split("\n").slice(0, 10).join("\n").match(new RegExp(`^//\\s*${key}:\\s*(\\S+)`, "m"));
  return m?.[1];
};

let cache: Entry[] | null = null;

export function entries(): Entry[] {
  if (cache) return cache;
  const raw = JSON.parse(fs.readFileSync(path.join(ROOT, "footguns.json"), "utf8"));
  cache = raw.map((e: any): Entry => ({
    id: e.id,
    category: e.category,
    title: String(e.title).replace(/`/g, ""),
    description: e.description,
    classification: e.classification,
    difficulty: e.difficulty,
    cppStandard: e.cpp_standard ?? null,
    urls: e.cppreference_urls ?? [],
    readme: read(e.examples?.readme),
    cases: (e.examples?.cases ?? []).map((c: any): Case => {
      const f = c.files ?? {};
      const bad = read(f.bad_cpp);
      return {
        name: c.name,
        classification: c.classification,
        detection: c.detection ?? [],
        dir: c.dir,
        badCpp: bad,
        goodCpp: read(f.good_cpp),
        goodRust: read(f.good_rust),
        explanation: read(f.explanation),
        compilers: read(f.compilers),
        headers: { std: header(bad, "std"), sanitize: header(bad, "sanitize"), expect: header(bad, "expect") },
      };
    }),
  }));
  return cache!;
}

export const summaries = (): Summary[] =>
  entries().map(({ id, category, title, description, classification, difficulty, cppStandard, cases }) => ({
    id, category, title, description, classification, difficulty, cppStandard, caseCount: cases.length,
  }));

/** Split explanation.md into its three fixed sections (the checker guarantees the skeleton). */
export function parseExplanation(md?: string) {
  const out = { why: "", fix: "", rust: "" };
  if (!md) return out;
  const parts = md.split(/^## /m).slice(1);
  for (const p of parts) {
    const nl = p.indexOf("\n");
    const head = p.slice(0, nl);
    const body = p.slice(nl + 1).trim();
    if (head.startsWith("Why")) out.why = body;
    else if (head.startsWith("The fix")) out.fix = body;
    else if (head.startsWith("Rust")) out.rust = body;
  }
  return out;
}

/** compilers.md minus its title line. */
export const parseCompilers = (md?: string) =>
  (md ?? "")
    .replace(/^# .*\n+/, "")
    .replace(/^\*\*(g\+\+ vs clang\+\+[^\n]*?\.)\*\*/m, "_$1_") // the bold run contains inline code and does not parse
    .trim();

/** README minus its title line. */
export const parseReadme = (md?: string) => (md ?? "").replace(/^# .*\n+/, "").trim();

export const caseTitle = (name: string) => {
  const s = name.replace(/-/g, " ");
  return s[0].toUpperCase() + s.slice(1);
};
