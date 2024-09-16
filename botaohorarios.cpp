#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <filesystem>
#include <FL/fl_ask.H>
#include <algorithm>



// Protótipos das funções
void save_schedule(const std::string& professor, const std::string& day, const std::string& start_time, const std::string& end_time);
void delete_schedule(const std::string& professor, const std::string& day, const std::string& start_time, const std::string& end_time);
void show_schedules(Fl_Multiline_Output* output, const std::string& professor);
void load_professors_into_choice(Fl_Choice* choice);
std::vector<std::string> load_professors();
std::vector<std::string> split(const std::string &s, char delimiter);

// Função para dividir uma string com base em um delimitador
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Função para carregar os nomes dos professores do arquivo
std::vector<std::string> load_professors() {
    std::vector<std::string> professors;
    std::ifstream file("professores.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            auto parts = split(line, ':');
            professors.push_back(parts[0]); // Adiciona apenas o nome do professor
        }
        file.close();
    }

    return professors;
}

// Função para comparar os dias da semana em ordem
int day_to_int(const std::string& day) {
    if (day == "Segunda-feira") return 1;
    if (day == "Terça-feira") return 2;
    if (day == "Quarta-feira") return 3;
    if (day == "Quinta-feira") return 4;
    if (day == "Sexta-feira") return 5;
    if (day == "Sábado") return 6;
    if (day == "Domingo") return 7;
    return 8; // Caso não seja um dia válido
}

// Função para salvar o horário no arquivo específico do professor com ordenação
void save_schedule(const std::string& professor, const std::string& day, const std::string& start_time, const std::string& end_time) {
    std::string filename = professor + ".txt"; // Nome do arquivo
    std::vector<std::pair<std::string, std::string>> schedules;

    // Carregar os horários existentes no arquivo
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            size_t delimiter_pos = line.find(':');
            if (delimiter_pos != std::string::npos) {
                std::string day_from_file = line.substr(0, delimiter_pos);
                std::string time_from_file = line.substr(delimiter_pos + 1);

                // Verifica se o horário é para o mesmo dia; se for, substitui o horário
                if (day_from_file == day) {
                    time_from_file = start_time + "-" + end_time;
                }

                schedules.emplace_back(day_from_file, time_from_file);
            }
        }
        file.close();
    }

    // Adicionar o novo horário (ou substituir se já existe para o mesmo dia)
    bool replaced = false;
    for (auto& schedule : schedules) {
        if (schedule.first == day) {
            schedule.second = start_time + "-" + end_time;
            replaced = true;
            break;
        }
    }
    if (!replaced) {
        schedules.emplace_back(day, start_time + "-" + end_time);
    }

    // Ordenar os horários por dia da semana
    std::sort(schedules.begin(), schedules.end(), [](const auto& a, const auto& b) {
        return day_to_int(a.first) < day_to_int(b.first);
    });

    // Reescrever os horários ordenados no arquivo
    std::ofstream outfile(filename);
    for (const auto& schedule : schedules) {
        outfile << schedule.first << ":" << schedule.second << "\n";
    }
    outfile.close();
}

// Função para excluir um horário do arquivo específico do professor
void delete_schedule(const std::string& professor, const std::string& day, const std::string& start_time, const std::string& end_time) {
    std::string filename = professor + ".txt";
    std::ifstream file(filename);
    std::ofstream temp("temp.txt");
    std::string line;

    if (file.is_open() && temp.is_open()) {
        while (std::getline(file, line)) {
            if (line != day + ":" + start_time + "-" + end_time) {
                temp << line << "\n";
            }
        }
        file.close();
        temp.close();
        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
    }
}

// Função para carregar os professores na lista suspensa
void load_professors_into_choice(Fl_Choice* choice) {
    auto professors = load_professors();
    choice->clear(); // Limpa opções anteriores
    for (const auto& professor : professors) {
        choice->add(professor.c_str());
    }
}

// Função para mostrar os horários salvos para o professor selecionado
void show_schedules(Fl_Multiline_Output* output, const std::string& professor) {
    std::string filename = professor + ".txt";
    std::ifstream file(filename);
    std::string line;
    std::string display_text;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // Encontrar a primeira ocorrência de ':' que separa o dia do horário
            size_t delimiter_pos = line.find(':');
            if (delimiter_pos != std::string::npos) {
                std::string day = line.substr(0, delimiter_pos); // Parte antes do ':'
                std::string time_range = line.substr(delimiter_pos + 1); // Parte após o ':'
                display_text += "Dia: " + day + "\nHorário: " + time_range + "\n\n";
            }
        }
        file.close();
    }

    output->value(display_text.c_str());
}


// Função de callback para salvar horário
void schedule_callback(Fl_Widget*, void* data) {
    auto inputs = static_cast<std::tuple<Fl_Choice*, Fl_Choice*, Fl_Input*, Fl_Input*, Fl_Multiline_Output*>*>(data);
    std::string professor = std::get<0>(*inputs)->text(); // Fl_Choice
    std::string day = std::get<1>(*inputs)->text();       // Fl_Choice
    std::string start_time = std::get<2>(*inputs)->value(); // Fl_Input
    std::string end_time = std::get<3>(*inputs)->value();   // Fl_Input

    // Salvar horário no arquivo
    save_schedule(professor, day, start_time, end_time);

    // Atualizar a lista de horários exibida
    show_schedules(std::get<4>(*inputs), professor); // Atualiza a lista de horários exibida
}

// Função de callback para excluir o horário
void delete_callback(Fl_Widget*, void* data) {
    auto inputs = static_cast<std::tuple<Fl_Choice*, Fl_Choice*, Fl_Input*, Fl_Input*, Fl_Multiline_Output*>*>(data);
    std::string professor = std::get<0>(*inputs)->text(); // Fl_Choice
    std::string day = std::get<1>(*inputs)->text();       // Fl_Choice
    std::string start_time = std::get<2>(*inputs)->value(); // Fl_Input
    std::string end_time = std::get<3>(*inputs)->value();   // Fl_Input

    // Excluir o horário do arquivo
    delete_schedule(professor, day, start_time, end_time);

    // Atualizar a lista de horários exibida
    show_schedules(std::get<4>(*inputs), professor); // Atualiza a lista de horários exibida
}

// Função de callback para carregar os horários ao selecionar o professor
void professor_choice_callback(Fl_Widget* widget, void* data) {
    Fl_Choice* choice = static_cast<Fl_Choice*>(widget);
    Fl_Multiline_Output* output = static_cast<Fl_Multiline_Output*>(data);
    std::string professor = choice->text();
    show_schedules(output, professor);
}

// Função para excluir todos os arquivos .txt de professores
void delete_all_schedules(Fl_Widget*, void*) {
    std::string path = "."; // Diretório atual
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".txt" && entry.path().filename() != "professores.txt") {
            std::filesystem::remove(entry.path());
        }
    }
    fl_message("Todos os horários foram excluídos!");
}

int main() {
    int window_width = 700;
    int window_height = 550;
    Fl_Window* window = new Fl_Window(window_width, window_height, "Cadastro de Horários");

    Fl_JPEG_Image* background_image = new Fl_JPEG_Image("pngs/listraazul.JPEG");

// Verifica se a imagem foi carregada corretamente
    if (!background_image->data()) {
        std::cerr << "Não foi possível carregar a imagem de fundo." << std::endl;
        return 1;
    }

    // Cria um widget Fl_Box para exibir a imagem de fundo
    Fl_Box* background_box = new Fl_Box(0, 0, window->w(), window->h());
    background_box->image(background_image); // Define a imagem de fundo
    background_box->box(FL_FLAT_BOX); // Define um estilo de caixa sem borda

    Fl_Choice* professor_choice = new Fl_Choice(150, 30, 200, 25, "Professor:");
    Fl_Choice* day_choice = new Fl_Choice(150, 70, 200, 25, "Dia da Semana:");
    Fl_Input* start_time_input = new Fl_Input(150, 110, 80, 25, "Início:");
    Fl_Input* end_time_input = new Fl_Input(150, 150, 80, 25, "Término:");

    Fl_Button* save_button = new Fl_Button(150, 190, 200, 25, "Salvar Horário");
    Fl_Button* delete_button = new Fl_Button(150, 230, 200, 25, "Excluir Horário");

    // Botão "Excluir Tudo"
    Fl_Button* delete_all_button = new Fl_Button(window_width - 150, window_height - 50, 120, 25, "Excluir Tudo");
    delete_all_button->callback(delete_all_schedules);

    // Área de rolagem para mostrar horários
    Fl_Scroll* scroll = new Fl_Scroll(50, 270, 600, 200);
    scroll->type(Fl_Scroll::VERTICAL); // Ativa a rolagem vertical
    scroll->box(FL_DOWN_BOX); // Adiciona uma borda para a área de rolagem

    Fl_Multiline_Output* output = new Fl_Multiline_Output(50, 0, 580, 3000);
    scroll->add(output); // Adiciona o output à área de rolagem
    scroll->end(); // Fecha a área de rolagem

    // Adicionar opções de dias da semana
    day_choice->add("Segunda-feira");
    day_choice->add("Terça-feira");
    day_choice->add("Quarta-feira");
    day_choice->add("Quinta-feira");
    day_choice->add("Sexta-feira");
    day_choice->add("Sábado");
    day_choice->add("Domingo");

    load_professors_into_choice(professor_choice);

    // Passar o Fl_Multiline_Output* para as funções de callback
    auto inputs = std::make_tuple(professor_choice, day_choice, start_time_input, end_time_input, output);

    save_button->callback(schedule_callback, &inputs);
    delete_button->callback(delete_callback, &inputs);

    // Callback para atualizar horários ao selecionar um professor
    professor_choice->callback(professor_choice_callback, output);

    window->end();
    window->show();

    return Fl::run();
}
