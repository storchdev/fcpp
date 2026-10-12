import Link from "next/link";
import { notFound } from "next/navigation";
import { ArrowLeft, ArrowRight, ExternalLink } from "lucide-react";
import { caseTitle, entries, parseCompilers, parseExplanation, parseReadme } from "@/lib/data";
import { shortCategory } from "@/lib/style";
import { ClassBadge, Difficulty } from "@/components/Badge";
import { CodeBlock, Markdown } from "@/components/Markdown";
import { CaseView, type CaseData } from "@/components/CaseView";

export const dynamicParams = false;
export const generateStaticParams = () => entries().map((e) => ({ id: String(e.id) }));

export async function generateMetadata({ params }: { params: Promise<{ id: string }> }) {
  const id = Number((await params).id);
  const e = entries().find((x) => x.id === id);
  return { title: e ? e.title : "Not found" };
}

const detectionLabel = (d: string) => {
  const [kind, ...rest] = d.split(":");
  if (kind === "none") return "no tool detects this";
  if (kind === "error") return "compile error";
  if (kind === "warning") return `${rest[0]} ${rest[1]}`;
  if (kind === "tool") return rest.slice(1).join(":") ? `${rest[0]} ${rest.slice(1).join(":")}` : rest[0];
  return `${kind} ${rest.join(":")}`;
};

export default async function EntryPage({ params }: { params: Promise<{ id: string }> }) {
  const id = Number((await params).id);
  const all = entries();
  const idx = all.findIndex((e) => e.id === id);
  if (idx < 0) notFound();
  const e = all[idx];
  const prev = all[idx - 1];
  const next = all[idx + 1];

  const cases: CaseData[] = e.cases.map((c) => {
    const x = parseExplanation(c.explanation);
    const chips = [
      c.headers.std,
      ...c.detection.map(detectionLabel),
    ].filter(Boolean) as string[];
    return {
      name: c.name,
      label: caseTitle(c.name),
      classification: <ClassBadge value={c.classification} />,
      chips,
      explanation: {
        why: <Markdown>{x.why}</Markdown>,
        fix: <Markdown>{x.fix}</Markdown>,
        rust: <Markdown>{x.rust}</Markdown>,
      },
      code: {
        bad: c.badCpp && <CodeBlock code={c.badCpp} lang="cpp" />,
        good: c.goodCpp && <CodeBlock code={c.goodCpp} lang="cpp" />,
        rust: c.goodRust && <CodeBlock code={c.goodRust} lang="rust" />,
      },
      compilers: <Markdown>{parseCompilers(c.compilers)}</Markdown>,
    };
  });

  return (
    <article>
      <Link href="/" className="mb-6 inline-flex items-center gap-1.5 text-[13px] text-muted transition-colors hover:text-zinc-200">
        <ArrowLeft className="h-3.5 w-3.5" /> All footguns
      </Link>

      <header className="mb-9 animate-rise">
        <div className="mb-3 flex flex-wrap items-center gap-3">
          <span className="font-mono text-[13px] text-muted">{String(e.id).padStart(3, "0")}</span>
          <ClassBadge value={e.classification} />
          <Difficulty value={e.difficulty} />
          <span className="text-[13px] text-muted">{shortCategory(e.category)}</span>
          {e.cppStandard && <span className="font-mono text-[12px] text-muted">since C++{e.cppStandard}</span>}
        </div>
        <h1 className="text-3xl font-semibold tracking-tight text-zinc-50">{e.title}</h1>
        <p className="mt-3 max-w-3xl text-[15px] leading-7 text-zinc-400">{e.description}</p>
        {e.urls.length > 0 && (
          <div className="mt-4 flex flex-wrap gap-x-5 gap-y-1">
            {e.urls.map((u) => (
              <a key={u} href={u} target="_blank" rel="noreferrer" className="inline-flex items-center gap-1.5 text-[13px] text-accent/90 hover:text-accent">
                {u.replace(/^https:\/\/en\.cppreference\.com\/w\//, "cppreference/")} <ExternalLink className="h-3 w-3" />
              </a>
            ))}
          </div>
        )}
      </header>

      <CaseView cases={cases} overview={e.readme ? <Markdown>{parseReadme(e.readme)}</Markdown> : undefined} />

      <nav className="mt-16 grid grid-cols-2 gap-3 border-t border-line pt-6">
        {prev ? (
          <Link href={`/${prev.id}`} className="group rounded-lg border border-line p-3.5 transition-colors hover:border-zinc-600">
            <span className="flex items-center gap-1.5 text-[12px] text-muted"><ArrowLeft className="h-3 w-3 transition-transform group-hover:-translate-x-0.5" /> {String(prev.id).padStart(3, "0")}</span>
            <span className="mt-1 block truncate text-sm text-zinc-200">{prev.title}</span>
          </Link>
        ) : <span />}
        {next ? (
          <Link href={`/${next.id}`} className="group rounded-lg border border-line p-3.5 text-right transition-colors hover:border-zinc-600">
            <span className="flex items-center justify-end gap-1.5 text-[12px] text-muted">{String(next.id).padStart(3, "0")} <ArrowRight className="h-3 w-3 transition-transform group-hover:translate-x-0.5" /></span>
            <span className="mt-1 block truncate text-sm text-zinc-200">{next.title}</span>
          </Link>
        ) : <span />}
      </nav>
    </article>
  );
}
