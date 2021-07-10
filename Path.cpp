#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Directory
{
    Directory() {
        childToToDir = nullptr;
    }
    Directory(string name) : name(name) {}
    string name;
    bool isRoot;
    bool isPathToDist = false;
    Directory *parent;
    Directory *childToToDir;
    vector<Directory *> children;

    void addChild(Directory *newChild)
    {
        children.push_back(newChild);
        newChild->parent = this;
    };

    bool hasThisChild(string &name, Directory** child)
    {
        for (auto dir : children)
        {
            if (dir->name == name)
            {
                *child = dir;
                return true;
            }
        }
        return false;
    };
};

void ConstructTree(Directory *root, string &path, Directory& lastDir, bool isPathToDist)
{
    Directory *current = root;

    // directory names
    vector<string> dirs;
    stringstream dirStream(path);
    char dilemer = '/';
    string dirName;
    while (getline(dirStream, dirName, dilemer))
    {
        dirs.push_back(dirName);
    }

    // constructing the tree
    for (auto name : dirs)
    {
        if (name == "..")
        {
            if (!current->isRoot)
            {
                current->parent->childToToDir = nullptr;
                current->isPathToDist = false;
                cout << "1" << endl;
                current = current->parent;
            }
        }
        else if (name != ".")
        {
            Directory* dir;
            if (!current->hasThisChild(name, &dir))
            {
                dir = new Directory();
                dir->name = name;
                current->addChild(dir);
            }
            if (isPathToDist)
            {
                current->isPathToDist = isPathToDist;
                current->childToToDir = dir;
            }
            cout << "2" << endl;

            current = dir;
        }
    }
    lastDir = *current;
};

string findPath(Directory *source, Directory *dist)
{
    string res;
    bool found = false;
    Directory *current = source;
    while (!found)
    {
        if (current == dist)
        {
            found = true;
            break;
        }

        if (current != nullptr &&  current->isPathToDist &&current->childToToDir != nullptr)
        {
            current = current->childToToDir;
            if (current != nullptr)
                res += "/" + current->name;
        }
        else if (current != nullptr)
        {
            current = current->parent;
            res += "/..";
        }
        else
        {
            cout << "----" << endl;
            found = true;
        }
    }
    return res;
};

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    string sourceName = "./aa/././bb/./cc";
    //cin >> sourceName;

    Directory root("");
    root.isRoot = true;
    Directory source;
    ConstructTree(&root, sourceName, source, false);

    string destName = "aa/cc/dd";
    //cin >> destName;
    Directory dest;
    ConstructTree(&root, destName, dest, true);

    cout << findPath(&source, &dest) << "1";
    return 0;
}
