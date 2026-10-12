import type { Classification } from "@/lib/data";
import { CLASS_INFO, DIFF } from "@/lib/style";

export function ClassBadge({ value }: { value: Classification }) {
  const i = CLASS_INFO[value];
  return (
    <span title={i.hint} className={`font-mono text-[12px] font-medium tracking-wide ${i.cls}`}>
      {i.label}
    </span>
  );
}

export function Difficulty({ value }: { value: string }) {
  const d = DIFF[value];
  return <span className={`text-[13px] ${d.cls}`}>{d.label}</span>;
}
