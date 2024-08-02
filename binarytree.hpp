#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <functional>
#include <stdexcept> // Per std::runtime_error

/**
 * @brief Classe template per un albero binario.
 * 
 * @tparam T Tipo dei dati contenuti nel nodo dell'albero.
 * @tparam Compare Functore per confrontare due oggetti di tipo T.
 * @tparam Equal Functore per verificare l'uguaglianza tra due oggetti di tipo T.
 */
template<typename T, typename Compare = std::less<T>, typename Equal = std::equal_to<T> >
class BinaryTree {
private:
    /**
     * @brief Struttura per rappresentare un nodo dell'albero.
     */
    struct Node {
        T data; ///< Dato contenuto nel nodo.
        Node* left; ///< Puntatore al nodo figlio sinistro.
        Node* right; ///< Puntatore al nodo figlio destro.

        /**
         * @brief Costruttore di Node.
         * 
         * @param value Valore da assegnare al nodo.
         */
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root; ///< Radice dell'albero.
    Compare compare; ///< Functore per confrontare i dati.
    Equal equal; ///< Functore per verificare l'uguaglianza tra i dati.
    size_t node_count; ///< Numero di nodi nell'albero.

    /**
     * @brief Funzione ricorsiva per l'inserimento di un nodo nell'albero.
     * 
     * @param node Nodo corrente in cui inserire il valore.
     * @param value Valore da inserire nell'albero.
     * @return Node* Nodo radice aggiornato dopo l'inserimento.
     * @throw std::runtime_error Se il valore duplicato viene inserito.
     */
    Node* insert(Node* node, const T& value) {
        if (!node) {
            node_count++;
            return new Node(value);
        }
        if (equal(value, node->data)) {
            throw std::runtime_error("Duplicate element insertion is not allowed.");
        } else if (compare(value, node->data)) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    /**
     * @brief Funzione ricorsiva per verificare se un valore esiste nell'albero.
     * 
     * @param node Nodo corrente da cui iniziare la ricerca.
     * @param value Valore da cercare.
     * @return true Se il valore esiste nell'albero.
     * @return false Altrimenti.
     */
    bool exists(Node* node, const T& value) const {
        if (!node) {
            return false;
        }
        if (equal(node->data, value)) {
            return true;
        }
        if (compare(value, node->data)) {
            return exists(node->left, value);
        } else {
            return exists(node->right, value);
        }
    }

    /**
     * @brief Trova il sottoalbero con radice contenente un dato valore.
     * 
     * @param node Nodo corrente da cui iniziare la ricerca.
     * @param value Valore da cercare nel sottoalbero.
     * @return Node* Radice del sottoalbero contenente il valore, se trovato; altrimenti nullptr.
     */
    Node* find_subtree(Node* node, const T& value) const {
        if (!node) {
            return nullptr;
        }
        if (equal(node->data, value)) {
            return node;
        }
        if (compare(value, node->data)) {
            return find_subtree(node->left, value);
        } else {
            return find_subtree(node->right, value);
        }
    }

    /**
     * @brief Stampa in ordine (in-order traversal) l'albero a partire da un nodo dato.
     * 
     * @param node Nodo corrente da cui iniziare la stampa.
     * @param os Stream di output su cui stampare.
     */
    void print_in_order(Node* node, std::ostream& os) const {
        if (!node) {
            return;
        }
        print_in_order(node->left, os);
        os << node->data << " ";
        print_in_order(node->right, os);
    }

    /**
     * @brief Distrugge ricorsivamente l'intero albero a partire da un nodo dato.
     * 
     * @param node Nodo corrente da cui iniziare la distruzione.
     */
    void destroy_tree(Node* node) {
        if (!node) {
            return;
        }
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }

    /**
     * @brief Copia ricorsivamente un sottoalbero a partire da un nodo sorgente.
     * 
     * @param dest Radice del sottoalbero di destinazione.
     * @param src Radice del sottoalbero sorgente da copiare.
     */
    void copy_subtree(Node*& dest, Node* src) const {
        if (!src) {
            return;
        }
        dest = new Node(src->data);
        if (src->left) {
            copy_subtree(dest->left, src->left);
        }
        if (src->right) {
            copy_subtree(dest->right, src->right);
        }
    }

public:
    /**
     * @brief Costruttore di default per creare un albero vuoto.
     */
    BinaryTree() : root(nullptr), node_count(0) {}

    /**
     * @brief Costruttore che crea un albero a partire da una sequenza di elementi.
     * 
     * @tparam InputIt Tipo dell'iteratore di input.
     * @param first Iteratore all'inizio della sequenza.
     * @param last Iteratore alla fine della sequenza.
     * @param comp Functore per confrontare due oggetti di tipo T.
     * @param eq Functore per verificare l'uguaglianza tra due oggetti di tipo T.
     */
    template<typename InputIt>
    BinaryTree(InputIt first, InputIt last, Compare comp = Compare(), Equal eq = Equal())
        : root(nullptr), compare(comp), equal(eq), node_count(0) {
        try {
            for (InputIt it = first; it != last; ++it) {
                insert(*it);
            }
        } catch (std::exception& e) {
            destroy_tree(root);
            throw; // Rilancia l'eccezione
        }
    }

    /**
     * @brief Costruttore di copia per creare un albero identico a un altro.
     * 
     * @param other Altro oggetto BinaryTree da cui copiare.
     */
    BinaryTree(const BinaryTree& other) : root(nullptr), compare(other.compare), equal(other.equal), node_count(0) {
        try {
            if (other.root) {
                copy_subtree(root, other.root);
                node_count = other.node_count;
            }
        } catch (std::exception& e) {
            destroy_tree(root);
            throw; // Rilancia l'eccezione
        }
    }

    /**
     * @brief Operatore di assegnazione per copiare un albero in un altro.
     * 
     * @param other Altro oggetto BinaryTree da cui copiare.
     * @return BinaryTree& Referenza a se stesso dopo l'assegnazione.
     */
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            destroy_tree(root);
            root = nullptr;
            node_count = 0;
            compare = other.compare;
            equal = other.equal;
            try {
                if (other.root) {
                    copy_subtree(root, other.root);
                    node_count = other.node_count;
                }
            } catch (std::exception& e) {
                destroy_tree(root);
                throw; // Rilancia l'eccezione
            }
        }
        return *this;
    }

    /**
     * @brief Distruttore che libera la memoria dell'albero.
     */
    ~BinaryTree() {
        destroy_tree(root);
    }

    /**
     * @brief Inserisce un nuovo valore nell'albero.
     * 
     * @param value Valore da inserire.
     * @throw std::runtime_error Se il valore duplicato viene inserito.
     */
    void insert(const T& value) {
        try {
            root = insert(root, value);
        } catch (std::exception& e) {
            throw; // Rilancia l'eccezione
        }
    }

    /**
     * @brief Verifica se un valore esiste nell'albero.
     * 
     * @param value Valore da cercare.
     * @return true Se il valore esiste nell'albero.
     * @return false Altrimenti.
     * @throw std::runtime_error Se si verifica un errore durante la ricerca.
     */
    bool exists(const T& value) const {
        try {
            return exists(root, value);
        } catch (std::exception& e) {
            throw; // Rilancia l'eccezione
        }
    }

    /**
     * @brief Restituisce il numero di nodi nell'albero.
     * 
     * @return size_t Numero di nodi nell'albero.
     */
    size_t size() const {
        return node_count;
    }

    /**
     * @brief Restituisce un sottoalbero con radice contenente un dato valore.
     * 
     * @param value Valore da cercare nel sottoalbero.
     * @return BinaryTree Sottoalbero con radice contenente il valore, se trovato.
     * @throw std::runtime_error Se si verifica un errore durante la ricerca.
     */
    BinaryTree subtree(const T& value) const {
        BinaryTree sub_tree;
        try {
            Node* subtree_root = find_subtree(root, value);
            if (subtree_root) {
                copy_subtree(sub_tree.root, subtree_root);
                sub_tree.node_count = sub_tree.count_nodes(sub_tree.root);
            }
        } catch (std::exception& e) {
            throw; // Rilancia l'eccezione
        }
        return sub_tree;
    }

    /**
     * @brief Conta il numero di nodi in un sottoalbero a partire da un dato nodo.
     * 
     * @param node Nodo radice del sottoalbero di cui contare i nodi.
     * @return size_t Numero di nodi nel sottoalbero.
     */
    size_t count_nodes(Node* node) const {
        if (!node) {
            return 0;
        }
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }


    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
        try {
            tree.print_in_order(tree.root, os);
        } catch (std::exception& e) {
            throw; // Rilancia l'eccezione
        }
        return os;
    }
    public:  
    /**
     * @brief Iterator costante per attraversare l'albero in ordine.
     */
    class const_iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category; ///< Categoria dell'iteratore.
        typedef std::ptrdiff_t difference_type; ///< Tipo per la differenza tra iteratori.
        typedef T value_type; ///< Tipo del valore puntato dall'iteratore.
        typedef const T* pointer; ///< Tipo del puntatore al valore.
        typedef const T& reference; ///< Tipo del riferimento al valore.

    private:
        Node *current; ///< Puntatore al nodo corrente dell'iteratore.
        Node *root;    ///< Puntatore alla radice dell'albero.

        /**
         * @brief Trova il nodo successivo nell'attraversamento in ordine.
         * 
         * @param node Nodo corrente da cui trovare il successivo.
         * @return Node* Nodo successivo nell'attraversamento.
         */
        Node *findNext(Node *node) const
        {
            if (node->right != nullptr)
            {
                Node *next = node->right;
                while (next->left != nullptr)
                {
                    next = next->left;
                }
                return next;
            }
            else
            {
                Node *successor = nullptr;
                Node *ancestor = root;
                while (ancestor != node)
                {
                    if (node->data < ancestor->data)
                    {
                        successor = ancestor;
                        ancestor = ancestor->left;
                    }
                    else
                    {
                        ancestor = ancestor->right;
                    }
                }
                return successor;
            }
        }

    public:
        /**
         * @brief Costruttore dell'iteratore costante.
         * 
         * @param node Nodo iniziale dell'iteratore.
         * @param root Radice dell'albero.
         */
        const_iterator(Node *node, Node *root) : current(node), root(root)
        {
            if (current != nullptr)
            {
                while (current->left != nullptr)
                {
                    current = current->left;
                }
            }
        }

        /**
         * @brief Operatore di dereferenziazione.
         * 
         * @return const T& Valore riferenziato dall'iteratore.
         */
        const T &operator*() const
        {
            return current->data;
        }

        /**
         * @brief Operatore di pre-incremento.
         * 
         * @return const_iterator& Referenza a se stesso dopo l'incremento.
         */
        const_iterator &operator++()
        {
            if (current != nullptr)
            {
                current = findNext(current);
            }
            return *this;
        }

        /**
         * @brief Operatore di confronto per l'uguaglianza.
         * 
         * @param other Altro iteratore da confrontare.
         * @return true Se i due iteratori puntano allo stesso nodo.
         * @return false Altrimenti.
         */
        bool operator==(const const_iterator &other) const
        {
            return current == other.current;
        }

        /**
         * @brief Operatore di confronto per l'ineguaglianza.
         * 
         * @param other Altro iteratore da confrontare.
         * @return true Se i due iteratori puntano a nodi diversi.
         * @return false Altrimenti.
         */
        bool operator!=(const const_iterator &other) const
        {
            return !(*this == other);
        }
    };

    /**
     * @brief Restituisce l'iteratore costante per il primo nodo in ordine (più piccolo).
     * 
     * @return const_iterator Iteratore costante per il primo nodo in ordine.
     */
    const_iterator begin() const
    {
        return const_iterator(root, root);
    }

    /**
     * @brief Restituisce l'iteratore costante di fine per l'attraversamento in ordine.
     * 
     * @return const_iterator Iteratore costante di fine.
     */
    const_iterator end() const {
        return const_iterator(nullptr, root);
    }

};

/**
 * @brief Operatore di stream per stampare l'albero in ordine.
 * 
 * @tparam T Tipo dei dati contenuti nell'albero.
 * @tparam Compare Functore per confrontare due oggetti di tipo T.
 * @tparam Equal Functore per verificare l'uguaglianza tra due oggetti di tipo T.
 * @param os Stream di output su cui stampare.
 * @param tree Albero binario da stampare.
 * @return std::ostream& Stream di output aggiornato.
 */
template <typename T, typename Compare, typename Equal>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T, Compare, Equal>& tree) {
    try {
        tree.print_in_order(tree.root, os);
    } catch (std::exception& e) {
        throw; // Rilancia l'eccezione
    }
    return os;
}

/**
 * @brief Funzione per stampare gli elementi di un albero che soddisfano un predicato.
 * 
 * @tparam T Tipo dei dati contenuti nell'albero.
 * @tparam Compare Functore per confrontare due oggetti di tipo T.
 * @tparam Equal Functore per verificare l'uguaglianza tra due oggetti di tipo T.
 * @tparam Predicate Functore per il predicato di selezione.
 * @param tree Albero binario da esaminare.
 * @param pred Predicato da applicare agli elementi dell'albero.
 */
template <typename T, typename Compare, typename Equal, typename Predicate>
void printIF(const BinaryTree<T, Compare, Equal>& tree, Predicate pred) {
    for (typename BinaryTree<T, Compare, Equal>::const_iterator it = tree.begin(); it != tree.end(); ++it) {
        if (pred(*it)) {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl;
}

#endif // BINARYTREE_HPP
