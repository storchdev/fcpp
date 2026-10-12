"use client";

import Link from "next/link";
import { useEffect, useMemo, useRef, useState } from "react";
import { ArrowDown, ArrowUp, ChevronDown, ChevronRight, Search } from "lucide-react";
import type { Classification, Summary } from "@/lib/data";
import { CLASS_INFO, DIFF, shortCategory } from "@/lib/style";
import { ClassBadge, Difficulty } from "./Badge";

const CLASSES = Object.keys(CLASS_INFO) as Classification[];
type SortKey = "id" | "title" | "category" | "classification" | "difficulty";
const COLS: { key: SortKey; label: string }[] = [
  { key: "id", label: "#" },
  { key: "title", label: "Title" },
  { key: "category", label: "Category" },
  { key: "classification", label: "Type" },
  { key: "difficulty", label: "Difficulty" },
];
const GRID = "grid-cols-[3rem_1fr_9rem_5rem_6.5rem_1rem]";

function Select({ children, className = "", ...p }: React.SelectHTMLAttributes<HTMLSelectElement>) {
  return (
    <div className={`relative ${className}`}>
      <select
        {...p}
        className="h-9 w-full appearance-none rounded-lg border border-line bg-panel pl-3 pr-9 text-[13px] text-zinc-300 transition-colors hover:border-zinc-600 focus:border-zinc-500"
      >
        {children}
      </select>
      <ChevronDown className="pointer-events-none absolute right-3 top-1/2 h-3.5 w-3.5 -translate-y-1/2 text-muted" />
    </div>
  );
}

export function Catalog({ items }: { items: Summary[] }) {
  const [q, setQ] = useState("");
  const [cls, setCls] = useState<Classification | null>(null);
  const [diff, setDiff] = useState("");
  const [std, setStd] = useState("");
  const [cat, setCat] = useState("");
  const [sort, setSort] = useState<{ key: SortKey; dir: 1 | -1 }>({ key: "id", dir: 1 });
  const input = useRef<HTMLInputElement>(null);

  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      const t = e.target as HTMLElement;
      if (e.key === "/" && !/INPUT|SELECT|TEXTAREA/.test(t.tagName)) {
        e.preventDefault();
        input.current?.focus();
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, []);

  const categories = useMemo(() => Array.from(new Set(items.map((i) => i.category))), [items]);
  const counts = useMemo(() => {
    const c: Record<string, number> = {};
    for (const i of items) c[i.classification] = (c[i.classification] ?? 0) + 1;
    return c;
  }, [items]);

  const toggleSort = (key: SortKey) =>
    setSort((s) => (s.key !== key ? { key, dir: 1 } : s.dir === 1 ? { key, dir: -1 } : { key: "id", dir: 1 }));

  const shown = useMemo(() => {
    const needle = q.trim().toLowerCase();
    const val = (i: Summary) =>
      sort.key === "difficulty" ? DIFF[i.difficulty].rank : sort.key === "category" ? shortCategory(i.category) : i[sort.key];
    return items.filter(
      (i) =>
        (!cls || i.classification === cls) &&
        (!diff || i.difficulty === diff) &&
        (!std || (i.cppStandard ?? 0) >= Number(std)) &&
        (!cat || i.category === cat) &&
        (!needle ||
          `${i.id} ${i.title} ${i.description} ${i.category} ${i.classification}`.toLowerCase().includes(needle)),
    ).sort((a, b) => {
      const x = val(a), y = val(b);
      const c = typeof x === "number" && typeof y === "number" ? x - y : String(x).localeCompare(String(y));
      return (c || a.id - b.id) * sort.dir;
    });
  }, [items, q, cls, diff, std, cat, sort]);

  return (
    <div className="rounded-xl border border-line bg-panel/60">
      <div className="space-y-3 border-b border-line p-3.5">
        <div className="relative">
          <Search className="pointer-events-none absolute left-3 top-1/2 h-4 w-4 -translate-y-1/2 text-muted" />
          <input
            ref={input}
            value={q}
            onChange={(e) => setQ(e.target.value)}
            placeholder="Search by title, description, category…"
            className="h-10 w-full rounded-lg border border-line bg-bg pl-9 pr-10 text-sm placeholder:text-zinc-600 transition-colors hover:border-zinc-600 focus:border-zinc-500 focus:outline-none"
          />
          <kbd className="absolute right-2.5 top-1/2 -translate-y-1/2 rounded border border-line px-1.5 font-mono text-[11px] text-muted">/</kbd>
        </div>
        <div className="flex flex-wrap items-center gap-2">
          {CLASSES.map((c) => (
            <button
              key={c}
              onClick={() => setCls(cls === c ? null : c)}
              title={CLASS_INFO[c].hint}
              aria-pressed={cls === c}
              className={`h-8 rounded-lg px-2.5 font-mono text-[12px] transition-all duration-200 active:scale-95 ${
                cls === c ? `bg-white/[0.08] ${CLASS_INFO[c].cls}` : "text-muted hover:bg-white/[0.04] hover:text-zinc-200"
              }`}
            >
              {c} <span className="opacity-60">{counts[c] ?? 0}</span>
            </button>
          ))}
          <div className="ml-auto flex gap-2">
            <Select value={std} onChange={(e) => setStd(e.target.value)} aria-label="C++ standard">
              <option value="">Any standard</option>
              {[11, 14, 17, 20].map((s) => (
                <option key={s} value={s}>
                  C++{s} and newer
                </option>
              ))}
            </Select>
            <Select value={diff} onChange={(e) => setDiff(e.target.value)} aria-label="Difficulty">
              <option value="">Any difficulty</option>
              <option value="easy">Easy</option>
              <option value="medium">Medium</option>
              <option value="hard">Hard</option>
            </Select>
            <Select value={cat} onChange={(e) => setCat(e.target.value)} className="max-w-[210px]" aria-label="Category">
              <option value="">All categories</option>
              {categories.map((c) => (
                <option key={c} value={c}>
                  {shortCategory(c)}
                </option>
              ))}
            </Select>
          </div>
        </div>
      </div>

      <div className="px-4 py-2.5 text-[13px] text-muted">
        {shown.length} of {items.length} footguns
      </div>

      <div className={`hidden ${GRID} gap-4 border-y border-line px-4 py-2 text-[12px] uppercase tracking-wider text-muted md:grid`}>
        {COLS.map((c) => {
          const on = sort.key === c.key;
          const Arrow = sort.dir === 1 ? ArrowUp : ArrowDown;
          return (
            <button key={c.key} onClick={() => toggleSort(c.key)} className={`flex items-center gap-1 text-left uppercase tracking-wider transition-colors hover:text-zinc-200 ${on ? "text-zinc-200" : ""}`}>
              {c.label}
              <Arrow className={`h-3 w-3 transition-opacity ${on && !(c.key === "id" && sort.dir === 1) ? "opacity-100" : "opacity-0"}`} />
            </button>
          );
        })}
        <span />
      </div>

      <ul>
        {shown.map((i, n) => (
          <li key={i.id} className="animate-rise border-b border-line/70 last:border-b-0" style={{ animationDelay: `${Math.min(n, 14) * 18}ms` }}>
            <Link
              href={`/${i.id}`}
              className="group grid grid-cols-[2.5rem_1fr_auto] items-center gap-x-4 gap-y-1 px-4 py-3 transition-colors hover:bg-white/[0.035] md:grid-cols-[3rem_1fr_9rem_5rem_6.5rem_1rem]"
            >
              <span className="font-mono text-[13px] tabular-nums text-muted">{String(i.id).padStart(3, "0")}</span>
              <span className="min-w-0">
                <span className="block truncate text-[15px] font-medium text-zinc-100">{i.title}</span>
                <span className="block truncate text-[13px] text-muted md:hidden">{shortCategory(i.category)}</span>
              </span>
              <span className="hidden truncate text-[13px] text-muted md:block">{shortCategory(i.category)}</span>
              <span className="hidden md:block">
                <ClassBadge value={i.classification} />
              </span>
              <span className="hidden md:block">
                <Difficulty value={i.difficulty} />
              </span>
              <span className="hidden md:block">
                <ChevronRight className="h-4 w-4 -translate-x-1 text-zinc-600 opacity-0 transition-all duration-200 group-hover:translate-x-0 group-hover:opacity-100" />
              </span>
              <span className="md:hidden">
                <ClassBadge value={i.classification} />
              </span>
            </Link>
          </li>
        ))}
        {shown.length === 0 && <li className="px-4 py-14 text-center text-sm text-muted">No footguns match those filters.</li>}
      </ul>
    </div>
  );
}
