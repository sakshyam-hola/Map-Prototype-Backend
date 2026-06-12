// =============================================================================
//  main.cpp — PathFinder entry point
//
//  Build with ConsoleUI  (default / CI):
//      make
//
//  Build with CustomUI  (UI designer build):
//      make CUSTOM_UI=1
//      or:  g++ … -DUSE_CUSTOM_UI …
//
//  The two builds share 100 % of the backend; only the UIInterface differs.
// =============================================================================

#include "include/PathFinder.h"
#include "include/UIInterface.h"   // ConsoleUI
#include "include/CustomUI.h"      // CustomUI stub — replace when ready

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    // ── Select UI ─────────────────────────────────────────────────────────────
    std::unique_ptr<UIInterface> ui;

#ifdef USE_CUSTOM_UI
    // =========================================================================
    //  UI DESIGNER BUILD
    //  Swap ConsoleUI for CustomUI once the designer's implementation is ready.
    //  All backend calls are identical — no other changes needed.
    // =========================================================================
    std::cout << "[PathFinder] Starting with CustomUI\n";
    ui = std::make_unique<CustomUI>();
#else
    // =========================================================================
    //  Default: fully-functional console UI (always works, no dependencies)
    // =========================================================================
    ui = std::make_unique<ConsoleUI>();
#endif

    // ── Boot ─────────────────────────────────────────────────────────────────
    try {
        PathFinder pathfinder(std::move(ui));
        pathfinder.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "[PathFinder] Fatal error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
