#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem> 
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void save_alunos(Fl_Input* name_input, Fl_Input* subjects_input) {
    std::ofstream file("alunos.txt", std::ios_base::app);
    if (file.is_open()) {
        file << name_input->value() << ":" << subjects_input->value() << "\n";
        file.close();
    }
}

void show_alunos(Fl_Multiline_Output* output) {
    std::ifstream file("alunos.txt");
    std::string line;
    std::string display_text;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            auto parts = split(line, ':');
            display_text += "Aluno: " + parts[0] + "\nAno: " + parts[1] + "\n\n";
        }
        file.close();
    }
    
    output->value(display_text.c_str());
}

void delete_alunos(const std::string& name) {
    std::ifstream file("alunos.txt");
    std::ofstream temp("temp.txt");
    std::string line;

    if (file.is_open() && temp.is_open()) {
        while (std::getline(file, line)) {
            auto parts = split(line, ':');
            if (parts[0] != name) {
                temp << line << "\n";
            }
        }
        file.close();
        temp.close();
        std::remove("alunos.txt");
        std::rename("temp.txt", "alunos.txt");
    }
}

void center_widget(Fl_Widget* widget, int window_width, int y) {
    int widget_width = widget->w();
    int x = (window_width - widget_width) / 2;
    widget->position(x, y);
}

int main() {
    int window_width = 700;
    int window_height = 550;
    Fl_Window* window = new Fl_Window(window_width, window_height, "Cadastro de Alunos");

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

    Fl_Input* name_input = new Fl_Input(0, 30, 200, 25, "Nome:");
    Fl_Input* subjects_input = new Fl_Input(0, 70, 200, 25, "Ano:");

    Fl_Button* save_button = new Fl_Button(0, 110, 200, 25, "Cadastrar Aluno");
    Fl_Button* show_button = new Fl_Button(0, 150, 200, 25, "Alunos Cadastrados");

    // Campo e botão para excluir professor
    Fl_Input* delete_input = new Fl_Input(0, 190, 200, 25, "Excluir Nome:");
    Fl_Button* delete_button = new Fl_Button(0, 230, 200, 25, "Excluir Aluno");

    //a porra do scroll
    Fl_Scroll* scroll = new Fl_Scroll(50, 270, 600, 250);
    scroll->type(Fl_Scroll::VERTICAL); // Ativa a rolagem vertical
    scroll->box(FL_DOWN_BOX); // Adiciona uma borda para a área de rolagem

    Fl_Multiline_Output* output = new Fl_Multiline_Output(0, 0, 600, 3000);
    scroll->add(output); // Adiciona o output à área de rolagem
    scroll->end(); // Fecha a área de rolagem


    center_widget(name_input, window_width, 30);
    center_widget(subjects_input, window_width, 70);
    center_widget(save_button, window_width, 110);
    center_widget(show_button, window_width, 150);
    center_widget(output, window_width, 190);
    center_widget(delete_input, window_width, 190);
    center_widget(delete_button, window_width, 230);

   save_button->callback([](Fl_Widget*, void* data) {
    auto inputs = static_cast<std::pair<Fl_Input*, Fl_Input*>*>(data);
    save_alunos(inputs->first, inputs->second);
}, new std::pair<Fl_Input*, Fl_Input*>(name_input, subjects_input));


    show_button->callback([](Fl_Widget*, void* data) {
        show_alunos(static_cast<Fl_Multiline_Output*>(data));
    }, output);

    delete_button->callback([](Fl_Widget*, void* data) {
        auto input = static_cast<Fl_Input*>(data);
        delete_alunos(input->value());
        // Atualiza a lista de alunos após a exclusão
        show_alunos(static_cast<Fl_Multiline_Output*>(input->user_data()));
    }, delete_input);

    // Configurar o usuário de dados para o botão de exclusão
    delete_input->user_data(output);

    window->end();
    window->show();

    return Fl::run();
}
