# Maximus CBCS (Classic BBS Revival)

This is a **modern revival** of the classic Maximus CBCS (Classic Bulletin Board System), originally written by **Scott Dudley**, **Peter Fitzsimmions**, and **David Nugent**, and later ported to UNIX by **Wes Garland** in 2002–2003.

This fork focuses on **cleaning up, modernizing, and restoring full functionality** under current Linux systems, with potential future support for Windows and DOS via cross-compilers.

> 📢 NOTE: This project is currently being refactored and modernized. The current state is unstable and should be considered experimental. Use at your own risk.

---

## 🧱 Goals

- Replace the legacy `make` system with modern **CMake**
- Clean up and modernize headers, defines, and dependencies
- Remove broken or obsolete platform-specific glue (e.g., OS/2 stubs)
- Restore functionality for Linux systems
- Reintroduce cross-platform support *after* Linux baseline is stable

---

## 📦 Requirements

- gcc / g++
- ncurses (for terminal UI)
- bison / flex
- git, cmake (for modern build system)
- Optional: `universal-ctags` for development

---

## 🚧 TODO

- [ ] Replace `configure` + Makefiles with a `CMakeLists.txt`
- [ ] Clean and modernize all `#include` usage and typedefs
- [ ] Remove broken cross-platform macros and dead stubs
- [ ] Restore `max` and `squish` build targets
- [ ] Validate and modernize `slib/`, `unix/include/`, etc.
- [ ] Rewrite or replace the QUICKSTART doc
- [ ] Build first working binary on Linux
- [ ] Optional: Reintroduce Windows support via MinGW
- [ ] Optional: Add Docker container for easy local builds

---

## 📂 Installation (in progress)

```bash
git clone https://github.com/RachaelsDen/maximus.git
cd maximus
mkdir build && cd build
cmake ..
make

