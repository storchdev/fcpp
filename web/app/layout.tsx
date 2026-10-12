import type { Metadata } from "next";
import "./globals.css";
import { ThemeToggle } from "@/components/ThemeToggle";

// Runs before paint so a saved or system light preference does not flash dark.
const THEME_INIT = `try{var t=localStorage.getItem("theme");if(t==="light")document.documentElement.classList.add("light")}catch(e){}`;

export const metadata: Metadata = {
  title: { default: "F*** C++", template: "%s · F*** C++" },
  description: "182 C++ footguns with runnable bad code, the fix, and what g++ and clang++ did.",
};

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en" suppressHydrationWarning>
      <head>
        <script dangerouslySetInnerHTML={{ __html: THEME_INIT }} />
      </head>
      <body>
        <ThemeToggle />
        <main className="mx-auto max-w-[1480px] px-5 pb-24 pt-12">{children}</main>
      </body>
    </html>
  );
}
