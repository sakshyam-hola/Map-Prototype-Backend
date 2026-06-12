#include "../include/UIInterface.h"
#include "../include/PathFinder.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>

// =============================================================================
//  ComparisonResult
// =============================================================================

void ComparisonResult::print(const Graph& graph) const {
    const int W = 64;
    std::string dbl(W, '=');
    std::cout << "\n  " << dbl << "\n";
    std::cout << "  COMPARISON RESULTS\n";
    std::cout << "  Start : " << graph.getNode(startNode).name
              << "    End : " << graph.getNode(endNode).name << "\n";
    std::cout << "  " << std::string(W, '-') << "\n";
    std::cout << "  " << std::left
              << std::setw(24) << "Algorithm"
              << std::setw(10) << "Cost"
              << std::setw(12) << "Explored"
              << std::setw(12) << "Time (ms)"
              << "\n";
    std::cout << "  " << std::string(W, '-') << "\n";

    for (const auto& r : results) {
        std::cout << "  " << std::left << std::setw(24) << r.algorithmName;
        if (r.found) {
            std::cout << std::fixed << std::setprecision(2)
                      << std::setw(10) << r.totalCost
                      << std::setw(12) << r.nodesExplored
                      << std::setprecision(4) << std::setw(12) << r.timeMs;
        } else {
            std::cout << std::setw(34) << "No path found";
        }
        std::cout << "\n";
    }
    std::cout << "  " << dbl << "\n";
}

const PathResult* ComparisonResult::cheapest() const {
    const PathResult* best = nullptr;
    for (const auto& r : results)
        if (r.found && (!best || r.totalCost < best->totalCost)) best = &r;
    return best;
}

const PathResult* ComparisonResult::fastest() const {
    const PathResult* best = nullptr;
    for (const auto& r : results)
        if (r.found && (!best || r.timeMs < best->timeMs)) best = &r;
    return best;
}

const PathResult* ComparisonResult::leastExplored() const {
    const PathResult* best = nullptr;
    for (const auto& r : results)
        if (r.found && (!best || r.nodesExplored < best->nodesExplored)) best = &r;
    return best;
}

// =============================================================================
//  ConsoleUI — helpers
// =============================================================================

void ConsoleUI::banner() const {
    std::cout << R"(
  ╔════════════════════════════════════════════════════════════╗
  ║          PATH FINDER  —  Algorithm Comparison Tool         ║
  ║        Dijkstra's  ·  A* Search  ·  Breadth-First          ║
  ╚════════════════════════════════════════════════════════════╝
)" << "\n";
}

void ConsoleUI::separator(char c, int n) const {
    std::cout << "  " << std::string(n, c) << "\n";
}

int ConsoleUI::readInt(int lo, int hi) const {
    int v;
    while (true) {
        if (std::cin >> v && v >= lo && v <= hi) return v;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Enter a number between " << lo << " and " << hi << ": ";
    }
}

// =============================================================================
//  ConsoleUI — UIInterface implementation
// =============================================================================

void ConsoleUI::initialize() {
    banner();
}

void ConsoleUI::shutdown() {
    showMessage("Thank you for using PathFinder. Goodbye!");
}

void ConsoleUI::showMessage(const std::string& msg) {
    std::cout << "\n  ▸  " << msg << "\n";
}

void ConsoleUI::showError(const std::string& err) {
    std::cerr << "\n  ✗  ERROR: " << err << "\n";
}

void ConsoleUI::showProgress(int pct, const std::string& label) {
    int filled = pct / 5;
    std::cout << "  [";
    for (int i = 0; i < 20; ++i) std::cout << (i < filled ? '#' : '.');
    std::cout << "] " << std::setw(3) << pct << "%  " << label << "\n";
}

void ConsoleUI::displayGraph(const Graph& graph) {
    graph.print();
}

void ConsoleUI::printPathVisual(const PathResult& r, const Graph& graph) const {
    if (!r.found) return;
    std::cout << "\n  Visual: ";
    for (size_t i = 0; i < r.path.size(); ++i) {
        if (i) {
            double w = graph.getWeight(r.path[i-1], r.path[i]);
            std::cout << " ──[" << std::fixed << std::setprecision(1) << w << "]── ";
        }
        std::cout << "[ " << graph.getNode(r.path[i]).name << " ]";
    }
    std::cout << "\n";
}

void ConsoleUI::displayPath(const PathResult& result, const Graph& graph) {
    result.print(graph);
    printPathVisual(result, graph);
}

void ConsoleUI::displayComparison(const ComparisonResult& cmp,
                                   const Graph& graph)
{
    cmp.print(graph);

    // Print each path detail
    for (const auto& r : cmp.results) {
        printPathVisual(r, graph);
    }

    // Summary winners
    auto* cheap  = cmp.cheapest();
    auto* few    = cmp.leastExplored();
    if (cheap) std::cout << "\n  ★ Lowest cost    : "
                         << cheap->algorithmName
                         << "  (cost " << cheap->totalCost << ")\n";
    if (few)   std::cout << "  ★ Least explored : "
                         << few->algorithmName
                         << "  (" << few->nodesExplored << " nodes)\n";
}

int ConsoleUI::promptNodeId(const std::string& prompt, const Graph& graph) {
    std::cout << "\n  " << prompt << "\n";
    // Show quick list
    std::cout << "  Available nodes:\n";
    for (int id : graph.nodeIds()) {
        const auto& n = graph.getNode(id);
        std::cout << "    [" << std::setw(2) << id << "]  " << n.name << "\n";
    }
    std::cout << "  Enter node ID: ";
    int id;
    while (true) {
        if (std::cin >> id && graph.hasNode(id)) return id;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Invalid ID. Try again: ";
    }
}

int ConsoleUI::promptAlgorithmChoice() {
    separator();
    std::cout << "  Select algorithm:\n"
              << "    [0] Dijkstra's Algorithm\n"
              << "    [1] A* Search\n"
              << "    [2] Breadth-First Search\n"
              << "    [3] Compare All Three\n"
              << "  Choice: ";
    return readInt(0, 3);
}

int ConsoleUI::promptMapChoice() {
    separator('=');
    std::cout << "  Select map:\n"
              << "    [0] City Map      (10 nodes, named locations)\n"
              << "    [1] 4×4 Grid      (16 nodes, unit-weight grid)\n"
              << "    [2] Sparse Graph  (7 nodes, sparse connections)\n"
              << "    [3] Load from file\n"
              << "    [4] Edit current map\n"
              << "  Choice: ";
    return readInt(0, 4);
}

bool ConsoleUI::promptRunAgain() {
    std::cout << "\n  Run another search? (y/n): ";
    char c;
    std::cin >> c;
    return (c == 'y' || c == 'Y');
}

void ConsoleUI::openMapEditor(Graph& graph) {
    separator('=');
    std::cout << "  MAP EDITOR\n";
    separator('-');

    bool done = false;
    while (!done) {
        std::cout << "\n  [1] Add node\n"
                  << "  [2] Remove node\n"
                  << "  [3] Add edge\n"
                  << "  [4] Remove edge\n"
                  << "  [5] Update edge weight\n"
                  << "  [6] Print graph\n"
                  << "  [7] Save to file\n"
                  << "  [0] Done\n"
                  << "  Choice: ";
        int ch;
        if (!(std::cin >> ch)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            continue;
        }

        switch (ch) {
            case 1: {
                std::string name;
                double x, y;
                std::cin.ignore();
                std::cout << "  Node name: "; std::getline(std::cin, name);
                std::cout << "  X coord  : "; std::cin >> x;
                std::cout << "  Y coord  : "; std::cin >> y;
                int id = graph.addNode(name, x, y);
                showMessage("Added node [" + std::to_string(id) + "] " + name);
                break;
            }
            case 2: {
                int id;
                std::cout << "  Node ID: "; std::cin >> id;
                graph.removeNode(id)
                    ? showMessage("Node removed.")
                    : showError("Node not found.");
                break;
            }
            case 3: {
                int from, to; double w;
                std::cout << "  From ID : "; std::cin >> from;
                std::cout << "  To ID   : "; std::cin >> to;
                std::cout << "  Weight  : "; std::cin >> w;
                graph.addEdge(from, to, w)
                    ? showMessage("Edge added.")
                    : showError("Failed (nodes missing or negative weight?).");
                break;
            }
            case 4: {
                int from, to;
                std::cout << "  From ID: "; std::cin >> from;
                std::cout << "  To ID  : "; std::cin >> to;
                graph.removeEdge(from, to)
                    ? showMessage("Edge removed.")
                    : showError("Edge not found.");
                break;
            }
            case 5: {
                int from, to; double w;
                std::cout << "  From ID    : "; std::cin >> from;
                std::cout << "  To ID      : "; std::cin >> to;
                std::cout << "  New weight : "; std::cin >> w;
                graph.updateWeight(from, to, w)
                    ? showMessage("Weight updated.")
                    : showError("Edge not found.");
                break;
            }
            case 6: graph.print(); break;
            case 7: {
                std::string path;
                std::cin.ignore();
                std::cout << "  Save path (e.g. map.txt): ";
                std::getline(std::cin, path);
                graph.saveToFile(path)
                    ? showMessage("Saved to " + path)
                    : showError("Could not open file.");
                break;
            }
            case 0: done = true; break;
            default: showError("Unknown option.");
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  ConsoleUI::run — main application loop
// ─────────────────────────────────────────────────────────────────────────────
void ConsoleUI::run() {
    PathFinder* pf = backend_;
    if (!pf) { showError("No backend connected."); return; }

    bool keepGoing = true;
    while (keepGoing) {

        // ── Step 1: choose / edit a map ──────────────────────────────────────
        int mapChoice = promptMapChoice();
        switch (mapChoice) {
            case 0: pf->loadPreset(Graph::Preset::CITY_MAP);     break;
            case 1: pf->loadPreset(Graph::Preset::GRID_4x4);     break;
            case 2: pf->loadPreset(Graph::Preset::SPARSE_GRAPH); break;
            case 3: {
                std::string path;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "  File path: ";
                std::getline(std::cin, path);
                if (!pf->graph().loadFromFile(path)) {
                    showError("Could not load '" + path + "'. Keeping current map.");
                } else {
                    showMessage("Map loaded from " + path);
                }
                break;
            }
            case 4:
                openMapEditor(pf->graph());
                break;
        }

        displayGraph(pf->graph());

        // ── Step 2: get start / end nodes ────────────────────────────────────
        int startId = promptNodeId("Choose START node:", pf->graph());
        int endId   = promptNodeId("Choose END node:",   pf->graph());

        if (startId == endId) {
            showMessage("Start and end are the same node — trivial path.");
            keepGoing = promptRunAgain();
            continue;
        }

        // ── Step 3: choose algorithm ─────────────────────────────────────────
        int algo = promptAlgorithmChoice();

        separator();
        if (algo == 3) {
            ComparisonResult cmp = pf->compareAll(startId, endId);
            displayComparison(cmp, pf->graph());
        } else {
            PathResult res = pf->findPath(startId, endId, algo);
            displayPath(res, pf->graph());
        }

        keepGoing = promptRunAgain();
    }
}
