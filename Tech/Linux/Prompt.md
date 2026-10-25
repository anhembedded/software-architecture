Create an Obsidian wiki note about "[TOPIC]" in Linux.

## Required Structure (Must Follow Exactly):

### 1. Title & Overview (2-3 sentences + mindmap)
- Start with "## Overview"
- Bold the topic name in first sentence
- Include a Mermaid mindmap showing key subtopics
- Provide alternative flowchart in case mindmap fails

### 2. "What is [Topic]?" Section
- Define clearly in 2-3 paragraphs
- Include a Mermaid diagram showing the concept visually
- Highlight the "key insight" in bold

### 3. "How It Works: The Mechanism" Section
- At least 2 Mermaid diagrams showing:
  - Sequence diagram of the operation/flow
  - State diagram showing lifecycle/states
- Explain step-by-step what the kernel does

### 4. "Similar Mechanisms (Same Level of Abstraction)" Section
- Mermaid graph showing related concepts
- Comparison table with columns:
  | Mechanism | Key Feature | Use Case | Linux Primitive |
- Explain what makes this topic unique vs alternatives

### 5. "Detection/Usage Commands" Section (if applicable)
- Quick diagnostic flow with actual bash commands
- Code blocks with explanatory comments
- Show both basic and advanced usage

### 6. "Common Mistakes, Pitfalls, and Misunderstandings" Section
- At least 5 specific mistakes with:
  - What people wrongly think/do
  - Why it's wrong
  - How to correctly diagnose/approach
- Use real command output examples showing the mistake vs reality

### 7. "How to Fix/Implement" Section (if applicable)
- Mermaid flowchart showing decision tree
- Cheat sheet table with: Symptom | Root Cause | Fix
- Immediate relief commands
- Long-term solutions

### 8. "Interview Quick-Reference" Callout Box
Use blockquote format:
> **🎯 Interview Quick-Reference**
> **One-liner:** [definition]
> **3 Must-Know Facts:** ...
> **Common Q&A:** Q: [...] A: [...]

### 9. "Real-World Troubleshooting Scenario"
- Brief incident description
- Step-by-step debug flow with actual commands
- Root cause revealed
- Lessons learned

### 10. "Important Notes" Table
| Concept | Description |
|---------|-------------|
| ... | ... |

### 11. "Related Notes" Section
- List internal links to other wiki notes
- Use [[double bracket]] Obsidian format

## Style Guidelines:

### Visual Requirements:
- Use Mermaid diagrams FREQUENTLY (aim for 5-8 per note)
- Types to use: mindmap, flowchart TD/LR, sequenceDiagram, stateDiagram-v2, graph
- Use color coding in flowcharts: red for problems, green for solutions
- Always provide text fallback if mindmap parse fails

### Technical Requirements:
- Include REAL bash commands with REAListic output
- Show both "wrong way" and "right way" examples
- Include kernel internals: mention task_struct, inode, VFS, etc.
- Reference /proc and /sys filesystem paths
- Mention specific system calls
- Include relevant kernel parameters (sysctl)

### Interview-Focused Elements:
- Anticipate "compare X vs Y" questions
- Anticipate "what happens when..." questions
- Anticipate "how would you debug..." questions
- Include gotchas that senior engineers should know

### Tone:
- Technical depth suitable for SRE/DevOps/Linux engineer
- Assume reader knows basic Linux but wants deep understanding
- Be opinionated about best practices
- Use "Key insight:" callouts for important realizations

## Anti-Patterns to Avoid:
- Don't just list commands without explaining WHY
- Don't skip the kernel's perspective
- Don't show only happy path—include error scenarios
- Don't make diagrams too simple (prefer detailed over minimal)
- Don't forget to mention what CAN'T be done (limitations)

Generate the complete note now.