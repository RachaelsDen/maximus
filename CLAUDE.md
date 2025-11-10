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

**Achievement**: 100% compilation success across entire codebase
- **max/**: 169/169 files compile successfully
- **util/**: 13/13 utilities compile successfully
  - maid, mecca, accem, ansi2bbs, ansi2mec, scanbld, cvtusr, editcall, mr, fixlr, setlr, fb, silt
- **squish/**: 8/8 programs compile successfully
  - squish, sqfix, sqpack, sqconv, sqinfo, sqset, sstat, sqreidx
- **Core libraries**: All 4 shared libraries build successfully
  - libmax.so (141,672 bytes)
  - libmsgapi.so (80,256 bytes)
  - libcompat.so (28,672 bytes)
  - libsmserial.so (15,992 bytes)

Modernized from GCC 2.72 (circa 2003) to GCC 14.2+ (2024) with modern Linux compatibility. All files compile with only harmless trigraph warnings.

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

#### 8. POSIX Compatibility
Modern Linux systems require feature test macros and updated permission constants:

```c
/* In slib/compiler_unix.h - Enable POSIX extensions */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

/* Map legacy BSD permission constants to modern POSIX */
#ifndef S_IREAD
#define S_IREAD S_IRUSR
#endif
#ifndef S_IWRITE
#define S_IWRITE S_IWUSR
#endif
```

**Required for**: strdup(), S_IREAD/S_IWRITE usage in util/ and max/ directories

#### 9. Circular Library Dependencies
Resolve circular dependencies between shared libraries by duplicating library references in link order:

```makefile
# In vars.mk - libmsgapi provides SquishHash needed by libmax
LOADLIBES = $(EXTRA_LOADLIBES) -lmax $(EXTRA_LOADLIBES) -lcompat -lcurses
```

This ensures libmsgapi links both before and after libmax, resolving undefined references.

#### 10. Utility-Specific Header Fixes
Several utility headers required self-containment fixes:

**util/mecca.h** - MECCA compiler header:
```c
#include <stdio.h>   /* For FILE type */
#include <stddef.h>  /* For NULL */
#include "stamp.h"   /* For union stamp_combo */
#include "typedefs.h" /* For word type */
```

**util/cvtusr.h** - User file converter:
```c
#include "typedefs.h"  /* For word and byte types */
#include "max_u.h"     /* For struct _usr */
/* Add missing function declarations */
void Convert_Max200(void);
void Reverse_Max200(void);
void Convert_Lread(void);
void Reverse_Max300(void);
```

**util/s_heap.h** - SILT heap manager:
```c
#include "typedefs.h"  /* For word type */
/* Forward declare zstr (defined in max.h as typedef word zstr) */
typedef word zstr;
```

**util/silt.h** - SILT main header:
```c
#include "max.h"       /* For FAREA, MAREA, struct _ovride, constants */
#include "s_heap.h"
```

**max/scanbld.h** - Message scan builder:
```c
#include "typedefs.h"  /* For word type */
```

#### 11. Build System Include Paths
Some source files require additional include paths for language files:

```makefile
# In util/Makefile - for files using language strings
max2priv.o: CPPFLAGS += -I../lang
l_attach.o: CPPFLAGS += -I../lang
```

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
| Implicit declaration of strdup | Add `_XOPEN_SOURCE 500` to compiler_unix.h | See Pattern #8 - POSIX Compatibility |
| S_IREAD/S_IWRITE undeclared | Map to S_IRUSR/S_IWUSR in compiler_unix.h | See Pattern #8 - POSIX Compatibility |
| Undefined reference to SquishHash | Fix library link order in vars.mk | See Pattern #9 - Circular Library Dependencies |
| FILE/NULL type unknown in util header | Add stdio.h/stddef.h to header | See Pattern #10 - mecca.h example |
| struct _usr incompatible pointer | Include max_u.h for complete definition | See Pattern #10 - cvtusr.h example |
| zstr type unknown in s_heap.h | Forward declare as `typedef word zstr;` | See Pattern #10 - s_heap.h example |
| Can't find english.lth | Add `-I../lang` to CPPFLAGS | See Pattern #11 - Build System Include Paths |

### Build Prerequisites (Updated)

**Minimum Requirements**:
- GCC 14.2 or later (tested on Debian 12 / Linux 6.14)
- GNU Make 3.79+
- Bison 3.8.2+ for MEX grammar file generation
- curses library (ncurses-dev)

**Recommended**:
- Modern Linux distribution (Debian 12, Ubuntu 22.04+, etc.)
- GCC with C89/C99 support and modern strict type checking

### Generated Files

The repository includes pre-generated parser files for the MEX scripting language:
- `mex/mex_tab.c` - Generated by GNU Bison 3.8.2 (4000+ lines)
- `mex/mex_tab.h` - Generated by GNU Bison 3.8.2 (header file)

**IMPORTANT**: These files are auto-generated and should NEVER be edited manually. They include a prominent "DO NOT EDIT" header explaining their purpose.

#### When to Regenerate

**Only regenerate these files if:**
1. You modify the grammar source file `mex/mex_tab.y`
2. You update to a newer Bison version and need to regenerate for compatibility
3. The files become corrupted or out of sync

**Do NOT regenerate if:**
- You're only fixing compilation errors in other files
- You're making changes unrelated to the MEX scripting language
- You don't have Bison installed (the pre-generated files work fine)

#### How to Regenerate

```bash
cd mex
bison -d mex_tab.y  # Generates mex_tab.c and mex_tab.h
```

After regeneration:
1. **Test the build**: Compile the entire project to ensure no regressions
2. **Verify the changes**: Review the diff to ensure changes match your grammar modifications
3. **Commit both files**: Always commit both .c and .h together with mex_tab.y changes

#### Why These Are Checked Into Version Control

The generated files are included in version control to:
- Allow building without requiring Bison (simplifies build dependencies)
- Ensure consistent parser behavior across different Bison versions
- Speed up the build process (no generation step needed)

**Requirements**: If regeneration is needed, requires Bison 3.8.2 or later.

#### Language Files (MAID-generated)

The repository includes generated language files for Maximus's multi-language support:
- `lang/english.lth` - C header file with language string #defines (~45KB)
- `lang/english.ltf` - Binary language data file for runtime (~52KB)

These are generated from `lang/english.mad` (the source language definition file) by the **MAID** utility.

**Source files**:
- `lang/english.mad` - Master language definition (111KB binary format)

**Generated files** (DO NOT EDIT):
- `lang/english.lth` - Header with `#define` macros for language strings (line 1: "generated by MAID")
- `lang/english.ltf` - Binary language data loaded at runtime
- `lang/english.mh` - Message header file

**When to Regenerate**:

**Only regenerate these files if:**
1. You modify the language strings in `lang/english.mad`
2. You're adding new language strings to Maximus
3. The generated files are corrupted or out of sync
4. You're porting to a new platform and need fresh generation

**Do NOT regenerate if:**
- You're only fixing compilation errors (the existing files work fine)
- You're working on code unrelated to language strings
- You don't have a working MAID binary (the pre-generated files are sufficient)

**How to Regenerate**:

The MAID tool must be built first from `util/maid.c`:

```bash
# Build MAID utility
cd util
make maid

# Generate language files (bootstrap - creates .ltf and .lth)
cd ../lang
../util/maid english -p

# Full regeneration (requires max.prm from configuration)
# This is done as part of 'make reconfig'
../util/maid english -d -s -p/path/to/etc/max
```

**Integration with Build System**:

The `make reconfig` target (after `make install`) runs a two-pass language compilation:
1. **Pass one**: Bootstrap compile (`maid english -p`) to generate initial .lth/.ltf
2. **Pass two**: Full compile (`maid english -d -s -p$(PREFIX)/etc/max`) with complete symbol table

**Important Notes**:
- The `.lth` file defines language string macros organized by sections (`MAX_LANG_global`, `MAX_LANG_sysop`, etc.)
- C source files use `#define MAX_LANG_<section>` to include only needed string definitions
- Regeneration updates the header comment to show "generated by MAID v3.03"
- The `.ltf` binary format may be endian-sensitive

**History**:
- Commit ec0d058: Regenerated english.lth/.ltf to update from MAID v3.01 to v3.03
  - Fixed path style from Windows (`..\\LANG\\`) to Unix (`../lang/`)
  - Expanded english.ltf from 216 bytes (stub) to 52KB (full)

### Dependency Files

The repository includes empty `depend.mk` files in each directory:
- `btree/depend.mk`
- `max/depend.mk`
- `msgapi/depend.mk`
- `slib/depend.mk`
- `squish/depend.mk`
- `unix/depend.mk`
- `util/depend.mk`

These are placeholder files for automatic header dependency tracking. They are:
- **Empty by default** - The build system works without populated dependency files
- **Auto-generated** - Run `make depend` to populate them with header dependencies
- **Cleaned automatically** - The `make clean` target removes them
- **Optional** - Not required for successful compilation

The files exist in version control as placeholders to prevent errors if Makefiles attempt to include them.

### Known Warnings (Non-Fatal)

These warnings are expected and do not prevent compilation:

1. **Trigraph warnings**: `warning: trigraph ??/ ignored, use -trigraphs to enable`
   - Appears in max_v.h:139 in URL string
   - Safe to ignore (or could be fixed by escaping the `?` characters)

2. **Packed attribute warnings**: `warning: 'packed' attribute ignored [-Wattributes]`
   - Appears in tracker headers (trackcom.h)
   - Safe to ignore (alignment handled differently on modern systems)

### Testing Modernized Build

**Full codebase test:**
```bash
cd /home/kgoodwin/maximus
make clean
make build  # Should build all libraries, utilities, and programs
```

**Individual directory tests:**
```bash
# Test max/ directory (169 files)
cd max
make clean && make -j$(nproc)
ls *.o | wc -l   # Should output 169

# Test util/ directory (13 programs)
cd util
make clean && make -j$(nproc)
ls maid mecca silt fb  # Should exist

# Test squish/ directory (8 programs)
cd squish
make clean && make -j$(nproc)
ls squish sqpack sqfix  # Should exist

# Test core libraries
cd slib && make clean && make
cd msgapi && make clean && make
cd unix && make clean && make
```

### Future Modernization Tasks

Areas that may need attention in future work:

1. **Header guard standardization**: Inconsistent header guard styles across the codebase
   - **Current state**: ~90 headers use `__HEADER_H_DEFINED` (POSIX-reserved due to leading `__`)
   - **Compliant style**: Only ~24 headers use `HEADER_H_INCLUDED` (no reserved identifiers)
   - **History**: Commit 2fe1c07 fixed 21 headers from `_HEADER_H` → `HEADER_H_INCLUDED` pattern
   - **Reserved identifiers**: Per POSIX 2.2.2, names starting with `__` or `_[A-Z]` are reserved for implementation
   - **Recommendation**: Standardize all remaining headers to `HEADER_H_INCLUDED` style
   - **Examples to fix**: max/api_brow.h:20, and 89+ other headers across max/, msgapi/, squish/, etc.
   - **Note**: This is a low-priority cleanup task - the current guards work but violate POSIX namespace rules

2. **MEX VM fixes**: Original README notes MEX is broken - needs investigation
3. **Big-endian support**: FidoNet packet handling may need fixes
4. **Serial I/O**: POSIX termios implementation incomplete
5. **Test suite**: Consider adding automated compilation tests

### Modernization History

- **2025-11**: Achieved 100% compilation success across entire codebase
  - **max/ directory** (169/169 files - initial focus)
    - Fixed circular dependencies (msgapi.h ↔ api_brow.h)
    - Added header self-containment (16+ headers fixed)
    - Resolved include order issues
    - Added missing language sections
    - Fixed GCC 14.2 type compatibility issues
  - **util/ directory** (13/13 programs - commits ceaa88a, 5e3b5a8)
    - Fixed mecca.h header self-containment (FILE, NULL, word, union stamp_combo types)
    - Fixed cvtusr.h (added max_u.h for struct _usr, added missing function declarations)
    - Fixed scanbld.h (added typedefs.h for word type)
    - Fixed s_heap.h (forward declared zstr type)
    - Fixed silt.h (added max.h for FAREA, MAREA, struct _ovride)
    - Added POSIX compatibility (S_IREAD/S_IWRITE, _XOPEN_SOURCE 500 for strdup)
    - Fixed library link order for SquishHash circular dependency
    - Added language include path for l_attach.o
  - **squish/ directory** (8/8 programs - commit ceaa88a)
    - All squish utilities compile successfully with existing patterns
  - **Core libraries** (4/4 shared libraries)
    - libmax.so, libmsgapi.so, libcompat.so, libsmserial.so all build successfully
  - **Full clean build test**: Validated entire codebase compiles from clean state
  - **Git hygiene**: Removed 9 accidentally tracked binaries, created comprehensive .gitignore

- **2024-10**: Initial modernization started (commit 17bc88e)
  - Added vars.mk and vars_local.mk for build configuration
  - Fixed endianness detection conflicts
  - Improved POSIX-reserved identifier usage
