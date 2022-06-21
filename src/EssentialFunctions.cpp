#include "EssentialFunctions.hpp"
#include <iostream>
#include <sys/stat.h>
#include <sstream>


//Checks if a file with the name already exist
bool EssentialFunctions::fileExists(const std::string& filename){
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}


//Only get number sequence between quotes
std::string EssentialFunctions::getSeqInQuotes(std::string& word){
    auto start = word.find('\"')+1;
    auto stop = word.find('\"', start);
    word = word.substr(start, stop-start);
    return word;
}


//Update progress for nodes/ways/relations (lines)
void EssentialFunctions::updateDataFilesProgress(const std::string& progress){
    EssentialFunctions::progressData[progress] += 1;
}


//Get the current line for nodes/ways/relations file for progress tracking
long long int EssentialFunctions::getDataFilesProgress(const std::string& progress){
    return EssentialFunctions::progressData[progress];
}


//Update progress text
void EssentialFunctions::updateProgressText(const std::string& progress){
    EssentialFunctions::progressText = progress;
}


//Getting the progress text to display on the UI
std::string EssentialFunctions::getProgressText(){
    return EssentialFunctions::progressText;
}


//Nodes processing
bool EssentialFunctions::nodesProcessing(){
    std::string line, word;
    std::fstream sourceFile("map.txt", std::ios::in);
    std::fstream wFileNodes("nodes.txt", std::ios::app);

    while(getline(sourceFile, line)){
        std::stringstream ss(line);
        updateDataFilesProgress("wnodes");
        while(ss >> word){
            if(word.substr(0,2) == "k=") wFileNodes << word << " ";
            if(word.substr(0,2) == "v=") wFileNodes << word.substr(0, word.find("/")) << " ";
            if(word.substr(0,3) == "id=") wFileNodes << word << " ";
            if(word.substr(0,4) == "lat=") wFileNodes << word << " ";
            if(word.substr(0,4) == "lon=") wFileNodes << "lon=\"" << getSeqInQuotes(word) << "\"" << " ";
            if((word.substr(0,4) == "lon=" && word.substr(word.length()-2, 2) == "/>") || word.substr(0,7) == "</node>") wFileNodes << "\n";
        }
    }
    sourceFile.close();
    wFileNodes.close();
    return true;
}


//Ways processing
bool EssentialFunctions::waysProcessing(){
    std::string line, word;
    std::fstream sourceFile("map.txt", std::ios::in);
    std::fstream wFileWays("ways.txt", std::ios::app);

    while(getline(sourceFile, line)){
        std::stringstream ss(line);
        updateDataFilesProgress("wways");
        while(ss >> word){
            if(word.substr(0,2) == "k=") wFileWays << word << " ";
            if(word.substr(0,2) == "v=") wFileWays << word.substr(0, word.find("/")) << " ";
            if(word.substr(0,3) == "id=") wFileWays << word << " ";
            if(word.substr(0,4) == "ref=") wFileWays << word.substr(0, word.find("/")) << " ";
            if(word.substr(0,6) == "</way>") wFileWays << "\n";
        }
    }
    sourceFile.close();
    wFileWays.close();
    return true;
}


//Relations processing
bool EssentialFunctions::relationsProcessing(){
    std::string line, word;
    std::fstream sourceFile("map.txt", std::ios::in);
    std::fstream wFileRelations("relations.txt", std::ios::app);

    while(getline(sourceFile, line)){
        std::stringstream ss(line);
        updateDataFilesProgress("wrelations");
        while(ss >> word){
            if(word.substr(0,3) == "id=") wFileRelations << word << " ";
            if(word.substr(0,4) == "ref=") wFileRelations << word << " ";
            if(word.substr(0,5) == "type=") wFileRelations << word << " ";
            if(word.substr(0,5) == "role=") wFileRelations << word.substr(0, word.find("/")) << " ";
            if(word.substr(0,11) == "</relation>") wFileRelations << "\n";
        }
    }
    sourceFile.close();
    wFileRelations.close();
    return true;
}


//Make filtered files for data
void EssentialFunctions::updateMapData(bool& nodesStatus, bool& waysStatus, bool& relationsStatus){
    bool nodes=false,ways=false,relations=false;
    
    updateProgressText("Filtering Necessary Data");
    while(!nodes && !ways && !relations){
        if(nodesStatus) nodes = nodesProcessing();
        if(waysStatus) ways = waysProcessing();
        if(relationsStatus) relations = relationsProcessing();
    }
    updateProgressText("Data Filtering Completed");
}


/*
void EssentialFunctions::mapUpdater(std::fstream &file, bool &nodesStatus, bool &waysStatus, bool &relationsStatus){
    
}
*/

//Load nodes into unordered_map from nodes file
void EssentialFunctions::loadNodes(std::ifstream& file){
    std::string line, word, word2;
    updateProgressText("Reading nodes data");
    while(getline(file,line)){
        updateDataFilesProgress("nodes");
        std::stringstream ss(line);
        while(ss >> word){
            if(word.substr(0,2) == "k="  ) ss >> word2, EssentialFunctions::nodes[getSeqInQuotes(word)] = getSeqInQuotes(word2);
            if(word.substr(0,3) == "id=" ) EssentialFunctions::nodes["id"] = getSeqInQuotes(word);
            if(word.substr(0,4) == "lat=") EssentialFunctions::nodes["lat"] = getSeqInQuotes(word);
            if(word.substr(0,4) == "lon=") EssentialFunctions::nodes["lon"] = getSeqInQuotes(word);
        }
    }
    updateProgressText("Nodes data successfully loaded");
    file.close();
}


//Load ways into unordered_map from ways file
void EssentialFunctions::loadWays(std::ifstream& file){
    std::string line, word, word2;
    updateProgressText("Reading ways data");
    while(getline(file, line)){
        updateDataFilesProgress("ways");
        std::stringstream ss(line);
        while(ss >> word){
            if(word.substr(0,2) == "k="  ) ss >> word2, EssentialFunctions::ways[getSeqInQuotes(word)] = getSeqInQuotes(word2);
            if(word.substr(0,3) == "id=" ) EssentialFunctions::ways["id"] = getSeqInQuotes(word);
            if(word.substr(0,4) == "ref=") EssentialFunctions::ways["ref"] = getSeqInQuotes(word);
        }
    }
    updateProgressText("Ways data successfully loaded");
    file.close();
}


//Load relations into unordered_map from relations file
void EssentialFunctions::loadRelations(std::ifstream& file){
    std::string line, word, word2;
    updateProgressText("Reading relations data");
    while(getline(file, line)){
        std::stringstream ss(line);
        while(ss >> word){
            if(word.substr(0,2) == "k="  ) EssentialFunctions::ways[getSeqInQuotes(word)] = getSeqInQuotes(word2);
            if(word.substr(0,3) == "id=" ) EssentialFunctions::ways["id"] = getSeqInQuotes(word);
            if(word.substr(0,5) == "type=") ss >> word2, EssentialFunctions::ways[getSeqInQuotes(word)] = getSeqInQuotes(word2);
            if(word.substr(0,5) == "role=" && !(getSeqInQuotes(word) == "")) EssentialFunctions::ways["role"] = getSeqInQuotes(word);
        }
    }
    updateProgressText("Relations data successfully loaded");
    file.close();
}


//Load settings
void EssentialFunctions::loadSettings(){
    std::ifstream rFileSettings;
    std::string line, word, word2;

    rFileSettings.open("settings.txt");
    updateProgressText("Loading settings");
    while(getline(rFileSettings, line)){
        std::stringstream ss(line);
        ss >> word;
        ss >> word2;
        EssentialFunctions::settings[word.substr(0, word.find(":"))] = word2;
    }
    updateProgressText("Settings data successfully loaded");
    rFileSettings.close();
}


//Load the map data for use
void EssentialFunctions::loadMapData(){
    std::ifstream rFileNodes, rFileWays, rFileRelations;
    bool nodesFailed = false, waysFailed = false, relationsFailed = false;

    std::string errorMessage = "";
    updateProgressText("Loading map data");
    try{
        rFileNodes.open("nodes.txt");
        rFileWays.open("ways.txt");
        rFileRelations.open("relations.txt");
        if(!rFileNodes.is_open()){
            nodesFailed = true;
            errorMessage += "Nodes, ";
        }
        if(!rFileWays.is_open()){
            waysFailed = true;
            errorMessage += "Ways, ";
        }
        if(!rFileRelations.is_open()){
            relationsFailed = true;
            errorMessage += "Relations, ";
        }
        if(nodesFailed || waysFailed || relationsFailed){
            rFileNodes.close();
            rFileWays.close();
            rFileRelations.close();
            throw "Error: loadMapData() - " + errorMessage + "file(s) failed to open/load... Reloading Map";
        }else{
            updateProgressText("Nodes and Ways files opened successfully");
            //calling loadNodes and loadWays functions
            loadNodes(rFileNodes);
            loadWays(rFileWays);
            loadRelations(rFileRelations);
        }
    }catch(std::string e){
        updateProgressText(e);

        updateMapData(nodesFailed, waysFailed, relationsFailed);
    }
}
