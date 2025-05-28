
---

#### ✅ `HACKING.md`
```markdown
# HACKING Maximus-CBCS

_Last updated: June 5, 2003 by Wes Garland_  
_Formatted and modernized for GitHub in 2025._

---

## Overview

The code base is a mixture of OS/2, Windows, and UNIX implementations, with a preference toward UNIX-style and portable implementations where feasible.

Where possible:
- Assembly code was removed.
- OS/2 and Windows features were emulated using **`curses`** and UNIX-native APIs.

## Platform-Specific Macros

Use appropriate compiler flags for conditional compilation:

| Macro   | Description |
|---------|-------------|
| `UNIX`  | General UNIX-specific code |
| `BSD`   | BSD variants: FreeBSD, NetBSD, OpenBSD, macOS |
| `LINUX` | Linux systems |
| `SYSV`  | System V UNIX: Solaris, AIX, HP/UX |

Where possible, prefer OS-native preprocessor defines such as `__FreeBSD__`, `__linux__`, etc.

## Contributing

When adding support for a new platform, isolate changes with compiler `#define`s and clearly document your changes.

Please do not submit patches that mix cleanup and functionality changes.

---

Feel free to file Issues or submit Pull Requests on GitHub if you'd like to help clean or modernize this codebase.
