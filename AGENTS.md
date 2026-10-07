---
scope: This repository and its descendants
role: Codex bridge to the shared Jungle workspace policy
updated: 2026-09-22
---

# Codex instructions

Before work, read [the workspace instructions](../AGENTS.md). Resolve the link
from this file's directory, not the shell's working directory. Read each source
only once, then read any applicable local instructions for the target files.

This is a support project, outside the week exercise tutor mode. If this
repository is moved outside the workspace, report the missing shared file and
use the available local instructions; do not invent the missing policy.

## Site rules

Hand-written static HTML served from `main` by GitHub Pages. No build step.

- **Paths.** A page published here lives at `study/weekNN/<slug>.html`
  (`slug` in English kebab-case). Weeks 2–4 live in other repositories
  (`SW-AI-W02-03`, `SW-AI-C`) and are only linked from the index.
- **Copies.** Every file under `study/weekNN/` is a byte copy of an original
  elsewhere under `~/dev/krafton-jungle/`. Edit the original, then copy it
  here again; never edit the copy. `rg data-src index.html` lists each
  card's original.
- **Cards.** One `<a class="card">` per page in `index.html`, inside its
  week's group, with `data-week`, `data-topic` (exactly one: 알고리즘,
  시스템, C언어; a new topic also needs a title-color rule), `data-kind`
  (`note`, `deck`, `repo`), `data-src`, and an absolute `href`. Card shape:
  `skills/jungle-deck/reference/local-template.md`, "Built-in card".
- **Week headings.** `N주차 · <week name>` plus a `WIL →` link to that
  week's velog post, added when the post exists (`jungle-week-init` asks for
  it at the start of the next week).
- **Moved pages.** `study/c-workshop/` and `study/malloc-lab/` hold redirect
  stubs for links shared before 2026-10-08. Do not delete them or add pages
  there.
