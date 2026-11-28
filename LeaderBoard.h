#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "Common.h"
#include "Registration.h"
#include "SpaceGraph.h"

struct LeaderEntry {
    int    rank;
    string cro;
    string result;
    int    cred;
    int    ticks;
    int    crash;
    int    hijack;
    int    breach;
    string date;
};

class LeaderBoard {
private:
    LeaderEntry entries[200];
    int         entryCount;

    void   loadEntries();
    void   sortEntries();
    bool   isBetter(const LeaderEntry& a, const LeaderEntry& b);
    int    dateKey(const string& date);
    string getTodayDate();

public:
    LeaderBoard();

    bool loadFlights(const string& filename, Registration& reg);
    bool loadCrew(const string& filename, Registration& reg);
    bool loadAirspace(const string& filename, SpaceGraph& graph);
    int  loadScenario(const string& filename, ScenarioEvent events[]);

    void saveResult(const string& commander, const string& result, int credibility,
                    int ticks, int crashes, int hijacks, int breaches);
    void displayLeaderboard();
};

#endif
