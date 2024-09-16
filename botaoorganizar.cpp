#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

// Função para definir uma ordem para os dias da semana
int getDayOrder(const string& day) {
    if (day == "Segunda-feira") return 1;
    if (day == "Terça-feira") return 2;
    if (day == "Quarta-feira") return 3;
    if (day == "Quinta-feira") return 4;
    if (day == "Sexta-feira") return 5;
    return 6; // Caso o dia seja inválido ou fora do esperado
}

// Função para ler o arquivo e organizar os blocos de horários
void organizeFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo de entrada: " << inputFileName << endl;
        return;
    }

    vector<pair<int, string>> blocks;
    string line, block, day;

    // Ler o arquivo linha por linha
    while (getline(inputFile, line)) {
        if (line.rfind("Dia:", 0) == 0) {
            // Ao encontrar o início de um novo bloco, adicionar o bloco anterior
            if (!block.empty()) {
                blocks.push_back({getDayOrder(day), block});
                block.clear();
            }
            // Extrair o dia da linha e iniciar um novo bloco
            day = line.substr(5); // Pega o nome do dia após "Dia: "
            block += line + "\n";
        } else {
            block += line + "\n";
        }
    }
    // Adiciona o último bloco
    if (!block.empty()) {
        blocks.push_back({getDayOrder(day), block});
    }

    inputFile.close();

    // Ordenar os blocos de acordo com os dias da semana
    sort(blocks.begin(), blocks.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first < b.first;
    });

    // Reescrever o arquivo organizado
    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Erro ao abrir o arquivo de saída: " << outputFileName << endl;
        return;
    }

    for (const auto& block : blocks) {
        outputFile << block.second;
    }

    outputFile.close();
}

int main() {
    string directory = "."; // Diretório onde os arquivos .txt estão localizados

    // Percorrer todos os arquivos no diretório
    for (const auto& entry : fs::directory_iterator(directory)) {
        string fileName = entry.path().filename().string();

        // Verificar se o arquivo tem o sufixo "_horario.txt"
        if (fileName.size() > 12 && fileName.substr(fileName.size() - 12) == "_horario.txt") {
            string inputFile = directory + "/" + fileName;
            string outputFile = directory + "/" + fileName;

            organizeFile(inputFile, outputFile);

            cout << "Arquivo " << fileName << " organizado com sucesso!" << endl;
        }
    }

    return 0;
}
