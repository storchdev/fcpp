import type { Metadata } from "next";
import "./globals.css";

export const metadata: Metadata = {
  title: { default: "F*** C++", template: "%s · F*** C++" },
  description: "182 C++ footguns with runnable bad code, the fix, and what g++ and clang++ did.",
};

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en">
      <body>
        <main className="mx-auto max-w-[1480px] px-5 pb-24 pt-12">{children}</main>
      </body>
    </html>
  );
}
