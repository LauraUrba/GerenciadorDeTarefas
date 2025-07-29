#include <QApplication>
#include "GUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GUI window;                // ← Aqui você instancia sua interface personalizada
    window.move(100, 100);     // ← Posiciona na tela
    window.show();             // ← Exibe

    return app.exec();         // ← Mantém a janela viva
}
