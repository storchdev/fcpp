import type { Metadata } from "next";
import "./globals.css";
import { Header } from "@/components/Header";

export const metadata: Metadata = {
  title: { default: "C++ Footguns", template: "%s · C++ Footguns" },
  description: "A catalog of C++ footguns, each with bad code, the fix, and what g++ and clang++ actually do.",
};

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en">
      <body>
        <Header />
        <main className="mx-auto max-w-5xl px-5 pb-24 pt-10">{children}</main>
      </body>
    </html>
  );
}
