# AI Coding Instructions for z88dk-sp1

## Project Overview

This is a **ZX Spectrum game development tutorial project** using the z88dk compiler and SP1 graphics engine. The project teaches game development fundamentals through 6 progressive modules, from initialization to advanced memory management and parallax effects.

- **Target:** ZX Spectrum (8-bit retro platform)
- **Language:** C + Z80 Assembly (via z88dk/SDCC)
- **Graphics Engine:** SP1 (differential update sprite engine)
- **Build System:** Makefile-based (z88dk compiler toolchain)

## Architecture & Components

### Core Structure

```
src/
├── main.c              # Menu system - routes to examples via switch statement
├── z88dk_headers.h     # Centralized header includes (z80, arch/zx, sp1)
└── modules/
    ├── modules.h       # Example function declarations (run_example1-6)
    ├── common.c        # Shared utilities (wait_for_intro_key callback)
    ├── module1.c       # SP1 initialization & differential updates
    ├── module2.c       # Background tiles & UDGs (User-Defined Graphics)
    └── module3-6.c     # (Planned: sprites, game logic, memory, parallax)
```

### Data Flow

1. **Menu Loop** (main.c) → Listen for numeric key input
2. **Example Dispatch** → Call corresponding `run_exampleN()` function
3. **Example Logic** → Initialize SP1, manage screen updates, wait for INTRO key
4. **Return to Menu** → `wait_for_intro_key()` callback polls sp1_UpdateNow()

## Critical Development Patterns

### Build & Compilation

- **Command:** `make COMPILER=sdcc CLIB=sdcc_iy CRT=1` (or use VS Code Build task)
- **Key Pragma Configuration** (zpragma.inc):
  - `CRT_ORG_CODE = 25000` - Code origin (must be high enough for sprite allocation)
  - `REGISTER_SP = 0xd000` - Stack pointer for SP1 engine
  - `CLIB_BALLOC_TABLE_SIZE = 1` - **MANDATORY** for SP1 dynamic sprite allocation
  - Stack size: 128 bytes (minimal for retro platform)
- **Output:** `bin/z88dk-sp1.sna` (emulator snapshot) + `.tap` (tape format)

### SP1 Graphics Engine Pattern

The SP1 library uses **differential updating**: only redraws changed 8x8 character cells ("dirty cells").

**Standard SP1 Initialization Sequence:**

```c
// 1. Mark full screen as "dirty"
struct sp1_Rect full_screen = {0, 0, 32, 24};

// 2. Initialize SP1 with flags
sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
               INK_WHITE | PAPER_BLACK, ' ');

// 3. Invalidate screen to force first draw
sp1_Invalidate(&full_screen);

// 4. Main loop - ALWAYS call sp1_UpdateNow()
while (1) {
    sp1_UpdateNow();  // Process dirty cell list
}
```

### Module Documentation Pattern

Each module has a corresponding `.md` file in `doc/`:

- **modulo-1.md** - Initialization (references functions with `[sp1_Initialize](z88dk-sp1.md#sp1_initialize)` anchor links)
- **modulo-2.md** - Background tiles (same link pattern)
- **Indice.md** - Central index linking all modules
- **z88dk-sp1.md** - (TBD) Reference documentation with anchor sections

When documenting new modules, follow the **link format**: `[function_name](z88dk-sp1.md#function_name_anchor)`

## Key Conventions & Gotchas

### Memory Constraints

- ZX Spectrum has only **48KB RAM** (or 128KB on extended models)
- Avoid `malloc()` / dynamic allocation except via SP1's internal allocator
- Use global variables and `static` declarations for efficiency
- Stack is tiny (128 bytes) - no deep recursion

### Interrupts & Timing

- SP1 disables interrupts at startup (`CRT_ENABLE_EIDI = 0x1`)
- Use **interrupt mode 2 (IM2)** for consistent 50Hz game loop (future modules)
- No `printf()` heavy lifting in game loops (impacts timing)

### Color Limitations (ZX Spectrum Attributes)

- **Attribute clash:** Colors are defined per 8x8 cell, not per pixel
- **UDGs (User-Defined Graphics):** Custom 8x8 character graphics registered via `sp1_TileEntry(char_code, byte_array)`
- **Bright bit:** Enable/disable brightness per cell: `INK_CYAN | PAPER_BLACK | BRIGHT`

### Callback Pattern

Polling functions receive a `__z88dk_fastcall` function pointer for tight loops:

```c
void wait_for_intro_key(void (*callback)(void)) __z88dk_fastcall;
// Called from modules to wait for INTRO key while running callback each frame
```

## Build & Debugging Commands

| Task              | Command                                                                                      |
| ----------------- | -------------------------------------------------------------------------------------------- |
| **Build**         | `make COMPILER=sdcc CLIB=sdcc_iy CRT=1 CREATE_SNA=true CREATE_TAP=true` (VS Code Build task) |
| **Clean**         | `make clean_all` (removes bin/ obj/ artifacts)                                               |
| **Emulator**      | Output `.sna` snapshot runs in any ZX Spectrum emulator (Fuse, ZEsarUX, etc.)                |
| **Assembly View** | `.lis` files in `bin/` and `src/` show compiled Z80 ASM for each module                      |

## When Adding New Examples (Modules 3-6)

1. **Create** `src/modules/moduleN.c` with `void run_exampleN(void)` function
2. **Declare** function in `src/modules/modules.h`
3. **Add Case** in `main.c` switch statement routing to new example
4. **Document** in `doc/modulo-N.md` with function links to z88dk-sp1.md
5. **Link** from `doc/Indice.md` central index
6. **Initialize SP1** following the pattern above (mark screen dirty, call `sp1_UpdateNow()` in loop)

## Resources & References

- **z88dk Documentation:** https://github.com/z88dk/z88dk (compiler, libraries, pragmas)
- **SP1 Library:** Differential sprite engine - see `zpragma.inc` stack requirements
- **ZX Spectrum Technical:** 48KB memory model, attribute system, interrupt modes
- **Emulators:** Fuse, ZEsarUX, or online (js99er.net for quick testing)

---

**Generated:** February 2026 | **Last Updated:** For modules 1-2 (initialization, tiles)
