#/**
 * @file main.cpp
 * @brief Test dell'albero binario utilizzando tipi di dati diversi.
 */

#include <iostream>
#include <string>
#include "binarytree.hpp"

// Tipo custom per test
struct CustomType {
    int id; ///< Identificatore univoco.
    std::string name; ///< Nome associato all'identificatore.

    /**
     * @brief Operatore di confronto '<' per il tipo CustomType.
     * 
     * @param other Altro oggetto CustomType da confrontare.
     * @return true Se l'oggetto corrente è minore di 'other'.
     * @return false Altrimenti.
     */
    bool operator<(const CustomType& other) const {
        return id < other.id;
    }

    /**
     * @brief Operatore di confronto '==' per il tipo CustomType.
     * 
     * @param other Altro oggetto CustomType da confrontare.
     * @return true Se l'oggetto corrente è uguale a 'other'.
     * @return false Altrimenti.
     */
    bool operator==(const CustomType& other) const {
        return id == other.id;
    }

    /**
     * @brief Operatore di stream '<<' per il tipo CustomType.
     * 
     * @param os Stream di output su cui stampare.
     * @param obj Oggetto CustomType da stampare.
     * @return std::ostream& Stream di output aggiornato.
     */
    friend std::ostream& operator<<(std::ostream& os, const CustomType& obj) {
        os << "{" << obj.id << ", " << obj.name << "}";
        return os;
    }
};

// Functor di comparazione per il tipo int
struct IntCompare {
    /**
     * @brief Operatore di confronto per il tipo int.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è minore di rhs.
     * @return false Altrimenti.
     */
    bool operator()(const int& lhs, const int& rhs) const {
        return lhs < rhs;
    }
};

// Functor di uguaglianza per il tipo int
struct IntEqual {
    /**
     * @brief Operatore di uguaglianza per il tipo int.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è uguale a rhs.
     * @return false Altrimenti.
     */
    bool operator()(const int& lhs, const int& rhs) const {
        return lhs == rhs;
    }
};

// Functor per verificare se un valore è pari
template<typename T>
struct IsEven {
    /**
     * @brief Operatore di verifica per valore pari.
     * 
     * @param value Valore da verificare.
     * @return true Se il valore è pari.
     * @return false Altrimenti.
     */
    bool operator()(const T& value) const {
        return value % 2 == 0;
    }
};

// Functor di comparazione per il tipo double
struct DoubleCompare {
    /**
     * @brief Operatore di confronto per il tipo double.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è minore di rhs.
     * @return false Altrimenti.
     */
    bool operator()(const double& lhs, const double& rhs) const {
        return lhs < rhs;
    }
};

// Functor di uguaglianza per il tipo double
struct DoubleEqual {
    /**
     * @brief Operatore di uguaglianza per il tipo double.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è uguale a rhs.
     * @return false Altrimenti.
     */
    bool operator()(const double& lhs, const double& rhs) const {
        return lhs == rhs;
    }
};

// Functor di comparazione per il tipo string
struct StringCompare {
    /**
     * @brief Operatore di confronto per il tipo string.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è minore di rhs.
     * @return false Altrimenti.
     */
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs < rhs;
    }
};

// Functor di uguaglianza per il tipo string
struct StringEqual {
    /**
     * @brief Operatore di uguaglianza per il tipo string.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è uguale a rhs.
     * @return false Altrimenti.
     */
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs == rhs;
    }
};

// Functor di comparazione per il tipo CustomType
struct CustomTypeCompare {
    /**
     * @brief Operatore di confronto per il tipo CustomType.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è minore di rhs.
     * @return false Altrimenti.
     */
    bool operator()(const CustomType& lhs, const CustomType& rhs) const {
        return lhs.id < rhs.id;
    }
};

// Functor di uguaglianza per il tipo CustomType
struct CustomTypeEqual {
    /**
     * @brief Operatore di uguaglianza per il tipo CustomType.
     * 
     * @param lhs Primo operando.
     * @param rhs Secondo operando.
     * @return true Se lhs è uguale a rhs.
     * @return false Altrimenti.
     */
    bool operator()(const CustomType& lhs, const CustomType& rhs) const {
        return lhs.id == rhs.id;
    }
};

/**
 * @brief Funzione di test per un albero binario di tipo int.
 */
void test_int_tree() {
    try {
        BinaryTree<int, IntCompare, IntEqual> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(8);
        tree.insert(1);
        tree.insert(4);

        std::cout << "Int Tree: " << tree << std::endl;

        std::cout << "Tree size: " << tree.size() << std::endl;
        std::cout << "Tree contains 3: " << (tree.exists(3) ? "Yes" : "No") << std::endl;
        std::cout << "Tree contains 7: " << (tree.exists(7) ? "Yes" : "No") << std::endl;

        BinaryTree<int, IntCompare, IntEqual> subtree = tree.subtree(3);
        std::cout << "Subtree rooted at 3: " << subtree << std::endl;

        BinaryTree<int, IntCompare, IntEqual> copiedTree = tree;
        std::cout << "Copied Tree: " << copiedTree << std::endl;

        BinaryTree<int, IntCompare, IntEqual> assignedTree;
        assignedTree = tree;
        std::cout << "Assigned Tree: " << assignedTree << std::endl;

        BinaryTree<int, IntCompare, IntEqual> treeEven;
        treeEven.insert(4);
        treeEven.insert(2);
        treeEven.insert(6);
        treeEven.insert(1);
        treeEven.insert(8);
        treeEven.insert(10);

        std::cout << "Tree for IsEven function test: " << treeEven << std::endl;

        std::cout << "Print only even int in the tree: ";
        printIF(treeEven, IsEven<int>());

    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

/**
 * @brief Funzione di test per un albero binario di tipo double.
 */
void test_double_tree() {
    try {
        BinaryTree<double, DoubleCompare, DoubleEqual> tree;
        tree.insert(5.5);
        tree.insert(3.3);
        tree.insert(8.8);
        tree.insert(1.1);
        tree.insert(4.4);

        std::cout << "Double Tree: " << tree << std::endl;

        std::cout << "Tree size: " << tree.size() << std::endl;
        std::cout << "Tree contains 3.3: " << (tree.exists(3.3) ? "Yes" : "No") << std::endl;
        std::cout << "Tree contains 7.7: " << (tree.exists(7.7) ? "Yes" : "No") << std::endl;

        BinaryTree<double, DoubleCompare, DoubleEqual> subtree = tree.subtree(3.3);
        std::cout << "Subtree rooted at 3.3: " << subtree << std::endl;

        BinaryTree<double, DoubleCompare, DoubleEqual> copiedTree = tree;
        std::cout << "Copied Tree: " << copiedTree << std::endl;

        BinaryTree<double, DoubleCompare, DoubleEqual> assignedTree;
        assignedTree = tree;
        std::cout << "Assigned Tree: " << assignedTree << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

/**
 * @brief Funzione di test per un albero binario di tipo string.
 */
void test_string_tree() {
    try {
        BinaryTree<std::string, StringCompare, StringEqual> tree;
        tree.insert("banana");
        tree.insert("apple");
        tree.insert("cherry");
        tree.insert("date");
        tree.insert("elderberry");

        std::cout << "String Tree: " << tree << std::endl;

        std::cout << "Tree size: " << tree.size() << std::endl;
        std::cout << "Tree contains 'apple': " << (tree.exists("apple") ? "Yes" : "No") << std::endl;
        std::cout << "Tree contains 'fig': " << (tree.exists("fig") ? "Yes" : "No") << std::endl;

        BinaryTree<std::string, StringCompare, StringEqual> subtree = tree.subtree("apple");
        std::cout << "Subtree rooted at 'apple': " << subtree << std::endl;

        BinaryTree<std::string, StringCompare, StringEqual> copiedTree = tree;
        std::cout << "Copied Tree: " << copiedTree << std::endl;

        BinaryTree<std::string, StringCompare, StringEqual> assignedTree;
        assignedTree = tree;
        std::cout << "Assigned Tree: " << assignedTree << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

/**
 * @brief Funzione di test per un albero binario di tipo CustomType.
 */
void test_custom_tree() {
    try {
        BinaryTree<CustomType, CustomTypeCompare, CustomTypeEqual> tree;

        CustomType ct1 = {1, "one"};
        CustomType ct2 = {2, "two"};
        CustomType ct3 = {3, "three"};
        CustomType ct4 = {4, "four"};
        CustomType ct5 = {5, "five"};
        CustomType ct6={6, "six"};

        tree.insert(ct1);
        tree.insert(ct2);
        tree.insert(ct3);
        tree.insert(ct4);
        tree.insert(ct5);

        std::cout << "CustomType Tree: " << tree << std::endl;

        std::cout << "Tree size: " << tree.size() << std::endl;
        std::cout << "Tree contains {2, 'two'}: " << (tree.exists(ct2) ? "Yes" : "No") << std::endl;
        std::cout << "Tree contains {6, 'six'}: " << (tree.exists(ct6) ? "Yes" : "No") << std::endl;

        BinaryTree<CustomType, CustomTypeCompare, CustomTypeEqual> subtree = tree.subtree(ct2);
        std::cout << "Subtree rooted at {2, 'two'}: " << subtree << std::endl;

        BinaryTree<CustomType, CustomTypeCompare, CustomTypeEqual> copiedTree = tree;
        std::cout << "Copied Tree: " << copiedTree << std::endl;

        BinaryTree<CustomType, CustomTypeCompare, CustomTypeEqual> assignedTree;
        assignedTree = tree;
        std::cout << "Assigned Tree: " << assignedTree << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

/**
 * @brief Funzione principale per eseguire i test dell'albero binario.
 * 
 * @return int Esito dell'esecuzione (0 se successo, altri valori per errore).
 */
int main() {
    std::cout << "Testing BinaryTree with int type:" << std::endl;
    test_int_tree();
    std::cout << std::endl;

    std::cout << "Testing BinaryTree with double type:" << std::endl;
    test_double_tree();
    std::cout << std::endl;

    std::cout << "Testing BinaryTree with string type:" << std::endl;
    test_string_tree();
    std::cout << std::endl;

    std::cout << "Testing BinaryTree with custom type:" << std::endl;
    test_custom_tree();
    std::cout << std::endl;

    return 0;
}
