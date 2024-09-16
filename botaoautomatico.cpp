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

// Função de callback para o botão manual
void button1_callback(Fl_Widget*, void*) {
    system("g++ botaomanual.cpp -o botaomanual -lfltk -lfltk_images"); // Compila botao1
    system("./botaomanual"); // Executa o executável

int ret = system("g++ botaomanual.cpp -o botaomanual -lfltk -lfltk_images");
if (ret != 0) 
    std::cerr << "Erro na compilação!" << std::endl;
    return;
}


// Função de callback para o botão auto
void button2_callback(Fl_Widget*, void*) {
    system("g++ botaoauto.cpp -o botaoauto -lfltk -lfltk_images"); // Compila botao2
    system("./botaoauto"); // Executa o executável

int ret = system("g++ botaoauto.cpp -o botaoauto -lfltk -lfltk_images");
if (ret != 0) 
    std::cerr << "Erro na compilação!" << std::endl;
    return;
}

int main() {
    // Cria a janela
    Fl_Window* window = new Fl_Window(700, 550, "Manager Time");

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
    
    // Cria os botões
    int button_width = 300;
    int button_height = 40;
    int spacing = 10;
    int window_height = window->h();
    int window_width = window->w();

// Calcula a posição dos botões
    int button_x1 = (window_width - button_width) / 2;
    int button_y1 = (window_height - button_height) / 2 - (button_height + spacing);

    int button_x2 = (window_width - button_width) / 2;
    int button_y2 = (window_height - button_height) / 2;

// Cria os botões
    Fl_Button* button1 = new Fl_Button(button_x1, button_y1, button_width, button_height, "Gerar Horários Manualmente");
    Fl_Button* button2 = new Fl_Button(button_x2, button_y2, button_width, button_height, "Gerar Horários Automaticamente");
    
//tipo de botao
    button1->box(FL_ROUND_UP_BOX);
    button2->box(FL_ROUND_UP_BOX);
    
// Define as funções de callback para os botões
    button1->callback(button1_callback);
    button2->callback(button2_callback);
    
// Finaliza a configuração da janela e a exibe
    window->end();
    window->show();

    // Inicia o loop principal do FLTK
    return Fl::run();
}