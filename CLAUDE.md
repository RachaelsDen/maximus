# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Maximus CBCS (Computerized Bulletin Board System) v3.03b for UNIX/Linux. This is a historic BBS software package originally developed for DOS/OS/2/Windows, ported to UNIX systems. The codebase includes:

- **Maximus BBS**: Full-featured bulletin board system
- **Squish**: FidoNet message tosser/scanner
- **MEX**: Maximus Extension language (scripting VM)
- **Utilities**: Various tools (SILT, MAID, MECCA compiler, etc.)

Released under GPL by Lanius Corporation and Scott J. Dudley. UNIX port by Wes Garland.

## Quick Start

```bash
# Prerequisites: GCC 14.2+, CMake 3.20+, Bison, ncurses library

# Configure and build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Install
sudo cmake --install build

# Compile configuration files
cmake --build build --target config_install
```

## Build System

### Prerequisites
- GCC 14.2+ (with G++)
- CMake 3.20+
- Bison 3.8.2+
- ncurses library (ncurses-dev)

### Common Build Commands

```bash
# Configure (default install: /usr/local)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Custom installation prefix
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/var/max

# Build everything
cmake --build build -j$(nproc)

# Build specific components
cmake --build build --target all_squish    # Squish only
cmake --build build --target all_maximus   # Maximus only
cmake --build build --target mex           # MEX compiler only

# Install
sudo cmake --install build

# Configuration targets
cmake --build build --target config_install  # Install + compile configs
cmake --build build --target reconfig        # Recompile configs only
cmake --build build --target create_userdb   # Create user database

# Clean build
rm -rf build/
```

### CMake Configuration Options

Set with `-D` flag during configuration:
- `CMAKE_INSTALL_PREFIX`: Installation root (default: /usr/local)
- `CMAKE_BUILD_TYPE`: Debug, Release, RelWithDebInfo, MinSizeRel
- `BUILD_MAXIMUS`: Build Maximus BBS (default: ON)
- `BUILD_SQUISH`: Build Squish tosser (default: ON)
- `BUILD_UTILITIES`: Build utilities (default: ON)

Installation directories (relative to CMAKE_INSTALL_PREFIX):
- Binaries: `bin/`
- Shared libraries: `lib/`
- Configuration files: `etc/`

### Out-of-Source Build Best Practices

The build system follows strict out-of-source build principles:
- All generated files go in `build/` directory
- Source tree remains clean during builds
- Generated header `compiler_details.h` is created in `build/slib/`
- All targets include `${CMAKE_BINARY_DIR}/slib` in their include paths

**When adding new targets**, ensure they include generated headers:
```cmake
target_include_directories(my_target PRIVATE
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/slib
    # ... other includes
)
```

## Architecture

### Module Organization

**Core Libraries** (built as shared objects):
- `slib/`: Shared utility library (string handling, file I/O, platform abstraction) → libmax.so
- `unix/`: UNIX compatibility layer (emulates OS/2/Windows APIs) → libcompat.so
- `msgapi/`: FidoNet message API (used by both Maximus and Squish) → libmsgapi.so
- `btree/`: B-tree C++ classes for indexed data → libmaxbt.so, libmaxdb.so
- `prot/`: File transfer protocols (Zmodem, Xmodem, Ymodem) → libxfer.so
- `mex/`: MEX scripting VM and runtime → libmexvm.so
- `comdll/`: Communications drivers → libcomm.so

**Main Programs**:
- `max/`: Maximus BBS main program → max (705KB executable)
- `squish/`: Squish message tosser → squish + 7 utilities
- `util/`: Configuration tools → maid, mecca, silt, fb, and 9 more

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
   - `maid`: Compiles language files (english.mad → english.lth/ltf)
   - `mecca`: Compiles menu/help files (*.mec → *.bbs)
   - `mex`: Compiles MEX scripts (*.mex → *.vm bytecode)

The `cmake --build build --target reconfig` target recompiles all control files after editing.

### Data Flow

1. **Maximus BBS**: Reads max.prm (compiled from max.ctl), presents menus (*.bbs files), executes MEX scripts, uses msgapi for message areas
2. **Squish**: Reads squish.cfg, processes FidoNet packets/bundles, uses msgapi to write/read message bases
3. **MEX VM**: Executes compiled .mex bytecode for BBS automation/customization

## Known Issues & Limitations

From the original README (as of v3.03b), with 2025 updates:

- **MEX VM**: ✅ FIXED - Now fully operational on GCC 14.2+ (see MEX VM Compiler Fix section)
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

## Modernization for GCC 14.2+ (2024-2025)

### Compilation Status

**Achievement**: 100% compilation success across entire codebase
- **max/**: 169/169 files compile successfully
- **util/**: 13/13 utilities compile successfully
- **squish/**: 8/8 programs compile successfully
- **Core libraries**: All 13 shared libraries build successfully

Modernized from GCC 2.72 (circa 2003) to GCC 14.2+ (2024) with modern Linux compatibility.

### Key Modernization Patterns

#### 1. Header Self-Containment
Headers must include their own dependencies and use proper include guards:

```c
#ifndef HEADER_NAME_H_INCLUDED
#define HEADER_NAME_H_INCLUDED

#include "required_types.h"  /* Include dependencies */
#include "compiler.h"        /* For near keyword, etc. */

/* Forward declarations for breaking circular dependencies */
typedef struct _somehandle *PSOMEHANDLE;

/* Function declarations */
int MyFunction(PSOMEHANDLE handle);

#endif /* HEADER_NAME_H_INCLUDED */
```

**Note**: Many older headers still use `__HEADER_H_DEFINED` style (POSIX-reserved). Future work should standardize to `HEADER_H_INCLUDED`.

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

#### 6. POSIX Compatibility

Modern Linux systems require feature test macros:

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

#### 7. Circular Library Dependencies

Resolve circular dependencies between shared libraries using linker groups:

```cmake
# In CMake - Use linker groups for circular dependencies
target_link_libraries(my_program
    -Wl,--start-group msgapi maxlib -Wl,--end-group
    compat ${CURSES_LIBRARIES}
)
```

This ensures libraries can reference symbols from each other, resolving undefined references.

### Common Issues and Solutions

| Issue | Solution |
|-------|----------|
| "unknown type name" in header | Add include or forward declaration: `typedef struct _foo *PFOO;` |
| Circular header dependency | Use forward declarations instead of #include |
| Undeclared language string | Add correct `MAX_LANG_*` section define |
| Undeclared version variable | Add `MAX_INCL_VER` define before includes |
| Incomplete type in struct | Fix include order - ensure type-defining header comes first |
| Implicit declaration of strdup | Add `_XOPEN_SOURCE 500` to compiler_unix.h |
| S_IREAD/S_IWRITE undeclared | Map to S_IRUSR/S_IWUSR in compiler_unix.h |
| Undefined reference to SquishHash | Use `-Wl,--start-group` / `-Wl,--end-group` in link order |
| Can't find compiler_details.h | Add `${CMAKE_BINARY_DIR}/slib` to include paths |
| Can't find english.lth | Add `${CMAKE_SOURCE_DIR}/lang` to include paths |

## Generated Files

### MEX Parser Files (DO NOT EDIT)

The repository includes pre-generated parser files for the MEX scripting language:
- `mex/mex_tab.c` - Generated by GNU Bison 3.8.2 (4000+ lines)
- `mex/mex_tab.h` - Generated by GNU Bison 3.8.2 (header file)

**IMPORTANT**: These files are auto-generated and should NEVER be edited manually.

**Only regenerate these files if:**
1. You modify the grammar source file `mex/mex_tab.y`
2. You update to a newer Bison version and need to regenerate for compatibility
3. The files become corrupted or out of sync

**Do NOT regenerate if:**
- You're only fixing compilation errors in other files
- You're making changes unrelated to the MEX scripting language
- You don't have Bison installed (the pre-generated files work fine)

**How to regenerate:**
```bash
cd mex
bison -d mex_tab.y  # Generates mex_tab.c and mex_tab.h
```

After regeneration:
1. Test the build to ensure no regressions
2. Verify the changes match your grammar modifications
3. Commit both .c and .h together with mex_tab.y changes

**Why checked into version control:**
- Allow building without requiring Bison
- Ensure consistent parser behavior across different Bison versions
- Speed up the build process (no generation step needed)

### MEX VM Compiler Fix (November 2025)

**Problem**: The MEX compiler failed to build with GCC 14.2 due to incompatible pointer type errors.

**Root Cause**: The 2007 Solaris yacc compatibility fix introduced intermediate grammar rules that took the address of temporary stack values (`&$1`), creating dangling pointers.

**Solution**: Changed the four `*ref()` functions to accept `CONSTTYPE` by value instead of by pointer:

**Before**:
```yacc
const_byte_p : T_CONSTBYTE { $$ = &$1; }  // ERROR: &$1 is dangling pointer
literal      : const_byte_p { $$=byteref($1); }
```

**After**:
```yacc
const_byte_p : T_CONSTBYTE { $$ = byteref($1); }  // Pass value directly
literal      : const_byte_p { $$=$1; }
```

**Status**: MEX VM compiler is now fully operational on modern GCC 14.2/Linux systems. Successfully compiles all 19 sample MEX scripts.

### Language Files (MAID-generated)

The repository includes generated language files:
- `lang/english.lth` - C header file with language string #defines (~45KB)
- `lang/english.ltf` - Binary language data file for runtime (~52KB)

These are generated from `lang/english.mad` by the **MAID** utility.

**Only regenerate these files if:**
1. You modify the language strings in `lang/english.mad`
2. You're adding new language strings to Maximus
3. The generated files are corrupted or out of sync

**How to regenerate:**
```bash
# Build MAID utility first
cd util
make maid  # Or: cmake --build build --target maid

# Generate language files (bootstrap)
cd ../lang
../util/maid english -p

# Full regeneration (requires max.prm from configuration)
# This is done as part of 'cmake --build build --target reconfig'
```

**Important**: The `.lth` file defines language string macros organized by sections (`MAX_LANG_global`, `MAX_LANG_sysop`, etc.). C source files use `#define MAX_LANG_<section>` to include only needed string definitions.

### Dependency Files

The repository includes empty `depend.mk` files in each directory. These are:
- **Empty by default** - Build system works without them
- **Auto-generated** - Run `make depend` to populate (if using Make system)
- **Optional** - Not required for CMake builds

## CMake Build System (November 2025)

### Migration Summary

The build system has been fully migrated from GNU Make to CMake 3.20+ for better cross-platform support, modern dependency management, and improved build performance.

**Key improvements:**
- **Out-of-source builds**: All build artifacts in `build/` directory (gitignored)
- **Modern CMake practices**: Target-based approach with proper dependency tracking
- **Parallel builds**: Full support for multi-core compilation
- **Component targets**: Can build Maximus, Squish, or utilities independently
- **Proper include management**: `${CMAKE_BINARY_DIR}` for generated headers

### Build Targets

**Component Targets:**
- `all_squish` - All Squish programs and libraries
- `all_maximus` - Maximus BBS and dependencies
- Individual executables: `max`, `squish`, `mex`, `maid`, `mecca`, `silt`, etc.

**Library Targets:**
- `maxlib` - libmax.so (core utility library)
- `msgapi` - libmsgapi.so (FidoNet message API)
- `compat` - libcompat.so (UNIX compatibility layer)
- `smserial` - libsmserial.so (serial communications)
- `mexvm` - libmexvm.so (MEX virtual machine)
- `maxbt` - libmaxbt.so (B-tree library)
- `maxdb` - libmaxdb.so (database library)
- `xfer` - libxfer.so (file transfer protocols)
- `comm` - libcomm.so (communications drivers)

**Configuration Targets:**
- `config_install` - Install and compile all configuration files
- `reconfig` - Recompile configs after editing .ctl/.mec files
- `create_userdb` - Create initial user database

### Build Performance

**Full clean build:**
- **13 shared libraries** built successfully
- **26 executables** compiled and linked
- **Parallel builds** supported (`-j` flag)

**Build time comparison:**
- Single-threaded: ~2-3 minutes
- Parallel (8 cores): ~30-45 seconds

### Adding New Source Files

When adding new source files or targets:

1. **Add to appropriate CMakeLists.txt** in the source directory
2. **Include generated headers** in target includes:
   ```cmake
   target_include_directories(my_target PRIVATE
       ${CMAKE_BINARY_DIR}/slib  # For generated files
       ${CMAKE_SOURCE_DIR}/slib
       # ... other includes
   )
   ```
3. **Link required libraries**:
   ```cmake
   target_link_libraries(my_target
       -Wl,--start-group msgapi maxlib -Wl,--end-group
       compat ${CURSES_LIBRARIES}
   )
   ```
4. **Test the build**:
   ```bash
   cmake --build build --target my_target
   ```

See `CMAKE_MIGRATION.md` for complete migration documentation.

## Known Warnings (Non-Fatal)

These warnings are expected and do not prevent compilation:

1. **Trigraph warnings**: `warning: trigraph ??/ ignored`
   - Appears in max_v.h:139 in URL string
   - Safe to ignore

2. **Packed attribute warnings**: `warning: 'packed' attribute ignored`
   - Appears in tracker headers (trackcom.h)
   - Safe to ignore (alignment handled differently on modern systems)

3. **DEBUGVM redefinition warnings**: `warning: "DEBUGVM" redefined`
   - Appears in mex/vm.h when compiling MEX VM files
   - Safe to ignore (defined both in CMakeLists.txt and header)

## Development Workflow

The codebase predates modern C/C++ standards (circa 2003, targeting C89/C++98). When making changes:

1. **Use appropriate platform defines** in #ifdef guards
2. **Maintain header self-containment** - headers should include their dependencies
3. **Use forward declarations** to break circular dependencies
4. **Follow POSIX compliance** - use modern constants and feature test macros
5. **Test with clean builds** - `rm -rf build && cmake -B build && cmake --build build`
6. **Verify all components** - test both Maximus and Squish after changes

### Testing Modernized Build

```bash
# Full codebase test
rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Verify executables
ls -lh build/max/max build/squish/squish build/mex/mex build/util/maid
```

## Future Modernization Tasks

Areas that may need attention:

1. **Header guard standardization**: ~90 headers use POSIX-reserved `__HEADER_H_DEFINED` style
2. **Big-endian support**: FidoNet packet handling may need fixes
3. **Serial I/O**: POSIX termios implementation incomplete
4. **Test suite**: Consider adding automated compilation tests
5. **Security**: Replace unsafe string functions (strcpy → snprintf/strlcpy)
