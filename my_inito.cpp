#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class FileSystem {
private:
    string currentDir;
    map<string, string> files;  
public:
    FileSystem() : currentDir("/") {}

    void mkdir(const string& dirName) {
        string newDir = currentDir + dirName + "/";
        files[newDir] = "";  
    }

    void cd(const string& path) {
        if (path == "/") {
            currentDir = "/";
        } else if (path == "..") {
            size_t found = currentDir.find_last_of('/');
            currentDir = currentDir.substr(0, found);
            if (currentDir.empty()) currentDir = "/";
        } else if (path[0] == '/') {
            currentDir = path + "/";
        } else {
            currentDir += path + "/";
        }
    }

    void ls() {
        cout << "Contents of " << currentDir << ":\n";
        for (const auto& entry : files) {
            if (entry.first.find(currentDir) == 0) {
                string relativePath = entry.first.substr(currentDir.size());
                size_t pos = relativePath.find('/');
                if (pos != string::npos) {
                   
                    cout << "  [DIR] " << relativePath.substr(0, pos) << "\n";
                } else {
                    
                    cout << "  [FILE] " << relativePath << "\n";
                }
            }
        }
    }

    void touch(const string& fileName) {
        string filePath = currentDir + fileName;
        files[filePath] = "";  
    }

    void echo(const string& content, const string& fileName) {
        string filePath = currentDir + fileName;
        files[filePath] = content;
    }

    void cat(const string& fileName) {
        string filePath = currentDir + fileName;
        if (files.find(filePath) != files.end()) {
            cout << files[filePath] << endl;
        } else {
            cout << "File not found: " << fileName << endl;
        }
    }


    void mv(const string& source, const string& destination) {
        string srcPath = currentDir + source;
        string destPath = currentDir + destination;

        if (files.find(srcPath) != files.end()) {
            files[destPath] = files[srcPath];
            files.erase(srcPath);
        } else {
            cout << "Source file/directory not found: " << source << "\n";
        }
    }

    void cp(const string& source, const string& destination) {
        string srcPath = currentDir + source;
        string destPath = currentDir + destination;

        if (files.find(srcPath) != files.end()) {
            files[destPath] = files[srcPath];
        } else {
            cout << "Source file/directory not found: " << source << "\n";
        }
    }

    void rm(const string& fileName) {
        string filePath = currentDir + fileName;
        if (files.find(filePath) != files.end()) {
            files.erase(filePath);
        } else {
            cout << "File not found: " << fileName << "\n";
        }
    }


};

int main(int argc, char* argv[]) {
    FileSystem fileSystem;
    while (true) {
        string input;
        cout << "> ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        istringstream iss(input);
        string command;
        iss >> command;

        if (command == "mkdir") {
            string dirName;
            iss >> dirName;
            fileSystem.mkdir(dirName);
        } else if (command == "cd") {
            string path;
            iss >> path;
            fileSystem.cd(path);
        } else if (command == "ls") {
            fileSystem.ls();
        } else if (command == "touch") {
            string fileName;
            iss >> fileName;
            fileSystem.touch(fileName);
        } else if (command == "echo") {
            string content;
            iss.ignore();  // Ignore space after 'echo'
            getline(iss, content);
            string fileName;
            iss >> fileName;
            fileSystem.echo(content, fileName);
        } else if (command == "cat") {
            string fileName;
            iss >> fileName;
            fileSystem.cat(fileName);
        } else if (command == "mv") {
            string source, destination;
            iss >> source >> destination;
            fileSystem.mv(source, destination);
        } else if (command == "cp") {
            string source, destination;
            iss >> source >> destination;
            fileSystem.cp(source, destination);
        } else if (command == "rm") {
            string fileName;
            iss >> fileName;
            fileSystem.rm(fileName);
        } else {
            cout << "Invalid command.\n";
        }
    }
    

    return 0;
}
