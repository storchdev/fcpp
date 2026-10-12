import { summaries } from "@/lib/data";
import { Catalog } from "@/components/Catalog";

export default function Home() {
  const items = summaries();
  return (
    <>
      <section className="mb-8 animate-rise">
        <h1 className="text-3xl font-semibold tracking-tight text-zinc-50">🦀 F*** C++</h1>
        <p className="mt-2 max-w-2xl text-[15px] leading-7 text-muted">
          {items.length} C++ gotchas. Each has code that breaks, the fix, and what g++ and clang++ did with it.
        </p>
      </section>
      <Catalog items={items} />
    </>
  );
}
