// Código de um compressor de Huffman com modelagem não contextual e semiadaptativo
// nesse caso estou considerando um alfabeto qualquer informado por mim e composto de chars
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include "Node.h"

using namespace std;

// Variáveis globais
vector<char> alfabeto = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
string mensagem_original = "102450010211000703060090002450233004050060078600007688000785";
map<char, int> cont; // contador para cada símbolo do alfabeto

priority_queue<Node*, vector<Node*>, NodeComparator> pq; // fila de prioridade para gerar a árvore de Huffman
Node* root; // raiz da árvore de Huffman
map<char, string> tabela_de_codigos;

string mensagem_codificada;
string mensagem_decodificada;

void count(){
  for(int i = 0; i < mensagem_original.size(); i++){
    cont[mensagem_original[i]]++;
  }
}

void init_nos(){
  for(auto it : cont){
    if(it.second == 0){ // se aquele símbolo não aparece naquela mensagem não precisa colocá-lo na árvore
      continue;
    }

    Node* aux_node = new Node(it.second, it.first); // cria um nó considerando a contagem e o símbolo

    pq.push(aux_node); // adiciona o nó na fila de prioridade, considerando a contagem e o símbolo
  }
}

Node* build_huffman_tree(){
  // usar fila de prioridade na qual eu tenha acesso aos menores elementos
  // a lógica vai ser,
  // enquanto eu tiver dois nos candidatos
  // vou pegar os dois menores, dando dois pops na fila de prioridade
  // e vou adicionar um push na fila de prioridade, que já vai tratar o ordenamento
  // sempre que eu fizer esse processo eu vou construindo a árvore
  // fazendo as devidas ligações

  while(pq.size() >= 2){ // enquanto haver elementos para juntar
    // resgato os menores elementos e os tiro da fila de prioridade
    Node* aux2 = pq.top(); pq.pop();
    Node* aux1 = pq.top(); pq.pop(); // aux1 >= aux2

    Node* node = new Node(aux1->cont+aux2->cont, aux1, aux2); // cria o nó fazendo as devidas ligações

    // cout << "Novo nó: (Contador = " << node.cont << ")\n"; // debug

    pq.push(node); // adiciona um novo nó
  }

  // cout << "pq.size() = " << pq.size() << endl; // debug

  Node* root = pq.top(); pq.pop();

  return root;
}

void generate_codes(){
  string code = ""; // código de Huffman para cada símbolo
  stack<Node*> s;

  s.push(root); // começo o dfs pela raiz
  Node* aux_node;

  // a lógica vai ser,
  // desço para um nó, e verifico se é folha, se for já coloca o código
  // se não for desço para o filho esquerdo

  while(!s.empty()){
    aux_node = s.top();

    if((s.top()->left == nullptr) && (s.top()->right == nullptr)){ // se for um nó folha
      tabela_de_codigos[s.top()->simbolo] = code; // salva o código de Huffman para aquele símbolo
      cout << "Símbolo: '" << s.top()->simbolo << "', Código de Huffman: " << code << endl;

      s.top()->visited = 2; // marco que já visitei aquele nó folha, para não visitá-lo mais tarde
    }

    if(aux_node->visited == 0){
      s.push(aux_node->left);
      code += "0";
    } else if(aux_node->visited == 1){
      s.push(aux_node->right);
      code += "1";
    } else {
      s.pop();
      code.pop_back(); // tiro o último bit do código
      continue; // volto para o próximo elemento da pilha
    }

    aux_node->visited++; // marco que já visitei aquele nó
  }
}

void codificate_message(){
  mensagem_codificada = ""; // reseta a mensagem codificada

  for(int i = 0; i < mensagem_original.size(); i++){
    mensagem_codificada += tabela_de_codigos[mensagem_original[i]];
  }
}

void decodificate_message(){
  mensagem_decodificada = ""; // mensagem decodificada
  
  Node* aux_node = root; // começo o processo de decodificação pela raiz

  for(int i = 0; i < mensagem_codificada.size(); i++){
    if(mensagem_codificada[i] == '0'){
      aux_node = aux_node->left;
    }else{
      aux_node = aux_node->right;
    }

    if((aux_node->left == nullptr) && (aux_node->right == nullptr)){ // chegou em uma folha
      mensagem_decodificada += aux_node->simbolo;
      aux_node = root; // volta para a raiz
    }
  }
}

int main(){
  count(); // conta a ocorrência de cada símbolo
  
  // verifica se a contagem está certa
  // cout << "Quantidade total de símbolos: " << mensagem_original.size() << endl;
  // cout << "Contagem de cada símbolo:\n";
  // for(auto it : cont){
  //   cout << "'" << it.first << "': " << it.second << endl;
  // }

  init_nos(); // inicializa os nós inicialmente

  // verifica se a contagem está certa
  // cout << "Nós candidatos:\n";
  // while(pq.size() > 0){
  //   auto node = pq.top(); pq.pop();
  //   cout << "Símbolo: '" << node.simbolo << "', Contagem: " << node.cont << endl;
  // }

  root = build_huffman_tree(); // constrói a árvore de Huffman

  generate_codes(); // gera os códigos de Huffman para cada símbolo

  // for(auto it : tabela_de_codigos){
  //   cout << "Símbolo: '" << it.first << "', Código de Huffman: " << it.second << endl;
  // }

  codificate_message(); // codifica a mensagem original usando os códigos de Huffman gerados
  decodificate_message(); // decodifica a mensagem codificada usando a árvore de Huffman

  cout << "Mensagem original(" << mensagem_original.size() << " símbolos): " << mensagem_original << endl;
  cout << "Mensagem codificada(" << mensagem_codificada.size() << " bits): " << mensagem_codificada << endl;
  cout << "Mensagem decodificada(" << mensagem_decodificada.size() << " símbolos): " << mensagem_decodificada << endl;

  return 0;
}