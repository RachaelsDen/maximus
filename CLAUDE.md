# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Maximus CBCS (Computerized Bulletin Board System) v3.03b for UNIX/Linux. This is a historic BBS software package originally developed for DOS/OS/2/Windows, ported to UNIX systems. The codebase includes:

- **Maximus BBS**: Full-featured bulletin board system
- **Squish**: FidoNet message tosser/scanner
- **MEX**: Maximus Extension language (scripting VM)
- **Utilities**: Various tools (SILT, MAID, MECCA compiler, etc.)

Released under GPL by Lanius Corporation and Scott J. Dudley. UNIX port by Wes Garland.

## Build System

### Prerequisites
- GCC 2.72+ (with G++)
- GNU Make 3.79+
- Bison/Yacc
- curses library

### Configuration and Building

```bash
# Configure (default install: /var/max)
./configure
# Or with custom prefix:
./configure --prefix=/custom/path

# Build everything
make build

# Build only Squish
make squish

# Build only Maximus
make max

# Install everything (requires prior configure)
make install

# Install only Squish
make squish_install

# Install only Maximus
make max_install

# Install just configuration files
make config_install

# Recompile control/MECCA files after changes
make reconfig

# Clean build artifacts
make clean

# Clean everything including generated config
make distclean
```

### Build Variables
Edit `vars.mk` to customize paths, or pass `--prefix` to configure. Key paths:
- `PREFIX`: Installation root (default: /var/max)
- `BIN`: Binaries (PREFIX/bin)
- `LIB`: Shared libraries (PREFIX/lib)
- `ETC`: Configuration files (PREFIX/etc)

## Architecture

### Module Organization

The codebase uses a hierarchical directory structure with shared libraries and separate programs:

**Core Libraries** (built as shared objects):
- `slib/`: Shared utility library (string handling, file I/O, platform abstraction)
- `unix/`: UNIX compatibility layer (emulates OS/2/Windows APIs using POSIX/curses)
- `msgapi/`: FidoNet message API (used by both Maximus and Squish)
- `btree/`: B-tree C++ classes for indexed data
- `prot/`: File transfer protocols (Zmodem, Xmodem, Ymodem, etc.)
- `mex/`: MEX scripting VM and runtime
- `comdll/`: Communications drivers

**Main Programs**:
- `max/`: Maximus BBS main program
- `squish/`: Squish message tosser
- `util/`: Utilities (silt, maid, mecca, ansi2bbs, etc.)

**Configuration & Support**:
- `ctl/`: Sample control files (*.ctl)
- `install_tree/`: Template installation with configs
- `m/`: MEX script sources
- `lang/`: Language definition files

### Platform Abstraction

The code is a hybrid of OS/2, Windows NT, and UNIX code paths. Key platform defines:

- `UNIX`: UNIX-specific code
- `BSD`: BSD variants (FreeBSD, NetBSD, macOS, SunOS 4)
- `LINUX`: Linux-specific code
- `SYSV`: System V UNIX (Solaris, AIX, HP-UX)

The `unix/` directory provides compatibility shims:
- `libcompat.so`: Emulates OS/2 DosXXX() and Windows NT calls
- Curses-based terminal I/O replacing direct video memory access
- POSIX termios replacing DOS/OS2 serial I/O (incomplete as of 3.03b)

### Configuration System

Maximus uses compiled control files:
1. **Source files** (*.ctl, *.mec): Human-editable configuration/menus
2. **Compilation**: Tools compile sources to binary formats:
   - `silt`: Compiles max.ctl → max.prm
   - `maid`: Compiles language files (english.mad)
   - `mecca`: Compiles menu/help files (*.mec → *.bbs)
   - `mex`: Compiles MEX scripts (*.mex)

The `make reconfig` target recompiles all control files after editing.

### Data Flow

1. **Maximus BBS**: Reads max.prm (compiled from max.ctl), presents menus (*.bbs files), executes MEX scripts, uses msgapi for message areas
2. **Squish**: Reads squish.cfg, processes FidoNet packets/bundles, uses msgapi to write/read message bases
3. **MEX VM**: Executes compiled .mex bytecode for BBS automation/customization

## Known Issues & Limitations

From the original README (as of v3.03b):

- **MEX VM is broken**: Remove .mex files for now, the scripting engine has bugs
- **Big-endian support**: FidoNet packet handling may fail on big-endian systems
- **File locking**: Multinode systems may have race conditions
- **No serial support**: Telnet/network only (serial I/O not yet ported)
- **Minimal testing**: This is an early UNIX port with limited production use

When making changes, use the most appropriate platform scope in #ifdef guards. Prefer OS-native defines (e.g., `__FreeBSD__`) over custom ones when possible.

## Testing

No automated test suite exists. Test manually by:
1. Building and installing to a test PREFIX
2. Running `bin/max etc/max -c` to create initial user database
3. Testing utilities individually
4. For Squish: Use with FidoNet-compatible mailers (e.g., BinkD)

## Common Development Patterns

- **Makefiles**: Each directory has a Makefile that includes `$(SRC)/vars.mk`
- **Dependencies**: Auto-generated via `make depend` (uses makedepend or gcc -MM)
- **Shared libraries**: Built with `-fPIC`, linked dynamically at runtime
- **String handling**: Heavy use of custom string functions in slib/ (pre-dates modern C standards)

The codebase predates modern C/C++ standards (circa 2003, targeting C89/C++98).

## Modernization for GCC 14.2+ (2024-2025)

### Compilation Status

**Achievement**: 100% compilation success in `max/` directory (169/169 files)
- Modernized from GCC 2.72 (circa 2003) to GCC 14.2+ (2024)
- Fixed compatibility issues with modern Linux systems
- All files compile with only harmless trigraph warnings

### Key Modernization Patterns

#### 1. Header Self-Containment
Headers must include their own dependencies and use proper include guards:

```c
#ifndef __MY_HEADER_H_DEFINED
#define __MY_HEADER_H_DEFINED

#include "required_types.h"  /* Include dependencies */
#include "compiler.h"        /* For near keyword, etc. */

/* Forward declarations for breaking circular dependencies */
typedef struct _somehandle *PSOMEHANDLE;

/* Function declarations */
int MyFunction(PSOMEHANDLE handle);

#endif /* __MY_HEADER_H_DEFINED */
```

**Fixed headers**: api_brow.h, api_brop.h, node.h, m_attach.h, m_save.h, mh_tty.h, mh_graph.h, exec.h, m_for.h, m_browse.h, m_full.h, max_edit.h, events.h, v7.h, qwk.h, protod.h

#### 2. Forward Declarations for Circular Dependencies
Use forward declarations to break circular header dependencies:

```c
/* In msgapi.h - forward declare instead of including api_brow.h */
typedef struct _browse BROWSE;

/* In protod.h - forward declare SEARCH */
struct _search;
typedef struct _search SEARCH;

/* In many headers - forward declare MAH/PMAH */
typedef struct _mahandle *PMAH;
```

**Key circular dependency fix**: msgapi.h ↔ api_brow.h resolved by moving include from msgapi.h to forward declaration.

#### 3. Include Order Dependencies
Critical include order discovered:

```c
/* max_msg.h must come BEFORE headers using MAH type */
#include "max_msg.h"  /* Includes max.h which defines MAH */
#include "m_for.h"    /* Uses MAH type */

/* mm.h must come BEFORE node.h for struct _maxnode */
#include "mm.h"       /* Includes max.h with struct definitions */
#include "node.h"     /* Uses struct _maxnode */
```

**Affected files**: m_for.c, me_misc.c, m_save.c, node.c

#### 4. Language String Sections
Language strings in `lang/english.lth` are organized by sections. Files must define the appropriate `MAX_LANG_*` section:

```c
#define MAX_INCL_LANGLTH  /* Include language strings */
#define MAX_LANG_global   /* Global strings */
#define MAX_LANG_sysop    /* Sysop strings (e.g., cantopen) */
#define MAX_LANG_m_area   /* Message area strings (e.g., keep_to, mroute_sysop) */
#define MAX_LANG_track    /* Tracker strings (e.g., trk_got_actrack) */
#define MAX_LANG_max_bor  /* Border strings */
```

**Pattern**: Search `lang/english.lth` for the undefined string, note its line number, find the closest preceding section name.

#### 5. Version Information
Files needing version variables must define `MAX_INCL_VER`:

```c
#define MAX_INCL_VER      /* Include version information */
#include "max_vr.h"       /* For version, test, us_short, name, tear_ver, xfer_id */
```

**Fixed files**: max_fini.c, max_main.c, max_log.c, max_init.c, me_misc.c

#### 6. GCC 14.2 Strict Type Checking
Modern GCC requires explicit pointer type casts:

```c
/* Union vs union member pointers */
TmDate_to_DosDate(tim, &plfa->scDateAttached);  /* Not &...scDateAttached.ldate */

/* Ternary operator type mismatches */
*temp ? temp : (char *)usr.name  /* Cast to match pointer types */

/* Function return types */
doit ? Address(&msg.orig) : (byte *)blank_str  /* Both must be same type */
```

#### 7. Grammar File Generation
MEX scripting language requires generated parser files:

```bash
cd mex
bison -d mex_tab.y  # Generates mex_tab.c and mex_tab.h
```

These generated files are now included in the repository.

### Common Issues and Solutions

| Issue | Solution | Example |
|-------|----------|---------|
| "unknown type name" in header | Add include or forward declaration | `#include "msgapi.h"` or `typedef struct _foo *PFOO;` |
| Circular header dependency | Use forward declarations | Replace `#include` with `typedef struct _name TYPE;` |
| Undeclared language string | Add correct `MAX_LANG_*` section | Search english.lth, add matching define |
| Undeclared version variable | Add `MAX_INCL_VER` define | `#define MAX_INCL_VER` before includes |
| Incomplete type in struct | Fix include order | Ensure type-defining header comes first |
| Pointer type mismatch | Add explicit cast | `(char *)pointer` for type compatibility |
| Missing function declaration | Add protod.h include | `#include "protod.h"` |

### Build Prerequisites (Updated)

**Minimum Requirements**:
- GCC 14.2 or later (tested on Debian 12 / Linux 6.14)
- GNU Make 3.79+
- Bison/Yacc for grammar file generation
- curses library (ncurses-dev)

**Recommended**:
- Modern Linux distribution (Debian 12, Ubuntu 22.04+, etc.)
- GCC with C89/C99 support and modern strict type checking

### Known Warnings (Non-Fatal)

These warnings are expected and do not prevent compilation:

1. **Trigraph warnings**: `warning: trigraph ??/ ignored, use -trigraphs to enable`
   - Appears in max_v.h:139 in URL string
   - Safe to ignore (or could be fixed by escaping the `?` characters)

2. **Packed attribute warnings**: `warning: 'packed' attribute ignored [-Wattributes]`
   - Appears in tracker headers (trackcom.h)
   - Safe to ignore (alignment handled differently on modern systems)

### Testing Modernized Build

```bash
cd max
make clean
make -j$(nproc)  # Should compile all 169 files successfully
ls *.o | wc -l   # Should output 169
```

### Future Modernization Tasks

Areas that may need attention in future work:

1. **Squish directory**: Apply similar modernization patterns
2. **Utilities directory**: Modernize individual tools (silt, maid, mecca, etc.)
3. **MEX VM fixes**: Original README notes MEX is broken - needs investigation
4. **Big-endian support**: FidoNet packet handling may need fixes
5. **Serial I/O**: POSIX termios implementation incomplete
6. **Test suite**: Consider adding automated compilation tests

### Modernization History

- **2025-11**: Achieved 100% compilation in max/ directory (169/169 files)
  - Fixed circular dependencies
  - Added header self-containment
  - Resolved include order issues
  - Added missing language sections
  - Fixed GCC 14.2 type compatibility
- **2024-10**: Initial modernization started (commit 17bc88e)
  - Added vars.mk and vars_local.mk for build configuration
  - Fixed endianness detection conflicts
  - Improved POSIX-reserved identifier usage
