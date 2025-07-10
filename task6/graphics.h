#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "canvasview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Graphics;
}
QT_END_NAMESPACE

class Graphics : public QMainWindow
{
    Q_OBJECT

public:
    Graphics(QWidget *parent = nullptr);
    ~Graphics();

private slots:
    void on_actionRectangle_triggered();

    void on_actionEllipse_triggered();

    void on_actionRhomb_triggered();

    void on_actionTriangle_equilateral_triggered();

    void on_actionset_default_color_black_triggered();

    void on_actionuser_choice_triggered();

    void on_action_0_triggered();

    void on_action_2_triggered();

    void on_actionSave_current_result_to_bin_file_triggered();

    void on_actionRestore_figures_from_bin_file_triggered();

    void on_action_triggered();

    void on_action_3_triggered();

    void handleFigureAdded();

private:
    void setUpScene();
    void updateStatusBar();
    Ui::Graphics *ui;
    CanvasView* scene;
    bool saved;
};
#endif // GRAPHICS_H
