import Link from "next/link";
import { Footprints } from "lucide-react";

export function Header() {
  return (
    <header className="sticky top-0 z-20 border-b border-line/80 bg-bg/80 backdrop-blur">
      <div className="mx-auto flex h-14 max-w-5xl items-center justify-between px-5">
        <Link href="/" className="group flex items-center gap-2.5 text-[15px] font-semibold text-zinc-100">
          <Footprints className="h-[18px] w-[18px] text-accent transition-transform duration-300 group-hover:-rotate-12" />
          C++ Footguns
        </Link>
        <span className="hidden text-[13px] text-muted sm:block">interview gotchas, with runnable proof</span>
      </div>
    </header>
  );
}
