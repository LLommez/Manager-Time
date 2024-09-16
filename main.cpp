#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <iostream>

// Função de callback para o botão 1
void button1_callback(Fl_Widget*, void*) {
    // Inclua o arquivo botao1.cpp aqui ou chame a função que cria a janela
    // Em vez de incluir diretamente, você pode usar a abordagem de declarar uma função para criar a janela
    system("g++ botaocadastrar.cpp -o botaocadastrar -lfltk -lfltk_images"); // Compila botao1
    system("./botaocadastrar"); // Executa o executável

int ret = system("g++ botaocadastrar.cpp -o botaocadastrar -lfltk -lfltk_images");
if (ret != 0) 
    std::cerr << "Erro na compilação!" << std::endl;
    return;
}


// Função de callback para o botão 2
void button2_callback(Fl_Widget*, void*) {
    // Inclua o arquivo botao1.cpp aqui ou chame a função que cria a janela
    // Em vez de incluir diretamente, você pode usar a abordagem de declarar uma função para criar a janela
    system("g++ botaohorarios.cpp -o botaohorarios -lfltk -lfltk_images"); // Compila botao2
    system("./botaohorarios"); // Executa o executável

int ret = system("g++ botaohorarios.cpp -o botaohorarios -lfltk -lfltk_images");
if (ret != 0) 
    std::cerr << "Erro na compilação!" << std::endl;
    return;
}

// Função de callback para o botão 3
void button3_callback(Fl_Widget*, void*) {
    // Inclua o arquivo botao3.cpp aqui ou chame a função que cria a janela
    // Em vez de incluir diretamente, você pode usar a abordagem de declarar uma função para criar a janela
    system("g++ botaoalunos.cpp -o botaoalunos -lfltk -lfltk_images"); // Compila botao3
    system("./botaoalunos"); // Executa o executável

int ret = system("g++ botaoalunos.cpp -o botaoalunos -lfltk -lfltk_images");
if (ret != 0) 
    std::cerr << "Erro na compilação!" << std::endl;
    return;
}

// Função de callback para o botão 4
void button4_callback(Fl_Widget*, void*) {
    // Inclua o arquivo botao4.cpp aqui ou chame a função que cria a janela
    // Em vez de incluir diretamente, você pode usar a abordagem de declarar uma função para criar a janela
    system("g++ botaoautomatico.cpp -o botaoautomatico -lfltk -lfltk_images"); // Compila botao4
    system("./botaoautomatico"); // Executa o executável

int ret = system("g++ botaoautomatico.cpp -o botaoautomatico -lfltk -lfltk_images");
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
    

// Define a largura da caixa de título e calcula a posição centralizada
    int title_box_width = 380;
    int title_box_height = 60;
    int window_width = window->w();
    int title_box_x = (window_width - title_box_width) / 2;
    int title_box_y = 40; // Posição vertical fixa

 Fl_Box* title_box = new Fl_Box(title_box_x, title_box_y, title_box_width, title_box_height, "Manager Time");
    title_box->box(FL_UP_BOX); // Define o estilo da borda da caixa
    title_box->labelsize(24);  // Define o tamanho da fonte do texto
    title_box->labelfont(FL_BOLD); // Define o estilo da fonte
    title_box->labelcolor(FL_WHITE); // Define a cor do texto
    title_box->color(FL_DARK_BLUE); // Define a cor de fundo da caixa de título
    
    
    // Cria os botões
    int button_width = 300;
    int button_height = 40;
    int spacing = 10;
    int window_height = window->h();

    // Calcula a posição dos botões
    int button_x1 = (window_width - button_width) / 2;
    int button_y1 = (window_height - button_height) / 2 - (button_height + spacing);

    int button_x2 = (window_width - button_width) / 2;
    int button_y2 = (window_height - button_height) / 2;

    int button_x3 = (window_width - button_width) / 2;
    int button_y3 = (window_height - button_height) / 2 + (button_height + spacing);

    int button_x4 = (window_width - button_width) / 2;
    int button_y4 = (window_height - button_height) / 2 + 2 * (button_height + spacing);


    // Cria os botões
    Fl_Button* button1 = new Fl_Button(button_x1, button_y1, button_width, button_height, "Cadastrar Professores");
    Fl_Button* button2 = new Fl_Button(button_x2, button_y2, button_width, button_height, "Cadastrar Horários");
    Fl_Button* button3 = new Fl_Button(button_x3, button_y3, button_width, button_height, "Cadastrar Alunos");
    Fl_Button* button4 = new Fl_Button(button_x4, button_y4, button_width, button_height, "Formular Horários");

    //tipo de botao
    button1->box(FL_ROUND_UP_BOX);
    button2->box(FL_ROUND_UP_BOX);
    button3->box(FL_ROUND_UP_BOX);
    button4->box(FL_ROUND_UP_BOX);

    // Define as funções de callback para os botões
    button1->callback(button1_callback);
    button2->callback(button2_callback);
    button3->callback(button3_callback);
    button4->callback(button4_callback);

    // Finaliza a configuração da janela e a exibe
    window->end();
    window->show();

    // Inicia o loop principal do FLTK
    return Fl::run();
}

