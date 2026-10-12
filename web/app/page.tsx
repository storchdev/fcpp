import { summaries } from "@/lib/data";
import { Catalog } from "@/components/Catalog";

export default function Home() {
  const items = summaries();
  return (
    <>
      <section className="mb-8 flex animate-rise items-stretch justify-between gap-6">
        <div>
          <h1 className="text-3xl font-semibold tracking-tight text-zinc-50">F*** C++</h1>
          <p className="mt-2 max-w-2xl text-[15px] leading-7 text-muted">
            {items.length} C++ gotchas. Each has code that breaks, the fix, and what g++ and clang++ did with it.
          </p>
        </div>
        <span aria-hidden className="flex select-none items-center text-[4.25rem] leading-none">
          🦀
        </span>
      </section>
      <Catalog items={items} />
    </>
  );
}
