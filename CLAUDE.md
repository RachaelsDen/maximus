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
