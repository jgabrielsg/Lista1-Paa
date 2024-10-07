#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <climits> // Para INT32_MAX

using namespace std;

// Função para gerar uma lista de inteiros aleatórios de tamanho n
// Aqui geramos um array com n elementos aleatórios dentro de um intervalo
void generateRandomArray(int arr[], int n, int range_min, int range_max) {
    srand(time(0)); // Inicializamos o gerador de números aleatórios
    for (int i = 0; i < n; i++) {
        arr[i] = range_min + rand() % (range_max - range_min + 1); // Geramos números no intervalo [range_min, range_max]
    }
}

// Função auxiliar para imprimir um array de inteiros
// Aqui percorremos o array e imprimimos seus valores
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "; // Imprimimos cada elemento do array
    }
    cout << endl;
}

// ==================== QUESTÃO 7 ====================
// Função para ordenar frequências com Counting Sort
// Utilizamos essa função auxiliar para ordenar as frequências do array
void countingSortFrequency(int frequency_array[][2], int k_range) {
    int max_freq = frequency_array[0][1];
    for (int i = 1; i < k_range; i++) {
        if (frequency_array[i][1] > max_freq) {
            max_freq = frequency_array[i][1]; // Encontramos a maior frequência
        }
    }

    // Criamos um array de contagem
    int count[max_freq + 1] = {0};
    int sorted_array[k_range][2]; // Usamos isso para armazenar a frequência temporariamente

    // Inicializamos o array de contagem
    for (int i = 0; i <= max_freq; i++) {
        count[i] = 0;
    }

    // Contamos as ocorrências das frequências
    for (int i = 0; i < k_range; i++) {
        count[frequency_array[i][1]]++;
    }

    // Ajustamos o array de contagem
    for (int i = 1; i <= max_freq; i++) {
        count[i] += count[i - 1];
    }

    // Usamos o array de contagem para ordenar as frequências
    for (int i = k_range - 1; i >= 0; i--) {
        int freq = frequency_array[i][1];
        int pos = count[freq] - 1;
        sorted_array[pos][0] = frequency_array[i][0];
        sorted_array[pos][1] = frequency_array[i][1];
        count[freq]--;
    }

    // Transferimos os valores ordenados de volta ao array original
    for (int i = 0; i < k_range; i++) {
        frequency_array[i][0] = sorted_array[i][0];
        frequency_array[i][1] = sorted_array[i][1];
    }
}

// Função principal para encontrar o k-ésimo elemento mais frequente
// Primeiro contamos as frequências, depois ordenamos e então encontramos o k-ésimo elemento
int findKthMostFrequent(const int arr[], int n, int k_search) {
    // Encontramos o maior e menor valor do array
    int max_value = arr[0];
    int min_value = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    // Calculamos o range e criamos uma matriz para armazenar os números e suas frequências
    int k_range = (max_value - min_value) + 1;
    int frequency_array[k_range][2];

    // Inicializamos a frequência de cada número com 0
    for (int i = 0; i < k_range; i++) {
        frequency_array[i][0] = (min_value + i);
        frequency_array[i][1] = 0;
    }

    // Contamos quantas vezes cada número aparece no array
    for (int i = 0; i < n; i++) {
        frequency_array[arr[i] - min_value][1] += 1;
    }

    // Usamos counting sort para ordenar as frequências
    countingSortFrequency(frequency_array, k_range);

    // Retornamos o k-ésimo número mais frequente
    return frequency_array[k_range - k_search][0];
}

// ==================== QUESTÃO 8 ====================
// Função para encontrar um par de números que somam X
// Aqui buscamos no array um par de números que, somados, dão o valor X
bool findPairWithSum(int arr[], int n, int x) {
    unordered_set<int> seenNumbers; // Usamos um conjunto para armazenar os números já vistos

    for (int i = 0; i < n; i++) {
        int complement = x - arr[i]; // Calculamos o complemento necessário para a soma ser x
        if (seenNumbers.find(complement) != seenNumbers.end()) {
            // Se encontramos o complemento, imprimimos o par
            cout << "Par encontrado: (" << arr[i] << ", " << complement << ")\n";
            return true;
        }
        seenNumbers.insert(arr[i]); // Adicionamos o número ao conjunto de números vistos
    }

    cout << "Nenhum par encontrado.\n";
    return false;
}

// ==================== QUESTÃO 9 ====================
// Função para contar quantas listas possuem elementos únicos
// Aqui verificamos se as listas têm elementos em comum
int numberOfSoloLists(int* arr[], int n, int m) {
    unordered_map<int, int> freqMap; // Mapeamos a frequência de cada número entre todas as listas

    // Contamos quantas vezes cada número aparece em todas as listas
    for (int i = 0; i < m; i++) {
        unordered_set<int> freqList; // Usamos um conjunto para garantir que não contamos o mesmo número duas vezes na mesma lista

        for (int j = 0; j < n; j++) {
            if (freqList.find(arr[i][j]) == freqList.end()) {
                freqList.insert(arr[i][j]); // Adicionamos o número à lista temporária
                freqMap[arr[i][j]]++; // Aumentamos a contagem do número no mapa
            }
        }
    }

    // Verificamos quantas listas não têm elementos em comum com outras listas
    int soloListsCount = 0;
    for (int i = 0; i < m; i++) {
        bool isSolo = true;
        for (int j = 0; j < n; j++) {
            if (freqMap[arr[i][j]] > 1) {
                isSolo = false; // Se algum número aparece mais de uma vez, essa lista não é "solo"
                break;
            }
        }
        if (isSolo) {
            soloListsCount++; // Contamos quantas listas são "solo"
        }
    }

    return soloListsCount; // Retornamos o número de listas sem elementos repetidos
}

// ==================== QUESTÃO 10 ====================
// Função para encontrar o valor de X para o qual o número de elementos >= X é igual a X
// Utilizamos um array de frequências acumuladas para contar os elementos
int findX(int arr[], int n) {
    int freq_arr[n + 2] = {0}; // Criamos um array de frequência com n+2 posições para incluir o caso de n+1
    for (int i = 0; i < n; i++) {
        if (arr[i] > n) {
            freq_arr[n + 1]++; // Contamos quantos números são maiores que n
        } else {
            freq_arr[arr[i]]++; // Contamos quantas vezes cada número aparece
        }
    }

    // Calculamos a soma acumulada das frequências
    int accum_arr[n + 2] = {0};
    accum_arr[0] = freq_arr[0];
    for (int i = 1; i <= n + 1; i++) {
        accum_arr[i] = freq_arr[i] + accum_arr[i - 1];
    }

    // Modificamos o array acumulado para que cada posição tenha o número de elementos >= i
    accum_arr[0] = 0;
    for (int i = 0; i <= n + 1; i++) {
        accum_arr[i] = n - accum_arr[i] + freq_arr[i];
    }

    // Procuramos o maior valor de X onde o número de elementos >= X seja igual a X
    for (int i = n + 1; i >= 0; i--) {
        if ((i <= accum_arr[i]) && (freq_arr[i] != 0)) {
            return i;
        }
    }

    return -1; // Se não encontramos X, retornamos -1
}

// ==================== QUESTÃO 11 ====================
// Estrutura de nó da árvore binária
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Função para inserir um valor na árvore binária de busca (BST)
TreeNode* insertBST(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value); // Se a raiz é nula, criamos o primeiro nó
    }

    TreeNode* parent = nullptr;
    TreeNode* current = root;

    // Procuramos a posição correta para inserir o novo nó
    while (current != nullptr) {
        parent = current;
        if (value < current->value) {
            current = current->left; // Se o valor for menor, vamos para a esquerda
        } else {
            current = current->right; // Se o valor for maior ou igual, vamos para a direita
        }
    }

    // Criamos o novo nó e o conectamos ao pai
    TreeNode* newNode = new TreeNode(value);
    newNode->parent = parent;
    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Função para construir uma árvore binária de busca (BST) a partir de um array
TreeNode* buildBST(const int arr[], int n) {
    TreeNode* root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insertBST(root, arr[i]); // Inserimos cada elemento na árvore
    }
    return root;
}

// Função para fazer a travessia in-order da árvore (imprime em ordem crescente)
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left); // Primeiro, percorremos a subárvore esquerda
    cout << root->value << " "; // Depois, imprimimos o valor da raiz
    inorderTraversal(root->right); // Finalmente, percorremos a subárvore direita
}

// Função recursiva para encontrar a menor diferença entre nós consecutivos
void findMinRecursive(TreeNode* root, int& prev, int& minDiff) {
    if (root == nullptr) return;
    findMinRecursive(root->left, prev, minDiff); // Percorremos a subárvore esquerda
    if (prev != -1) {
        int diff = abs(root->value - prev); // Calculamos a diferença com o nó anterior
        if (diff < minDiff) {
            minDiff = diff; // Atualizamos a menor diferença encontrada
        }
    }
    prev = root->value; // Atualizamos o valor do nó anterior
    findMinRecursive(root->right, prev, minDiff); // Percorremos a subárvore direita
}

// Função para encontrar a menor diferença entre nós de uma árvore binária
int findMinDifference(TreeNode* root) {
    int prev = -1; // Inicializamos o valor anterior como -1 (indicando que não há valor ainda)
    int minDiff = INT32_MAX; // Inicializamos a menor diferença como um valor muito alto

    findMinRecursive(root, prev, minDiff); // Chamamos a função recursiva para calcular a menor diferença
    return minDiff;
}

// ==================== QUESTÃO 12 ====================
// Função para aplicar max-heapify em uma heap de pares (diferença, valor original)
void maxHeapify(int heap[][2], int heapSize, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left][0] > heap[largest][0])
        largest = left;

    if (right < heapSize && heap[right][0] > heap[largest][0])
        largest = right;

    if (largest != i) {
        swap(heap[i][0], heap[largest][0]); // Troca a diferença
        swap(heap[i][1], heap[largest][1]); // Troca o valor original
        maxHeapify(heap, heapSize, largest);
    }
}

// Função para realizar heapsort em um array de pares (diferença, valor original)
void heapSort(int heap[][2], int k) {
    // Constrói a max-heap
    for (int i = k / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, k, i);
    }

    // Extrai os elementos da heap um a um
    for (int i = k - 1; i >= 0; i--) {
        // Move o maior para o final
        swap(heap[0][0], heap[i][0]); // Troca a diferença
        swap(heap[0][1], heap[i][1]); // Troca o valor original

        // Reduz o tamanho da heap e reheapifica
        maxHeapify(heap, i, 0);
    }
}

// Função para encontrar os k elementos mais próximos de x
int* closestToX(int arr[], int n, int k, int x) {
    int diffArr[n];

    // Calculamos as diferenças em relação a x
    for (int i = 0; i < n; i++) {
        diffArr[i] = abs(x - arr[i]); // Diferença de cada elemento para x
    }

    // Inicializa a heap com os primeiros k elementos
    int heap[k][2];
    for (int i = 0; i < k; i++) {
        heap[i][0] = diffArr[i];  // Primeira coluna: diferença
        heap[i][1] = arr[i];      // Segunda coluna: valor original
    }

    // Constrói a max-heap
    for (int i = k / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, k, i);
    }

    // Processa os elementos restantes
    for (int i = k; i < n; i++) {
        if (diffArr[i] < heap[0][0]) { // Se a diferença é menor que a maior da heap
            heap[0][0] = diffArr[i];  // Atualiza a diferença
            heap[0][1] = arr[i];      // Atualiza o valor original
            maxHeapify(heap, k, 0);   // Reheapifica
        }
    }

    // Ordena a heap usando heapsort
    heapSort(heap, k);

    // Prepara o array de resultados
    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = heap[i][1];  // Pega os valores originais
    }

    return result;
}

// ==================== QUESTÃO 13 ====================
// Função que retorna o maior subconjunto onde a maior diferença é <= x
int* mostElementsInInterval(int arr[], int n, int x, int &resultSize) {
    // Ordenamos o array
    sort(arr, arr + n);

    int start = 0;
    int maxInterval = 0;
    int maxStart = 0; // Para rastrear o início do maior intervalo

    // Janela deslizante
    for (int end = 0; end < n; end++) {
        // Enquanto a diferença entre o maior e o menor for maior que x, movemos o início
        while (arr[end] - arr[start] > x) {
            start++;
        }

        int intervalSize = end - start + 1;

        // Atualiza o início e tamanho do maior intervalo
        if (intervalSize > maxInterval) {
            maxInterval = intervalSize;
            maxStart = start;
        }
    }

    // Agora, aloca dinamicamente o array de saída com base no tamanho do maior intervalo
    resultSize = maxInterval;
    int* output = new int[resultSize];
    
    // Preenche o array de saída com os elementos do maior intervalo encontrado
    for (int i = 0; i < resultSize; i++) {
        output[i] = arr[maxStart + i];
    }

    return output; // Retorna o ponteiro para o array dinâmico
}

// ==================== QUESTÃO 14 ====================
// Função que encontra o par de índices (i, j) que maximizam |i - j| * min{A[i], A[j]}
int** maximumPair(int arr[], int n) {
    int max_result = INT32_MIN;
    int result;

    // Alocando uma matriz bidimensional dinamicamente
    int** pair = new int*[2];
    pair[0] = new int[2];
    pair[1] = new int[2];
    
    int i = 0;
    int j = n - 1;
    
    while (i < j) {
        // Calculamos o resultado para o par atual
        result = (j - i) * min(arr[i], arr[j]);
        
        if (result > max_result) {
            // Se encontramos um novo máximo, atualizamos o par de índices e valores
            max_result = result;
            pair[0][0] = arr[i]; // valor em i
            pair[0][1] = i;      // índice i
            pair[1][0] = arr[j]; // valor em j
            pair[1][1] = j;      // índice j
        }
        
        // Movemos os ponteiros de acordo com os valores dos elementos
        if (arr[i] < arr[j]) {
            i++;
        } else {
            j--;
        }
    }
    
    return pair;
}

// ==================== QUESTÃO 15 ====================
// Função recursiva para criar uma árvore binária balanceada
TreeNode* createBalancedTree(int arr[], int n) {
    if (n == 0) return nullptr; // Caso base: se o array estiver vazio, retornamos nullptr
    
    // Ordenamos o array para garantir que a árvore seja uma BST balanceada
    sort(arr, arr + n);
    
    // Encontramos o elemento do meio e tornamos ele a raiz da árvore
    int mid = n / 2;
    TreeNode* root = new TreeNode(arr[mid]);

    // Criamos arrays para as subárvores esquerda e direita
    int* arrLeft = new int[mid]; // O array esquerdo tem 'mid' elementos
    int* arrRight = new int[n - mid - 1]; // O array direito tem 'n - mid - 1' elementos

    // Preenchemos os arrays para subárvore esquerda e direita
    for (int i = 0; i < mid; i++) {
        arrLeft[i] = arr[i];
    }

    for (int i = mid + 1; i < n; i++) {
        arrRight[i - (mid + 1)] = arr[i]; // Ajustamos o índice ao preencher arrRight
    }

    // Recursivamente criamos as subárvores esquerda e direita
    root->left = createBalancedTree(arrLeft, mid);
    root->right = createBalancedTree(arrRight, n - mid - 1);

    return root; // Retornamos a raiz da árvore
}

// Função auxiliar para calcular a altura de uma árvore
int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0; // Se a árvore for vazia, a altura é 0
    }
    
    int leftHeight = getHeight(root->left); // Calculamos a altura da subárvore esquerda
    int rightHeight = getHeight(root->right); // Calculamos a altura da subárvore direita
    
    return max(leftHeight, rightHeight) + 1; // Retornamos a altura total
}

// Função para verificar se uma árvore está balanceada
bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
        return true; // Uma árvore vazia é considerada balanceada
    }

    int leftHeight = getHeight(root->left); // Calculamos a altura da subárvore esquerda
    int rightHeight = getHeight(root->right); // Calculamos a altura da subárvore direita

    // Verificamos se a diferença de altura entre subárvores é maior que 1
    if (abs(leftHeight - rightHeight) > 1) {
        return false; // Se a diferença for maior que 1, a árvore não é balanceada
    }

    // Recursivamente verificamos se as subárvores esquerda e direita são balanceadas
    return isBalanced(root->left) && isBalanced(root->right);
}


// ==================== FUNÇÃO MAIN ====================
int main() {
    int n = 15;
    int range_min = 1, range_max = 25;
    
    // ============ QUESTÃO 7 ============
    cout << "============ QUESTÃO 7 ============\n";
    int arr_q7[n];
    generateRandomArray(arr_q7, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q7, n);

    int k_search = 3;
    int kthMostFrequent = findKthMostFrequent(arr_q7, n, k_search);
    cout << k_search << "th elemento mais frequente: " << kthMostFrequent << endl << endl;

    // ============ QUESTÃO 8 ============
    cout << "============ QUESTÃO 8 ============\n";
    int arr_q8[n];
    generateRandomArray(arr_q8, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q8, n);

    int x = 16;
    findPairWithSum(arr_q8, n, x);
    cout << "que soma " << x << endl << endl;

    // ============ QUESTÃO 9 ============
    cout << "============ QUESTÃO 9 ============\n";
    n = 10;
    int m = 6;
    int arr1[n], arr2[n], arr3[n], arr4[n], arr5[n], arr6[n]; 
    generateRandomArray(arr1, n, 0, 1);
    generateRandomArray(arr2, n, 0, 1);
    generateRandomArray(arr3, n, -2, -1);
    generateRandomArray(arr4, n, 5, 6);
    generateRandomArray(arr5, n, 0, 1);
    generateRandomArray(arr6, n, 0, 1);

    int* dimArr[] = {arr1, arr2, arr3, arr4, arr5, arr6};
    
    int soloLists = numberOfSoloLists(dimArr, n, m);
    cout << "Número de listas sem elementos em comum: " << soloLists << endl << endl;

    // ============ QUESTÃO 10 ============
    cout << "============ QUESTÃO 10 ============\n";
    n = 15;
    int arr_q10[n];
    generateRandomArray(arr_q10, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q10, n);

    int theX = findX(arr_q10, n);
    cout << theX << " é o numero x" << endl << endl;

    // ============ QUESTÃO 11 ============
    cout << "============ QUESTÃO 11 ============\n";
    n = 15;
    int arr_q11[n];
    generateRandomArray(arr_q11, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q11, n);

    TreeNode* root = buildBST(arr_q11, n);
    cout << "BST In-Order Traversal: ";
    inorderTraversal(root);
    cout << endl;

    int minDiff = findMinDifference(root);
    cout << "A diferenca minima na árvore e de: " << minDiff << endl << endl;

    // ============ QUESTÃO 12 ============
    cout << "============ QUESTÃO 12 ============\n";
    int arr_q12[n];
    generateRandomArray(arr_q12, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q12, n);

    int closeX = 10;
    int k = 5;
    int* arrCloseX = closestToX(arr_q12, n, k, closeX);
    
    cout << k << " numeros mais próximos de " << closeX << ": ";
    printArray(arrCloseX, k);
    cout << endl;

    // ============ QUESTÃO 13 ============
    cout << "============ QUESTÃO 13 ============\n";
    int resultSize;
    int xInterval = 10;
    int arr_q13[n];
    generateRandomArray(arr_q13, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q13, n);

    int* result = mostElementsInInterval(arr_q13, n, xInterval, resultSize);
    cout << "O maior subconjunto onde a diferenca maxima <= " << xInterval << " é: ";
    printArray(result, resultSize);
    cout << endl;

    // ============ QUESTÃO 14 ============
    cout << "============ QUESTÃO 14 ============\n";
    int arr_q14[n];
    generateRandomArray(arr_q14, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q14, n);

    int** pair = maximumPair(arr_q14, n);
    cout << "O par máximo é: \n";
    cout << "Elemento 1: Valor = " << pair[0][0] << ", Índice = " << pair[0][1] << endl;
    cout << "Elemento 2: Valor = " << pair[1][0] << ", Índice = " << pair[1][1] << endl << endl;
    
    // ============ QUESTÃO 15 ============
    cout << "============ QUESTÃO 15 ============\n";
    int arr_q15[n];
    generateRandomArray(arr_q15, n, range_min, range_max);
    cout << "Array gerado: ";
    printArray(arr_q15, n);
    
    TreeNode* root15 = createBalancedTree(arr_q15, n);
    
    // Verifica se a árvore está balanceada
    if (isBalanced(root15)) {
        cout << "A árvore está balanceada!" << endl;
    } else {
        cout << "A árvore NÃO está balanceada." << endl;
    }
    

    return 0;
}
