import ReactMarkdown from "react-markdown";
import remarkGfm from "remark-gfm";
import rehypeHighlight from "rehype-highlight";

export function Markdown({ children, className = "" }: { children: string; className?: string }) {
  return (
    <div className={`prose max-w-none prose-p:leading-7 prose-headings:font-semibold ${className}`}>
      <ReactMarkdown remarkPlugins={[remarkGfm]} rehypePlugins={[[rehypeHighlight, { detect: false }]]}>
        {children}
      </ReactMarkdown>
    </div>
  );
}

/** Highlighted source file. The fence is longer than any backtick run in the code. */
export function CodeBlock({ code, lang }: { code: string; lang: string }) {
  const longest = Math.max(2, ...(code.match(/`+/g) ?? []).map((s) => s.length));
  const fence = "`".repeat(longest + 1);
  return (
    <div className="code">
      <ReactMarkdown rehypePlugins={[[rehypeHighlight, { detect: false }]]}>
        {`${fence}${lang}\n${code.replace(/\n$/, "")}\n${fence}`}
      </ReactMarkdown>
    </div>
  );
}
