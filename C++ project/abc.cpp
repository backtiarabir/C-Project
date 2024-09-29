#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class FileSystem {
private:
    struct Node {
        std::string name;
        bool is_directory;
        std::string contents;
        std::vector<Node*> children;
        Node(std::string name, bool is_directory): name(name), is_directory(is_directory) {}
    };
    Node* root;
    std::map<std::string, Node*> path_to_node;

public:
    FileSystem(): root(new Node("/", true)) {
        path_to_node["/"] = root;
    }

    void create_file(std::string path) {
        if (path_to_node.count(path) > 0) {
            std::cout << "Error: " << path << " already exists" << std::endl;
            return;
        }

        std::string parent_path = path.substr(0, path.find_last_of('/'));
        std::string filename = path.substr(path.find_last_of('/') + 1);

        Node* parent = path_to_node[parent_path];
        Node* file = new Node(filename, false);

        parent->children.push_back(file);
        path_to_node[path] = file;
    }

    void create_directory(std::string path) {
        if (path_to_node.count(path) > 0) {
            std::cout << "Error: " << path << " already exists" << std::endl;
            return;
        }

        std::string parent_path = path.substr(0, path.find_last_of('/'));
        std::string dirname = path.substr(path.find_last_of('/') + 1);

        Node* parent = path_to_node[parent_path];
        Node* dir = new Node(dirname, true);

        parent->children.push_back(dir);
        path_to_node[path] = dir;
    }

    void delete_file(std::string path) {
        if (path_to_node.count(path) == 0) {
            std::cout << "Error: " << path << " does not exist" << std::endl;
            return;
        }

        std::string parent_path = path.substr(0, path.find_last_of('/'));

        Node* parent = path_to_node[parent_path];
        Node* file = path_to_node[path];

        for (int i = 0; i < parent->children.size(); i++) {
            if (parent->children[i] == file) {
                parent->children.erase(parent->children.begin() + i);
                break;
            }
        }

        path_to_node.erase(path);
        delete file;
    }

    void delete_directory(std::string path) {
        if (path_to_node.count(path) == 0) {
            std::cout << "Error: " << path << " does not exist" << std::endl;
            return;
        }

        Node* dir = path_to_node[path];

        if (!dir->is_directory) {
            std::cout << "Error: " << path << " is not a directory" << std::endl;
            return;
        }

        std::vector<Node*> children = dir->children;

        for (Node* child : children) {
            if (child->is_directory) {
                delete_directory(path + "/" + child->name);
            } else {
                delete_file(path + "/" + child->name);
            }
        }

        std::string parent_path = path.substr(0, path.find_last_of('/'));

        Node* parent = path_to_node[parent_path];

        for (int i = 0; i < parent->children.size();
