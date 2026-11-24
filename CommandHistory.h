#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H
#include "Common.h"
#include "Registration.h"


struct CommandNode {
    string       action;
    string       callsign;
    int          tick;
    CommandNode* prev;
    CommandNode* next;
};

struct SnapshotNode {
    string        callsign;
    string        commandName;
    string        prevRunway;
    int           prevPriority;
    string        prevSector;
    int           prevStatus;
    int           prevAlertTick;
    int           credDelta;
    SnapshotNode* next;
};

class SnapshotStack {
private:
    SnapshotNode* top;
public:
    SnapshotStack();
    ~SnapshotStack();
    void          push(SnapshotNode* node);
    SnapshotNode* pop();
    SnapshotNode* peek();
    bool          isEmpty();
    void          clear();
};

class CommandHistory {
private:
    CommandNode*  head;
    CommandNode*  tail;
    int           commandCount;
    SnapshotStack undoStack;
    SnapshotStack redoStack;
    Registration* registry;

    void swapState(SnapshotNode* node);

public:
    // details of the last undo/redo, read by the game engine
    string lastName;
    string lastCallsign;
    int    lastAlertTick;
    int    lastDelta;

    CommandHistory(Registration* reg);
    ~CommandHistory();

    void logCommand(const string& action, const string& callsign, int tick);
    void pushSnapshot(Flight* flight, const string& commandName);
    void pushCustomSnapshot(const string& commandName, const string& key, int alertTick);
    void setLastDelta(int delta);
    bool undo();
    bool redo();
    void displayHistory(int count);
    void displayLastCommand();
};

#endif
