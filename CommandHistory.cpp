#include "CommandHistory.h"
//stack implemented by link list
SnapshotStack::SnapshotStack() { top = nullptr; }
SnapshotStack::~SnapshotStack() { clear(); }

void SnapshotStack::push(SnapshotNode* node) {
    node->next = top;
    top = node;
}

SnapshotNode* SnapshotStack::pop() {
    if (top == nullptr) return nullptr;
    SnapshotNode* node = top;
    top = top->next;
    node->next = nullptr;
    return node;
}

SnapshotNode* SnapshotStack::peek() { return top; }
bool SnapshotStack::isEmpty() { return top == nullptr; }

void SnapshotStack::clear() {
    while (top != nullptr) {
        SnapshotNode* next = top->next;
        delete top;
        top = next;
    }
}

CommandHistory::CommandHistory(Registration* reg) {
    head = nullptr;
    tail = nullptr;
    commandCount = 0;
    registry = reg;
    lastAlertTick = -1;
    lastDelta = 0;
}

CommandHistory::~CommandHistory() {
    while (head != nullptr) {
        CommandNode* next = head->next;
        delete head;
        head = next;
    }
}
// Adds a new command to the end of the his list
void CommandHistory::logCommand(const string& action, const string& callsign, int tick) {
    CommandNode* node = new CommandNode();
    node->action = action;
    node->callsign = callsign;
    node->tick = tick;
    node->prev = tail;
    node->next = nullptr;
    if (tail != nullptr) tail->next = node;
    else head = node;
    tail = node;
    commandCount++;
}
//saves the current flight state before executing a command
void CommandHistory::pushSnapshot(Flight* flight, const string& commandName) {
    SnapshotNode* node = new SnapshotNode();
    node->callsign = flight->callsign;
    node->commandName = commandName;
    node->prevRunway = flight->assignedRunway;
    node->prevPriority = flight->priorityLevel;
    node->prevSector = flight->currentSector;
    node->prevStatus = flight->status;
    node->prevAlertTick = flight->alertTick;
    node->credDelta = 0;
    node->next = nullptr;
    undoStack.push(node);
    redoStack.clear();
}
// Saves a snapshot for commands that do not require a flight state
void CommandHistory::pushCustomSnapshot(const string& commandName, const string& key, int alertTick) {
    SnapshotNode* node = new SnapshotNode();
    node->callsign = key;
    node->commandName = commandName;
    node->prevPriority = 0;
    node->prevStatus = 0;
    node->prevAlertTick = alertTick;
    node->credDelta = 0;
    node->next = nullptr;
    undoStack.push(node);
    redoStack.clear();
}
// Stores the credit change in the latest snapshot
void CommandHistory::setLastDelta(int delta) {
    SnapshotNode* top = undoStack.peek();
    if (top != nullptr) top->credDelta = delta;
}
// Swaps the saved flight state with the current state
void CommandHistory::swapState(SnapshotNode* node) {
    Flight* f = registry->findFlight(node->callsign);
    if (f != nullptr) {
        string runway = f->assignedRunway;
        int priority = f->priorityLevel;
        string sector = f->currentSector;
        int status = f->status;
        int alertTick = f->alertTick;

        f->assignedRunway = node->prevRunway;
        f->priorityLevel = node->prevPriority;
        f->currentSector = node->prevSector;
        f->status = node->prevStatus;
        f->alertTick = node->prevAlertTick;
        f->moveTimer = 0;

        node->prevRunway = runway;
        node->prevPriority = priority;
        node->prevSector = sector;
        node->prevStatus = status;
        node->prevAlertTick = alertTick;
    }
    lastName = node->commandName;
    lastCallsign = node->callsign;
    lastAlertTick = node->prevAlertTick;
    lastDelta = node->credDelta;
}
// Reverses the most recent command and moves its snapshot to the redo stack
bool CommandHistory::undo() {
    SnapshotNode* node = undoStack.pop();
    if (node == nullptr) return false;
    swapState(node);
    redoStack.push(node);
    return true;
}
// Restores the command that was most recently undone
bool CommandHistory::redo() {
    SnapshotNode* node = redoStack.pop();
    if (node == nullptr) return false;
    swapState(node);
    undoStack.push(node);
    return true;
}

void CommandHistory::displayHistory(int count) {
    if (tail == nullptr) {
        cout << "No commands yet.\n";
        return;
    }
    CommandNode* node = tail;
    for (int i = 0; i < count && node != nullptr; i++) {
        cout << "  Tick " << node->tick << ": " << node->action << " (" << node->callsign << ")\n";
        node = node->prev;
    }
}

void CommandHistory::displayLastCommand() {
    if (tail == nullptr) cout << "No commands yet.\n";
    else cout << "Last command: Tick " << tail->tick << ": " << tail->action << " (" << tail->callsign << ")\n";
}
