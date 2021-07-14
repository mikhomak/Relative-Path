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

/**
 * Each directory contains:
 *      * name
 *      * isRoot - is it the root of the tree?
 *      * isPathToDist - is this directory marked as a path from root to the destination folder? If so, we can coonect to any marked folder and by going down the marked root we will esentially find the destniation
 *      * parent - parent folder
 *      * chilToDir - marked child folder (only one child folder is allowed)
 *      * children - all the child folders
 */
struct Directory
{
    Directory() {}
    Directory(string &name) : name(name) {}
    // I could use smart pointers and make my life easier but since it wasn't imported to the libs i dunno if that's allowed
    ~Directory()
    {
        for (auto child : children)
        {
            delete child;
        }
    }
    string name;
    bool isRoot = false;
    bool isPathToDist = false;
    Directory *parent = nullptr;
    Directory *childToToDir = nullptr;
    vector<Directory *> children;

    /**
     * Adds child directory to the current directory (aka to children array)
     * Sets the parent of the child to this
     */
    void addChild(Directory *newChild)
    {
        children.push_back(newChild);
        newChild->parent = this;
    };

    /**
     * Checks if the directory has a child directory with this name
     * If so, sets outChild and returns null
     *
     * @param name - name of the child directory to find
     * @param outChild - in case if the directory was found, sets this directory to this value
     * @return true if directory was found false if it wasn't found
     */
    bool hasThisChild(const string &name, Directory *&outChild)
    {
        for (auto dir : children)
        {
            if (dir->name == name)
            {
                outChild = dir;
                return true;
            }
        }
        return false;
    };
};

/**
 * Constructs the directory tree
 * 2 steps to construct the tree:
 *  1. construct the path from root to source folder
 *  2. construct the path from root to destination folder, marking the path from root to the destination, so it will be easier to find the path
 *
 * @param root - root of the tree
 * @param path - path to make all the folder
 * @param outlastDir - returns the last folder. We need it to get the source/destination folder
 * @param isPathToDist - whenever we need to mark the path as the path to the destination folder
 */
void constructTree(Directory *root, string &path, Directory *&outlastDir, bool isPathToDist)
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
        // going to parent
        if (name == "..")
        {
            if (!current->isRoot)
            {
                // if we go up -> unmark this directory as the path to destination
                current->parent->childToToDir = nullptr;
                current->isPathToDist = false;
                current = current->parent;
            }
        }
        else if (name != ".")
        {
            Directory *dir;
            // if the dir with name was found in current, we will set it in hasThisChild()
            // if not, then create it
            if (!current->hasThisChild(name, dir))
            {
                dir = new Directory();
                dir->name = name;
                current->addChild(dir);
            }
            // marking it as a folder to the destiatnion folder
            if (isPathToDist)
            {
                current->isPathToDist = isPathToDist;
                current->childToToDir = dir;
            }

            current = dir;
        }
    }
    //setting last folder as a source/destination folder
    outlastDir = current;
};

string findPath(Directory *source, Directory *dist)
{
    string res;
    bool found = false;

    Directory *current = source;

    while (!found)
    {
        // found the destination
        if (current == dist)
        {
            found = true;
            break;
        }

        // if there is a path to the destination from the current folder -> going down by its path
        if (current != nullptr && current->isPathToDist && current->childToToDir != nullptr)
        {
            current = current->childToToDir;
            res += res.length() == 0 ? current->name : "/" + current->name;
        }
        // if there is no marked path -> going up untill we find one of the parent that has a marked folder(potentially going up to the root)
        else if (current != nullptr)
        {
            current = current->parent;
            res += res.length() == 0 ? ".." : "/..";
        }
    }
    return res;
};

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    string sourceName  = "./aa/././bb/./cc";
    //cin >> sourceName;

    Directory root;
    root.isRoot = true;
    Directory *source;
    constructTree(&root, sourceName, source, false);

    string destName  = "aa/cc/dd";
    //cin >> destName;
    Directory *dest;
    constructTree(&root, destName, dest, true);

    cout << findPath(source, dest);
    
    return 0;
}
