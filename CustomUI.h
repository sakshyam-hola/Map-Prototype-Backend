#pragma once
// =============================================================================
//  CustomUI.h  ──  UI DESIGNER STUB
// =============================================================================
//
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  This file is the integration surface for the UI designer.               │
//  │                                                                          │
//  │  Every method that currently says  TODO: UI DESIGNER  is a placeholder.  │
//  │  Replace the stub bodies with real widget / render calls.                │
//  │                                                                          │
//  │  The backend (PathFinder) is already wired up; call it via              │
//  │      backend_->findPath(startId, endId, algoIndex)                       │
//  │      backend_->compareAll(startId, endId)                                │
//  │      backend_->graph()          ← read-only access to the Graph          │
//  │      backend_->graph()          ← also call graph().addNode() etc.       │
//  └──────────────────────────────────────────────────────────────────────────┘
//
//  QUICK-START CHECKLIST
//  ─────────────────────
//  [ ] Choose a UI toolkit (Qt 6, Dear ImGui, wxWidgets, SFML, …)
//  [ ] Add toolkit headers / libs to CMakeLists.txt
//  [ ] Implement initialize()  →  create window, load fonts, set theme
//  [ ] Implement run()         →  main render/event loop; call backend on input
//  [ ] Implement displayGraph()→  draw nodes as circles, edges as lines
//  [ ] Implement displayPath() →  highlight path edges & nodes in a colour
//  [ ] Implement promptNodeId()→  clickable node picker or text field
//  [ ] Implement promptAlgorithmChoice() →  radio buttons / combo box
//  [ ] Implement onNodeVisited / onEdgeRelaxed →  animate exploration live
//
//  DATA AVAILABLE ON EACH Node (see include/Node.h):
//      node.id    — unique integer key
//      node.name  — display label
//      node.x / node.y  — 2-D position (use for canvas coordinates)
//
//  DATA AVAILABLE ON PathResult (see include/AlgorithmBase.h):
//      result.path          — vector<int> of node IDs, start → end
//      result.totalCost     — accumulated edge-weight along the path
//      result.nodesExplored — how many nodes the algorithm visited
//      result.timeMs        — wall-clock milliseconds
//      result.found         — false if no path exists
// =============================================================================

#include "UIInterface.h"
#include "PathFinder.h"
#include <string>

class CustomUI : public UIInterface {
public:
    // ── Constructor ───────────────────────────────────────────────────────────
    CustomUI() = default;
    ~CustomUI() override = default;

    // =========================================================================
    //  LIFECYCLE
    // =========================================================================

    void initialize() override {
        // TODO: UI DESIGNER
        // Create the main application window.
        // Examples:
        //   Qt  → QApplication::exec(), MainWindow w; w.show();
        //   ImGui → glfwCreateWindow(…);  ImGui::CreateContext();
        //   SFML  → window_.create(sf::VideoMode(1280,720), "PathFinder");
    }

    void run() override {
        // TODO: UI DESIGNER
        // Enter the main render / event loop.
        //
        // Suggested flow:
        //   while (window is open) {
        //       poll / dispatch events;
        //       if (user clicked "Find Path") {
        //           int s = <get start node from UI>;
        //           int e = <get end node from UI>;
        //           int a = <get algorithm choice from UI>;
        //           PathResult r = backend_->findPath(s, e, a);
        //           displayPath(r, backend_->graph());
        //       }
        //       if (user clicked "Compare All") {
        //           ComparisonResult c = backend_->compareAll(s, e);
        //           displayComparison(c, backend_->graph());
        //       }
        //       render frame;
        //   }
    }

    void shutdown() override {
        // TODO: UI DESIGNER
        // Destroy the window, flush any saves, free GPU resources, etc.
    }

    // =========================================================================
    //  GRAPH DISPLAY
    // =========================================================================

    void displayGraph(const Graph& graph) override {
        // TODO: UI DESIGNER
        // Draw the graph on a canvas.
        //
        // Suggested approach:
        //   const float SCALE = 60.0f;   // world units → pixels
        //   const float OFFSET_X = 40.0f, OFFSET_Y = 40.0f;
        //
        //   // Draw edges first (so nodes render on top)
        //   for (int id : graph.nodeIds()) {
        //       for (const Edge& e : graph.neighbors(id)) {
        //           Node a = graph.getNode(e.from);
        //           Node b = graph.getNode(e.to);
        //           draw_line(a.x*SCALE+OFFSET_X, a.y*SCALE+OFFSET_Y,
        //                     b.x*SCALE+OFFSET_X, b.y*SCALE+OFFSET_Y, GRAY);
        //           draw_label(edge_midpoint, std::to_string(e.weight), SMALL);
        //       }
        //   }
        //   // Draw nodes
        //   for (int id : graph.nodeIds()) {
        //       Node n = graph.getNode(id);
        //       draw_circle(n.x*SCALE+OFFSET_X, n.y*SCALE+OFFSET_Y, 20, BLUE);
        //       draw_label(n.x*SCALE+OFFSET_X, n.y*SCALE+OFFSET_Y, n.name, WHITE);
        //   }
    }

    void displayPath(const PathResult& result, const Graph& graph) override {
        // TODO: UI DESIGNER
        // Highlight the found path on the canvas.
        //
        // result.path is a vector<int> of node IDs: [start, …, end]
        //
        // Suggested approach:
        //   for (size_t i = 1; i < result.path.size(); ++i) {
        //       Node a = graph.getNode(result.path[i-1]);
        //       Node b = graph.getNode(result.path[i]);
        //       draw_line(…, HIGHLIGHT_COLOR, THICK);
        //   }
        //   for (int id : result.path) {
        //       Node n = graph.getNode(id);
        //       draw_circle(…, HIGHLIGHT_COLOR);
        //   }
        //   // Show stats panel
        //   show_panel("Cost: "  + result.totalCost);
        //   show_panel("Explored: " + result.nodesExplored + " nodes");
        //   show_panel("Time: "  + result.timeMs + " ms");
    }

    void displayComparison(const ComparisonResult& cmp,
                           const Graph& graph) override {
        // TODO: UI DESIGNER
        // Show a side-by-side comparison table / bar chart.
        //
        // cmp.results is a vector<PathResult>, one per algorithm.
        //
        // Suggested layout:
        //   ┌──────────────────┬────────┬──────────┬──────────┐
        //   │ Algorithm        │  Cost  │ Explored │ Time(ms) │
        //   ├──────────────────┼────────┼──────────┼──────────┤
        //   │ Dijkstra         │  12.00 │    6     │  0.0120  │
        //   │ A* Search        │  12.00 │    4     │  0.0085  │
        //   │ BFS              │  14.00 │    8     │  0.0060  │
        //   └──────────────────┴────────┴──────────┴──────────┘
    }

    // =========================================================================
    //  USER INPUT
    // =========================================================================

    int promptNodeId(const std::string& prompt,
                     const Graph& graph) override {
        // TODO: UI DESIGNER
        // Show a modal / panel that lets the user click a node on the canvas
        // OR type its ID into a text field.
        //
        // Return the selected node ID.
        //
        // Example (Dear ImGui):
        //   static int selected = 0;
        //   ImGui::Text("%s", prompt.c_str());
        //   for (int id : graph.nodeIds()) {
        //       if (ImGui::Selectable(graph.getNode(id).name.c_str(),
        //                            selected == id))
        //           selected = id;
        //   }
        //   return selected;

        return -1;  // placeholder
    }

    int promptAlgorithmChoice() override {
        // TODO: UI DESIGNER
        // Show radio buttons or a combo box:
        //   [●] Dijkstra's Algorithm
        //   [○] A* Search
        //   [○] Breadth-First Search
        //   [○] Compare All Three
        //
        // Return 0 = Dijkstra, 1 = A*, 2 = BFS, 3 = Compare All

        return 0;  // placeholder
    }

    int promptMapChoice() override {
        // TODO: UI DESIGNER
        // Show a map-selection panel:
        //   [●] City Map      — 10 nodes
        //   [○] 4×4 Grid      — 16 nodes
        //   [○] Sparse Graph  — 7 nodes
        //   [○] Load from file
        //   [○] Edit current map
        //
        // Return 0–4

        return 0;  // placeholder
    }

    bool promptRunAgain() override {
        // TODO: UI DESIGNER
        // After a result is shown, offer a "Search Again" button.
        // Return true if the user wants to keep going.

        return false;  // placeholder
    }

    // =========================================================================
    //  MAP EDITOR
    // =========================================================================

    void openMapEditor(Graph& graph) override {
        // TODO: UI DESIGNER
        // Open an interactive map-editor panel (inline or as a modal).
        //
        // Required editing operations (all exist on Graph):
        //   graph.addNode(name, x, y)          → returns new id
        //   graph.removeNode(id)
        //   graph.updateNode(id, name, x, y)
        //   graph.addEdge(fromId, toId, weight)
        //   graph.removeEdge(fromId, toId)
        //   graph.updateWeight(fromId, toId, w)
        //
        // UI suggestions:
        //   • Click canvas to place a node, drag to reposition
        //   • Click two nodes then "Add Edge" button → prompt for weight
        //   • Right-click node → "Delete" context menu
        //   • Right-click edge → "Edit weight" / "Delete"
        //   • Floating properties panel shows selected node/edge details
    }

    // =========================================================================
    //  STATUS / FEEDBACK
    // =========================================================================

    void showMessage(const std::string& msg) override {
        // TODO: UI DESIGNER
        // Show a toast / status-bar message.
    }

    void showError(const std::string& err) override {
        // TODO: UI DESIGNER
        // Show an error dialog or red status message.
    }

    void showProgress(int pct, const std::string& label) override {
        // TODO: UI DESIGNER
        // Show / update a progress bar (used during file loads etc.).
    }

    // =========================================================================
    //  ANIMATION HOOKS  (step-by-step visualisation)
    // =========================================================================
    //  These are called automatically by PathFinder while an algorithm runs.
    //  Override them to animate node exploration live on the canvas.

    void onAlgorithmStart(const std::string& name,
                          int start, int end) override {
        // TODO: UI DESIGNER
        // Reset any previous highlights; store start/end for rendering.
        // Example: clear visited_set_; set status_label_ = name + " running…";
    }

    void onNodeVisited(int nodeId, double cost) override {
        // TODO: UI DESIGNER
        // Mark nodeId as "explored" (e.g. paint it a lighter colour).
        // Example: explored_nodes_.insert(nodeId);
        //          redraw();
    }

    void onEdgeRelaxed(int from, int to, double cost) override {
        // TODO: UI DESIGNER
        // Highlight the edge (from→to) as "candidate path".
        // Example: relaxed_edges_.insert({from, to});
        //          redraw();
    }

    void onAlgorithmComplete(const PathResult& result) override {
        // TODO: UI DESIGNER
        // Called when the algorithm finishes.
        // Trigger final path highlight + stats panel.
        // Example: displayPath(result, backend_->graph());
        //          status_label_ = "Done — cost: " + result.totalCost;
    }

    // =========================================================================
    //  INTERNAL STATE  (add your own toolkit-specific fields here)
    // =========================================================================
private:
    // ── Example fields — replace / extend for your toolkit ───────────────────
    // QMainWindow*       mainWindow_ = nullptr;    // Qt
    // GLFWwindow*        glfwWindow_ = nullptr;    // Dear ImGui / OpenGL
    // sf::RenderWindow   sfmlWindow_;              // SFML

    // Animation state
    // std::unordered_set<int>                explored_nodes_;
    // std::unordered_set<std::pair<int,int>> relaxed_edges_;
    // std::vector<int>                       final_path_;

    // UI state
    // int  selectedStart_  = -1;
    // int  selectedEnd_    = -1;
    // int  selectedAlgo_   = 0;
    // bool showEditor_     = false;
    // bool showComparison_ = false;
};
