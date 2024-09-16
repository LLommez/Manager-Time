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

int main() {
    // Cria a janela
    Fl_Window* window = new Fl_Window(700, 550, "Em Breve");

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
    

// Define a largura da caixa de título e calcula a posição centralizada
    int title_box_width = 380;
    int title_box_height = 60;
    int window_width = window->w();
    int title_box_x = (window_width - title_box_width) / 2;
    int title_box_y = 225; // Posição vertical fixa

 Fl_Box* title_box = new Fl_Box(title_box_x, title_box_y, title_box_width, title_box_height, "Em Breve");
    title_box->box(FL_UP_BOX); // Define o estilo da borda da caixa
    title_box->labelsize(24);  // Define o tamanho da fonte do texto
    title_box->labelfont(FL_BOLD); // Define o estilo da fonte
    title_box->labelcolor(FL_WHITE); // Define a cor do texto
    title_box->color(FL_DARK_BLUE); // Define a cor de fundo da caixa de título

    // Finaliza a configuração da janela e a exibe
    window->end();
    window->show();

    // Inicia o loop principal do FLTK
    return Fl::run();
}