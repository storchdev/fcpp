/** @type {import('next').NextConfig} */
export default { output: "standalone", reactStrictMode: true, distDir: process.env.NEXT_DIST_DIR || ".next" };
