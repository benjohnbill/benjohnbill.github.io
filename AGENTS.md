---
scope: This repository and its descendants
role: Codex bridge to the shared Jungle workspace policy
updated: 2026-10-14
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
  (`note`, `deck`, `repo`, `lesson`), `data-src`, and an absolute `href`. CSS
  makes each card a row, and the visible type label comes from `data-kind`, not
  `.b`. `lesson` (label 레슨) marks a page made by the `/teach` skill: a lesson
  or its reference page. Its original is under `weekNN/lab/teach/publish/`,
  built by `publish/build.py` there.
  A team deck also has `data-scope="team"`. A deck without it counts as
  personal in the `유형` view.
  Card shape: `skills/jungle-deck/reference/local-template.md`, "Built-in
  card". Cards must stay in the HTML, because `jungle-deck` `publish.py` and
  `jungle-week-init` read that markup; the script only adds the sidebar, the
  repository table, and clones for the `주제` and `유형` views.
- **Project hubs.** A week group can hold one hub (`<div class="hub">`)
  for each project, labeled `모음`. Make a hub when a project gets its second
  note. A hub has a `<button class="hub-head">` and a body with one
  `<div class="phase">` for each phase (`공통`, `Phase 1`, …). Each phase has an
  `<h3 class="ph">` and a `.cards` block. The cards in a hub are normal cards:
  the same attributes, the same shape, and the same `data-src`. Put a new
  page of that project in its phase's `.cards` block, not directly in the
  week's `.cards`. A card that belongs to no single project (for example a team
  meeting deck) stays outside the hubs. The script starts each hub collapsed.
  A hub that the reader opened stays open in that tab (`sessionStorage`). The
  `주제` and `유형` views show the hub cards as normal rows. Without JavaScript,
  the hubs show open. Reference: `#hub-mini-react` in `index.html`.
- **Skill cards.** The `자동화 스킬` group (`id="skills"`) sits below `#list`,
  outside it. The script shows the group only in the `유형` view. Without
  JavaScript it shows below the weeks. Its cards link to skill repositories,
  with `data-kind="repo"`, `data-src`, and an absolute `href`. They have no
  `data-week` and no `data-topic`.
- **Week headings.** `N주차 · <week name>`, wrapped in
  `<a class="wk-repo" href="https://github.com/<owner>/<repo>">` pointing at
  that week's repository (the `origin` of `~/dev/krafton-jungle/weekNN/`),
  plus a `WIL →` link to that week's velog post, added when the post exists
  (`jungle-week-init` asks for it at the start of the next week).
- **Shared CSS.** Every written page (the index and the notes; not the decks)
  links `https://benjohnbill.github.io/assets/site.css` by absolute URL, so an
  original opened from disk gets it too. It holds the color tokens (light and
  dark, by `prefers-color-scheme` only), the three font slots (`--font-head`,
  `--font-body`, `--font-code`; meta text uses the code slot) and the base
  elements. A page keeps only its own shapes and page-only tokens.
  Box rules for a page on this base (decided 2026-10-08):
  1. Outer boxes (cards, panels, tables) get `1px solid var(--line)` and no
     fill. `--surface` equals `--bg`, so a box told apart by fill alone has
     no edge.
  2. Fill (`--surface-2`) goes one level in only: code, bins, highlighted
     rows. Never put fill on fill.
  3. Color marks meaning only. Page accent tokens and their `-soft` fills
     stay as they are.
  4. No shadows and no large corner radii on outer boxes. One line is the
     only surface cue.
  5. Each note starts its `.wrap` (or `.page`) with
     `<a class="home" href="https://benjohnbill.github.io/">← 학습 기록</a>`.
  A page with its own token names keeps the names and points them at site
  tokens (`--rule:var(--line)`, `--paper:var(--bg)`). Dark `--line`
  (`#2A2A2A`) is shared with the index cards: ask before raising it.
- **Design reference.** Before you write or restyle a note, read
  [DESIGN.md](DESIGN.md). It is a reference of formats to copy (type, cards,
  fold cards, heading voice), not a full spec. Its "Keep" items are firm;
  "Default" items change only with a written reason; "Pattern" items are
  optional. Pages made before 2026-10-14 follow it only when edited.
- **Moved pages.** `study/c-workshop/` and `study/malloc-lab/` hold redirect
  stubs for links shared before 2026-10-08. Do not delete them or add pages
  there.
