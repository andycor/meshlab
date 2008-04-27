#include <QTabBar>
#include "textureeditor.h"
#include<vcg/complex/trimesh/textcoord_optimization.h>


static int countPage = 1;	// Number of Tab in the texture's TabWidgets

TextureEditor::TextureEditor(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
}

TextureEditor::~TextureEditor()
{
	Reset();
}

void TextureEditor::Reset()
{
	for (int i = 1; i < countPage; i++) ui.tabWidget->removeTab(i);
	countPage = 1;
	first = 0;
}

void TextureEditor::AddRenderArea(QString texture, MeshModel *m, unsigned index)
{
	// Add a RenderArea widget to the TabWidget
	int id = area->mm()->glw.TMId.back();
	

	QTabBar *t = new QTabBar(ui.tabWidget);
	RenderArea *ra= new RenderArea(t, texture, m, index);
	ra->setGeometry(MARGIN,MARGIN,MAXW,MAXH);
	ui.tabWidget->addTab(t, texture);
	if (countPage == 1)
	{
		ui.tabWidget->removeTab(0);
		first = ra;
		ra->show();
	}
	countPage++;
	QObject::connect(ra, SIGNAL(UpdateModel()),this, SLOT(UpdateModel()));

}

void TextureEditor::AddEmptyRenderArea()
{
	// Add an empty render area (the model doesn't has any texture)
	RenderArea *ra= new RenderArea(ui.tabWidget->widget(0));
	first = ra;
	ra->setGeometry(MARGIN,MARGIN,400,400);
	ra->show();
}

void TextureEditor::SelectFromModel()
{
	// Update the Render Area according to the select faces from the model
	for (int i = 0; i < countPage-1; i++)
		((RenderArea*)ui.tabWidget->widget(i)->childAt(MARGIN,MARGIN))->ImportSelection();
	ResetLayout();
	ui.selectButton->setChecked(true);
}

void TextureEditor::UpdateModel()
{
	// Update the mesh after an edit
	area->update();
}

void TextureEditor::SetProgress(int val)
{
	// Change the value of the progress bar
	ui.progressBar->setValue(val);
	ui.progressBar->update();
}

void TextureEditor::SetProgressMax(int val)
{
	// Set the max of progress bar
	ui.progressBar->setMaximum(val);
}

void TextureEditor::ResetLayout()
{
	// uncheck all the buttons
	ui.connectedButton->setChecked(false);
	ui.moveButton->setChecked(false);
	ui.selectButton->setChecked(false);
	ui.vertexButton->setChecked(false);
}

void TextureEditor::SmoothTextureCoordinates()
{
	// <-------
	//vcg::tri::SmoothTextureCoords(model->cm);
}

// Buttons
void TextureEditor::on_moveButton_clicked()
{
	ResetLayout();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeMode(0);
	ui.moveButton->setChecked(true);
}

void TextureEditor::on_connectedButton_clicked()
{
	ResetLayout();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeSelectMode(1);
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeMode(2);
	ui.connectedButton->setChecked(true);
}

void TextureEditor::on_selectButton_clicked()
{
	ResetLayout();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeSelectMode(0);
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeMode(2);
	ui.selectButton->setChecked(true);
}

void TextureEditor::on_vertexButton_clicked()
{
	ResetLayout();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeSelectMode(2);
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeMode(2);
	ui.vertexButton->setChecked(true);
}

void TextureEditor::on_clampButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->RemapClamp();
}

void TextureEditor::on_modulusButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->RemapMod();
}

void TextureEditor::on_invertButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->InvertSelection();
}

void TextureEditor::on_cancelButton_clicked()
{
	ResetLayout();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ClearSelection();
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ChangeMode(0);
	ui.cancelButton->setChecked(false);
	ui.moveButton->setChecked(true);
}

void TextureEditor::on_flipHButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->Flip(true);
}

void TextureEditor::on_flipVButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->Flip(false);
}

void TextureEditor::on_unify2Button_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->UnifyCouple();
}

void TextureEditor::on_unifySetButton_clicked()
{
	((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->UnifySet();
}

void TextureEditor::on_smoothButton_clicked()
{
	// Apply the smooth
	SmoothTextureCoordinates();
}

void TextureEditor::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_H) ((RenderArea*)ui.tabWidget->currentWidget()->childAt(MARGIN,MARGIN))->ResetPosition();
	else e->ignore();
}

void TextureEditor::on_tabWidget_currentChanged(int index)
{
	int button = 0, mode = -1;
	if (ui.selectButton->isChecked()) {button = 2; mode = 0;}
	else if (ui.connectedButton->isChecked()) {button = 2; mode = 1;}
	else if (ui.vertexButton->isChecked()) {button = 2; mode = 2;}
	((RenderArea*)ui.tabWidget->widget(index)->childAt(MARGIN,MARGIN))->ChangeMode(button);
	if (mode != -1) ((RenderArea*)ui.tabWidget->widget(index)->childAt(MARGIN,MARGIN))->ChangeSelectMode(mode);
}