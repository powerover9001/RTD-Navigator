#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

class EssentialFunctions{
    public:
        //Public Functions
        bool fileExists(const std::string& filename);
        //void mapUpdater(std::fstream &file, bool &nodesStatus, bool &waysStatus, bool &relationsStatus);
        void updateMapData(bool& nodesStatus, bool& waysStatus, bool& relationsStatus);
        void loadSettings();
        void loadMapData();
        std::string& getSeqInQuotes(std::string& word);
        void reload();

        //Get progress
        long long int& getDataFilesProgress(const std::string& progress);
        std::string& getProgressText();

        //Public Variables
        std::unordered_map<std::string, std::string> settings;
        std::unordered_map<std::string, std::string> nodes;
        std::unordered_map<std::string, std::string> ways;
        std::unordered_map<std::string, std::string> relations;

    private:
        //Private Functions
        bool nodesProcessing();
        bool waysProcessing();
        bool relationsProcessing();
        void loadNodes(std::ifstream& file);
        void loadWays(std::ifstream& file);
        void loadRelations(std::ifstream& file);
        //void errorHandler(std::string error);

        //Update progress
        void updateDataFilesProgress(const std::string& toUpdate);
        void updateProgressText(const std::string& progress);

        //Private Variables
        std::string progressText;
        long long int sourceFileProgress = 86343140;
        std::unordered_map<std::string, long long int> progressData{
            {"wnodes", 0},
            {"wways", 0},
            {"wrelations", 0},
            {"rnodes", 0},
            {"rways", 0},
            {"rrelations", 0}
        };
};