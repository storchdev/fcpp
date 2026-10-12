"use client";

import { useState, type ReactNode } from "react";
import { Check, ChevronDown, FileCode2, ShieldAlert, Terminal, X } from "lucide-react";

export type CaseData = {
  name: string;
  label: string;
  classification: ReactNode;
  chips: string[];
  explanation: { why: ReactNode; fix: ReactNode; rust: ReactNode };
  code: { bad?: ReactNode; good?: ReactNode; rust?: ReactNode };
  compilers: ReactNode;
};

function Panel({ file, tone, children, className = "" }: { file: string; tone: "bad" | "good" | "rust"; children: ReactNode; className?: string }) {
  const Icon = tone === "bad" ? X : tone === "good" ? Check : FileCode2;
  const color = tone === "bad" ? "text-red-300" : tone === "good" ? "text-emerald-300" : "text-orange-300";
  return (
    <div className={`flex min-w-0 flex-col overflow-hidden rounded-xl border border-line bg-[#0e0e12] ${className}`}>
      <div className="flex items-center gap-2 border-b border-line px-4 py-2 font-mono text-[12px] text-zinc-400">
        <Icon className={`h-3.5 w-3.5 ${color}`} />
        {file}
      </div>
      {children}
    </div>
  );
}

export function CaseView({ cases, overview }: { cases: CaseData[]; overview?: ReactNode }) {
  const [ci, setCi] = useState(0);
  const showOverview = ci === -1;
  const c = cases[Math.max(ci, 0)];
  const multi = cases.length > 1;

  return (
    <div>
      {(multi || overview) && (
        <div className="mb-6 flex flex-wrap gap-1.5">
          {overview && <Pill active={showOverview} onClick={() => setCi(-1)}>Overview</Pill>}
          {cases.map((x, i) => (
            <Pill key={x.name} active={ci === i} onClick={() => setCi(i)}>
              <span className="mr-1.5 font-mono text-[11px] opacity-60">{String(i + 1).padStart(2, "0")}</span>
              {x.label}
            </Pill>
          ))}
        </div>
      )}

      {showOverview ? (
        <div key="overview" className="max-w-3xl animate-rise">{overview}</div>
      ) : (
        <div key={c.name} className="animate-rise">
          <div className="mb-5 flex flex-wrap items-baseline gap-2 text-[13px]">
            {c.classification}
            {c.chips.map((chip) => (
              <span key={chip} className="font-mono text-[12px] text-muted before:mr-2 before:text-zinc-700 before:content-['·']">{chip}</span>
            ))}
          </div>

          <div className="space-y-4">
            <div className="grid items-start gap-4 xl:grid-cols-2 xl:gap-y-3">
              {c.code.bad && <Panel file="bad.cpp" tone="bad" className="order-1 h-full xl:order-1">{c.code.bad}</Panel>}
              {c.explanation.why && (
                <Fold className="order-2 xl:order-3" icon={<ShieldAlert className="h-4 w-4 text-red-300" />} title="Why the bad code is wrong">{c.explanation.why}</Fold>
              )}
              {c.code.good && <Panel file="good.cpp" tone="good" className="order-3 h-full xl:order-2">{c.code.good}</Panel>}
              {c.explanation.fix && (
                <Fold className="order-4 xl:order-4" icon={<Check className="h-4 w-4 text-emerald-300" />} title="The fix">{c.explanation.fix}</Fold>
              )}
            </div>
            {c.code.rust && (
              <div className="space-y-3">
                <Panel file="good.rs" tone="rust">{c.code.rust}</Panel>
                <Fold icon={<FileCode2 className="h-4 w-4 text-orange-300" />} title="Rust">{c.explanation.rust}</Fold>
              </div>
            )}
            {!c.code.rust && <Fold icon={<FileCode2 className="h-4 w-4 text-orange-300" />} title="Rust">{c.explanation.rust}</Fold>}
            <Fold icon={<Terminal className="h-4 w-4 text-sky-300" />} title="g++ vs clang++">{c.compilers}</Fold>
          </div>
        </div>
      )}
    </div>
  );
}

function Pill({ active, onClick, children }: { active: boolean; onClick: () => void; children: ReactNode }) {
  return (
    <button
      onClick={onClick}
      className={`rounded-lg border px-3 py-1.5 text-[13px] transition-all duration-200 active:scale-95 ${
        active ? "border-accent/40 bg-accent/10 text-accent" : "border-line text-muted hover:border-zinc-600 hover:text-zinc-200"
      }`}
    >
      {children}
    </button>
  );
}

function Fold({ icon, title, children, className = "" }: { icon: ReactNode; title: string; children: ReactNode; className?: string }) {
  const [open, setOpen] = useState(false);
  return (
    <section className={`rounded-xl border border-line bg-panel/60 ${className}`}>
      <button
        onClick={() => setOpen(!open)}
        aria-expanded={open}
        className="flex w-full items-center gap-2.5 px-4 py-3 text-left text-sm text-zinc-300 transition-colors hover:text-zinc-50"
      >
        {icon}
        {title}
        <ChevronDown className={`ml-auto h-4 w-4 text-muted transition-transform duration-300 ${open ? "rotate-180" : ""}`} />
      </button>
      <div className={`grid transition-[grid-template-rows] duration-300 ease-out ${open ? "grid-rows-[1fr]" : "grid-rows-[0fr]"}`}>
        <div className="overflow-hidden">
          <div className={`border-t border-line px-5 py-5 transition-opacity duration-300 ${open ? "opacity-100" : "opacity-0"}`}>{children}</div>
        </div>
      </div>
    </section>
  );
}
