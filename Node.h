#pragma once

class Node{
  public:
    int cont;
    char simbolo; // nesse caso vai ser char para o alfabeto em especifico
    Node* left;
    Node* right;
    int visited = 0; // para o dfs

    Node(int cont, char simbolo){
      this->cont = cont;
      this->simbolo = simbolo;
      this->left = nullptr;
      this->right = nullptr;
    }

    Node(int cont, Node* left, Node* right){
      this->cont = cont;
      this->simbolo = '\0'; // nó interno não tem símbolo
      this->left = left;
      this->right = right;
    }
};

class NodeComparator{
  public:
    bool operator()(Node* a, Node* b){
      return a->cont > b->cont; // ordena por contagem crescente
    }
};