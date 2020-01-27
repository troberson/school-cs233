// BSTStartProject.cpp : Defines the entry point for the console
// application.
//


#include "BSTree.h"
#include "ComputerScientist.h"
#include <algorithm>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

vector<string> split(const string& s, char delim)
{
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
    return tokens;
}

vector<ComputerScientist*> load(const string& filename)
{
    vector<ComputerScientist*> list;
    std::ifstream file(filename);

    std::string str;
    while (std::getline(file, str))
    {
        vector<string> tokens = split(str, ',');

        list.push_back(new ComputerScientist(tokens[1], tokens[2],
                                             tokens[3], stoi(tokens[0])));
    }

    auto rng = default_random_engine{};
    // I wonder why I need this?
    std::shuffle(std::begin(list), std::end(list), rng);
    return list;
}

int main()
{
    // Uncomment later try the different files out
    // vector<ComputerScientist*> list = load("csList.txt");
    // vector<ComputerScientist*> list = load("csListSmall.txt");
    BinarySearchTree<int, ComputerScientist*> tree2;

    // for turn-in use this line
    vector<ComputerScientist*> list = load("csListMed.txt");

    for (int i = 0; i < list.size(); i++)
    {
        tree2.insert(list[i], list[i]->getID());
    }

    cout << "\n\nPRINTING TREE:\n";
    tree2.printTree();
    cout << "Tree2 count: " << tree2.getCount() << endl;
    cout << "Tree2 size: " << tree2.getSize() << endl << endl;

    // for (int i = 101; i <= 110; ++i) {		// for turn-in uncomment these
    // lines 	tree2.remove(i);
    //}

    // cout << "\n\nPRINTING TREE AFTER REMOVING 101-110:\n";  // for
    // turn-in uncomment these lines tree2.printTree(); cout << "Tree2
    // count: " << tree2.getCount() << endl; cout << "Tree2 size: " <<
    // tree2.getSize() << endl << endl;

    BinarySearchTree<int, ComputerScientist*> tree;
    tree.insert(new ComputerScientist("Robert", "Ward", "Education", 50),
                50);
    tree.insert(new ComputerScientist("Grace", "Hopper", "Compilers", 40),
                40);
    tree.insert(
        new ComputerScientist("Alan", "Turing", "Cryptogarphy", 60), 60);
    tree.insert(
        new ComputerScientist("John", "von Neumann", "Hardware", 45), 45);
    tree.insert(
        new ComputerScientist("Dennis", "Ritchie", "Compilers", 55), 55);
    tree.insert(
        new ComputerScientist("Ada", "Lovelace", "Programming", 30), 30);
    tree.insert(
        new ComputerScientist("Edsger", "Dikstra", "Algorithms", 80), 80);
    tree.insert(new ComputerScientist("Ken", "Thompson", "OS", 70), 70);
    tree.insert(new ComputerScientist("Lonnie", "Heinke", "Education", 58),
                58);

    cout << "\n\nPRINTING TREE:\n";
    tree.printTree();
    cout << "Tree count: " << tree.getCount() << endl;
    cout << "Tree size: " << tree.getSize() << endl << endl;

    ComputerScientist* find;
    if (tree.find(80, find))
    {
        cout << *find << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }

    // tree.remove(50);						// for turn-in uncomment these
    // lines cout << "\n\nPRINTING TREE AFTER REMOVING 50:\n";
    // tree.printTree();
    // cout << "Tree count: " << tree.getCount() << endl;
    // cout << "Tree size: " << tree.getSize() << endl << endl;


    // tree.remove(60);						// for turn-in uncomment these
    // lines cout << "\n\nPRINTING TREE AFTER REMOVING 60:\n";
    // tree.printTree();
    // cout << "Tree count: " << tree.getCount() << endl;
    // cout << "Tree size: " << tree.getSize() << endl << endl;

    return 0;
}
