import type { Config } from "tailwindcss";
import typography from "@tailwindcss/typography";

const v = (name: string) => `rgb(var(--c-${name}) / <alpha-value>)`;

export default {
  content: ["./lib/**/*.{ts,tsx}", "./app/**/*.{ts,tsx}", "./components/**/*.{ts,tsx}"],
  theme: {
    extend: {
      colors: {
        white: v("white"),
        bg: v("bg"),
        panel: v("panel"),
        code: v("code"),
        line: v("line"),
        muted: v("muted"),
        accent: v("accent"),
        zinc: Object.fromEntries([50, 100, 200, 300, 400, 500, 600, 700].map((n) => [n, v(`zinc-${n}`)])),
        red: { 300: v("red") },
        orange: { 300: v("orange") },
        yellow: { 200: v("yellow") },
        sky: { 300: v("sky") },
        emerald: { 300: v("emerald") },
        violet: { 300: v("violet") },
        amber: { 300: v("amber") },
        rose: { 300: v("rose") },
      },
      fontFamily: {
        sans: ["Inter", "ui-sans-serif", "system-ui", "-apple-system", "Segoe UI", "sans-serif"],
        mono: ["ui-monospace", "SFMono-Regular", "JetBrains Mono", "Menlo", "monospace"],
      },
      keyframes: {
        rise: { from: { opacity: "0", transform: "translateY(6px)" }, to: { opacity: "1", transform: "none" } },
      },
      animation: { rise: "rise 360ms cubic-bezier(0.22, 1, 0.36, 1) both" },
    },
  },
  plugins: [typography],
} satisfies Config;
