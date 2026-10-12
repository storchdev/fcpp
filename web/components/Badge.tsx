import type { Classification } from "@/lib/data";
import { CLASS_INFO, DIFF } from "@/lib/style";

export function ClassBadge({ value }: { value: Classification }) {
  const i = CLASS_INFO[value];
  return (
    <span title={i.hint} className={`inline-flex h-5 items-center rounded border px-1.5 font-mono text-[11px] font-medium tracking-wide ${i.cls}`}>
      {i.label}
    </span>
  );
}

export function Difficulty({ value }: { value: string }) {
  const d = DIFF[value];
  return (
    <span className="inline-flex items-center gap-2 text-[13px] text-zinc-300">
      <span className={`h-2 w-2 rounded-full ${d.dot}`} />
      {d.label}
    </span>
  );
}
