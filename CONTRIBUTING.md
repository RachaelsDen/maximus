# Contributing to Maximus-CBCS

Thanks for your interest in contributing! Here are a few things to keep in mind:

## 🛍️ Project Goals

* ✅ **Primary Target**: Modern Linux systems (x86\_64)
* ⚠️ **Future Support**: Windows (via MinGW or MSVC), DOS (via DOSBox/DOSEMU)
* ❌ **Legacy Platforms**: OS/2, native DOS, or other platforms are *not* officially supported but community patches are welcome if they don’t break core builds

## 💡 Contribution Guidelines

* Please keep code **clean and readable**; we are actively working to modernize the codebase.
* Pull requests should **not break Linux builds**.
* If adding platform support, isolate OS-specific code in separate files where possible.
* If replacing deprecated libraries or methods, please describe your changes in the PR description.

## 🛠️ Development

We use:

* Standard C (with GNU extensions OK for now)
* `make` for builds (modernization may come later)
* `cppcheck` and `clang-tidy` for static analysis (optional but helpful)

## 📁 Repo Structure

* `src/` – Core source code
* `unix/` – UNIX/Linux-specific code
* `windows/` – (placeholder)
* `docs/` – Documentation and quickstart files
* `etc/` – Example configuration and data layouts

## 📢 Communication

For now, open issues or PRs directly on [GitHub](https://github.com/RachaelsDen/maximus). Discussion is welcome!
