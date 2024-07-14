/*
PAULO HENRIQUE ARAÚJO BENTO
Matrícula - 535543
*/

#include <iostream>
#include <vector>
#include "set.h"

using namespace std;

void printMenu() {
    cout << "\n===================================================" << endl;
    cout << "                       -                           " << endl;
    cout << "OBS: como o conjunto T terá importância" << endl;
    cout << "somente na função SWAP(), resolvi então" << endl;
    cout << "fazer com que as únicas operações com o" << endl;
    cout << "conjunto T fossem de inserir, remover e" << endl;
    cout << "visualizar para que o menu não ficasse" << endl;
    cout << "tão poluído." << endl;
    cout << "                       -                           " << endl;
    cout << "====================== Menu: ======================" << endl;
    cout << "1. Inserir elemento no conjunto S" << endl;
    cout << "2. Inserir elemento no conjunto T" << endl;
    cout << "3. Remover elemento do conjunto S" << endl;
    cout << "4. Remover elemento do conjunto T" << endl;
    cout << "5. Verificar se contém elemento no conjunto S" << endl;
    cout << "6. Encontrar mínimo no conjunto S" << endl;
    cout << "7. Encontrar máximo no conjunto S" << endl;
    cout << "8. Encontrar sucessor no conjunto S" << endl;
    cout << "9. Encontrar predecessor no conjunto S" << endl;
    cout << "10. Verificar se a árvore do conjunto S está vazia" << endl;
    cout << "11. Verificar o tamanho da árvore do conjunto S" << endl;
    cout << "12. Mostrar a árvore do conjunto S" << endl;
    cout << "13. Mostrar a árvore do conjunto T" << endl;
    cout << "14. Realizar o SWAP" << endl;
    cout << "15. UNIÃO entre o conjunto S e T" << endl;
    cout << "16. INTERSECÇÃO entre S e T" << endl;
    cout << "17. DIFERENÇA entre S e T" << endl;
    cout << "0. Sair" << endl;
    cout << "==================================================" << endl;
    cout << "Escolha uma opção: ";
}

int main() {
    setTree treeS, treeT;
    int option, value, quantity;

    while (true) {
        printMenu();
        cin >> option;

        switch (option) {
            case 1: // Inserir elemento
                cout << "Adicionar elemento no conjunto S" << endl;
                cout << "Digite a quantidade: ";
                cin >> quantity;
                for(int i = 0; i < quantity; i++) {
                    cin >> value;
                    treeS.insert(value);
                }
                cout << "Valores inseridos no conjunto S" << endl;
                break;

            case 2: // Inserir elemento
                cout << "Adicionar elemento no conjunto T" << endl;
                cout << "Digite a quantidade: ";
                cin >> quantity;
                for(int i = 0; i < quantity; i++) {
                    cin >> value;
                    treeT.insert(value);
                }
                cout << "Valores inseridos no conjunto T" << endl;
                break;

            case 3: // Remover elemento
                cout << "Removendo valor do conjunto S" << endl;
                cout << "Digite o valor para remover: ";
                cin >> value;
                treeS.erase(value);
                break;

            case 4: // Remover elemento
                cout << "Removendo valor do conjunto T" << endl;
                cout << "Digite o valor para remover: ";
                cin >> value;
                treeT.erase(value);
                break;

            case 5: // Verificar se contém elemento
                cout << "Verificando se há um valor no conjunto S" << endl;
                cout << "Digite o valor para verificar: ";
                cin >> value;
                if (treeS.contains(value)) {
                    cout << "O valor está na árvore." << endl;
                } else {
                    cout << "O valor não está na árvore." << endl;
                }
                break;

            case 6: // Encontrar mínimo
                if (!treeS.empty()) {
                    cout << "O mínimo valor é: " << treeS.minimum() << endl;
                } else {
                    cout << "A árvore está vazia." << endl;
                }
                break;

            case 7: // Encontrar máximo
                if (!treeS.empty()) {
                    cout << "O máximo valor é: " << treeS.maximum() << endl;
                } else {
                    cout << "A árvore está vazia." << endl;
                }
                break;

            case 8: // Encontrar sucessor
                cout << "Digite o valor para encontrar o sucessor: ";
                cin >> value;
                try {
                    cout << "O sucessor do valor é: " << treeS.successor(value) << endl;
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;

            case 9: // Encontrar predecessor
                cout << "Digite o valor para encontrar o predecessor: ";
                cin >> value;
                try {
                    cout << "O predecessor do valor é: " << treeS.predecessor(value) << endl;
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;

            case 10: // Verificar se a árvore está vazia
                if (treeS.empty()) {
                    cout << "A árvore está vazia." << endl;
                } else {
                    cout << "A árvore não está vazia." << endl;
                }
                break;

            case 11: // Verificar o tamanho da árvore
                cout << "O tamanho da árvore é: " << treeS.size() << endl;
                break;

            case 12: // Mostrar a árvore
                cout << "Mostrar árvore do conjunto S" << endl;
                treeS.bshow();
                break;

            case 13: // Mostrar a árvore
                cout << "Mostrar árvore do conjunto T" << endl;
                treeT.bshow();
                break;

            case 14: // SWAP()
                cout << "Trocando conjunto S pelo conjunto T" << endl;
                treeS.swap(treeT);
                break;

            case 15: // UNION()
                cout << "UNIÃO do conjunto S e conjunto T" << endl;
                treeS.union_ensemble(treeT);
                break;

            case 16: // INTERSECTION()
                cout << "INTERSECÇÃO do conjunto S e T" << endl;
                treeS.intersection(treeT);
                break;

            case 17: // DIFFERENCE()
                cout << "DIFERENÇA entre o conjunto S e T" << endl;
                treeS.difference(treeT);
                break;

            case 0: // Sair
                return 0;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    }

    return 0;
}
