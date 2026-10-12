"use client";

import { useState, type ReactNode } from "react";
import { Check, FileCode2, ShieldAlert, X } from "lucide-react";

export type CaseData = {
  name: string;
  label: string;
  classification: ReactNode;
  chips: string[];
  explanation: { why: ReactNode; fix: ReactNode; rust: ReactNode };
  code: { bad?: ReactNode; good?: ReactNode; rust?: ReactNode };
  compilers: ReactNode;
};

const TABS = ["Explanation", "Code", "Compilers"] as const;

function Panel({ file, tone, children, className = "" }: { file: string; tone: "bad" | "good" | "rust"; children: ReactNode; className?: string }) {
  const Icon = tone === "bad" ? X : tone === "good" ? Check : FileCode2;
  const color = tone === "bad" ? "text-red-300" : tone === "good" ? "text-emerald-300" : "text-orange-300";
  return (
    <div className={`min-w-0 overflow-hidden rounded-xl border border-line bg-[#0e0e12] ${className}`}>
      <div className="flex items-center gap-2 border-b border-line px-4 py-2 font-mono text-[12px] text-zinc-400">
        <Icon className={`h-3.5 w-3.5 ${color}`} />
        {file}
      </div>
      {children}
    </div>
  );
}

export function CaseView({ cases, overview }: { cases: CaseData[]; overview?: ReactNode }) {
  const [ci, setCi] = useState(-1 + (overview ? 0 : 1));
  const [tab, setTab] = useState<(typeof TABS)[number]>("Explanation");
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
        <div key="overview" className="animate-rise">{overview}</div>
      ) : (
        <div key={c.name} className="animate-rise">
          <div className="mb-5 flex flex-wrap items-center gap-2 text-[13px]">
            {c.classification}
            {c.chips.map((chip) => (
              <span key={chip} className="rounded border border-line px-1.5 py-0.5 font-mono text-[12px] text-muted">{chip}</span>
            ))}
          </div>

          <div className="mb-6 flex gap-6 border-b border-line">
            {TABS.map((t) => (
              <button
                key={t}
                onClick={() => setTab(t)}
                className={`relative -mb-px pb-2.5 text-sm transition-colors ${tab === t ? "text-zinc-50" : "text-muted hover:text-zinc-300"}`}
              >
                {t}
                <span className={`absolute inset-x-0 -bottom-px h-px bg-accent transition-opacity duration-200 ${tab === t ? "opacity-100" : "opacity-0"}`} />
              </button>
            ))}
          </div>

          <div key={tab} className="animate-rise">
            {tab === "Explanation" && (
              <div className="space-y-9">
                <Section icon={<ShieldAlert className="h-4 w-4 text-red-300" />} title="Why the bad code is wrong">{c.explanation.why}</Section>
                <Section icon={<Check className="h-4 w-4 text-emerald-300" />} title="The fix">{c.explanation.fix}</Section>
                <Section icon={<FileCode2 className="h-4 w-4 text-orange-300" />} title="Rust">{c.explanation.rust}</Section>
              </div>
            )}
            {tab === "Code" && (
              <div className="grid gap-4 lg:grid-cols-2">
                {c.code.bad && <Panel file="bad.cpp" tone="bad">{c.code.bad}</Panel>}
                {c.code.good && <Panel file="good.cpp" tone="good">{c.code.good}</Panel>}
                {c.code.rust && <Panel file="good.rs" tone="rust" className="lg:col-span-2">{c.code.rust}</Panel>}
              </div>
            )}
            {tab === "Compilers" && c.compilers}
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

function Section({ icon, title, children }: { icon: ReactNode; title: string; children: ReactNode }) {
  return (
    <section>
      <h2 className="mb-3 flex items-center gap-2 text-[13px] font-medium uppercase tracking-wider text-muted">
        {icon}
        {title}
      </h2>
      {children}
    </section>
  );
}
