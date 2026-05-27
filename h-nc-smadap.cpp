// Código de um compressor de Huffman com modelagem não contextual e semiadaptativo
// nesse caso estou considerando um alfabeto qualquer informado por mim e composto de chars
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "Node.h"

using namespace std;

// Variáveis globais
vector<char> alfabeto = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
string mensagem = "102450010211000703060090002450233004050060078600007688000785";
vector<int> cont(alfabeto.size(), 0); // contador para cada símbolo do alfabeto
list<pair<char, int>> nos_candidatos; // nós para poder formar uma junção

priority_queue<Node> pq; // considerando que eu tenho uma fila de prioridade, depois organizo melhor isso

void count(){
  for(int i = 0; i < mensagem.size(); i++){
    cont[(mensagem[i] - '0')]++;
  }
}

void init_nos(){
  for(int i = cont.size()-1; i >= 0; i--){
    if(cont[i] == 0){ // se aquele símbolo não aparece naquela mensagem não precisa colocá-lo na árvore
      continue;
    }

    auto it = nos_candidatos.begin(); // inicializa fora do loop para poder utilizar depois
    for(; it != nos_candidatos.end(); it++){ // itera procurando a posição de inserção daquele símbolo
      if(cont[i] >= it->second){
        break;
      }
    }

    nos_candidatos.insert(it, make_pair(alfabeto[i], cont[i])); // adiciona o símbolo na lista
  }
}

void build_huffman_tree(){
  // usar fila de prioridade na qual eu tenha acesso aos menores elementos
  // a lógica vai ser,
  // enquanto eu tiver dois nos candidatos
  // vou pegar os dois menores, dando dois pops na fila de prioridade
  // e vou adicionar um push na fila de prioridade, que já vai tratar o ordenamento
  // sempre que eu fizer esse processo eu vou construindo a árvore
  // fazendo as devidas ligações

  while(pq.size() >= 2){ // enquanto haver elementos para juntar
    // resgato os menorres elementos e os tiro da fila de prioridade
    auto aux2 = pq.top(); pq.pop();
    auto aux1 = pq.top(); pq.pop(); // aux1 >= aux2

    // Node node(cont, aux1, aux2); // cria o nó fazendo as devidas ligações

    // pq.push(node); // adiciona um novo nó
  }
}

int main(){
  count(); // conta a ocorrência de cada símbolo
  // fill_pq(); // preenche a fila de prioridade
  
  // verifica se a contagem está certa
  // cout << "Quantidade total de símbolos: " << mensagem.size() << endl;
  // cout << "Contagem de cada símbolo:\n";
  // for(int i = 0; i < cont.size(); i++){
  //   cout << "'" << alfabeto[i] << "': " << cont[i] << endl;
  // }


  init_nos(); // inicializa os nós inicialmente

  // verifica se a contagem está certa
  // cout << "Nós candidatos:\n";
  // for(auto it = nos_candidatos.begin(); it != nos_candidatos.end(); it++){
  //   cout << "('" << it->first << "', " << it->second << ")\n";
  // }

  build_huffman_tree(); // constrói a árvore de Huffman

  return 0;
}