/** @type {import('next').NextConfig} */
export default {
  output: "standalone",
  reactStrictMode: true,
  distDir: process.env.NEXT_DIST_DIR || ".next",
  // Set to "/fcpp" when served under hudsonshi.com/fcpp; empty for local dev.
  basePath: process.env.NEXT_BASE_PATH || "",
};
