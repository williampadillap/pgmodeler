/*
# PostgreSQL Database Modeler (pgModeler)
# Sub-project: Biblioteca libobjrenderer
# Classe: OGRelacionamento
# Description:Esta classe deriva a classe ObjetoGrafico e implementa a representação gráfica
#            da classe Relacionamento/RelacionamentoBase. O sufixo OG foi adicionado ao nome
#            da classe para evitar conflitos de nomes entra a classe Tabela da biblioteca
#            libpgmodeler e a classe abaixo definida.
#
# Copyright 2006-2013 - Raphael Araújo e Silva <rkhaotix@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/
#ifndef OG_RELACIONAMENTO_H
#define OG_RELACIONAMENTO_H

#include "textboxview.h"
#include "basetableview.h"
#include "relationship.h"

class RelationshipView: public BaseObjectView {
 private:
  //Raio padrão da representação gráfica do ponto.
  static const float GRAPHIC_PNT_RADIUS=2.5f;

  Q_OBJECT
  /* Flag que indica que a linha está sendo configurada/atualizada. Este é usado
     para evitar que o método configurarLinha seja chamado excessivamente durante
     o movimento das tabelas envolvidas. */
  bool configuring_line;

  QPainterPath rel_shape;

  //Armazena a representação gráfica dos rótulos
  TextboxView *labels[3];

  //Armazena a representação gráfica das tabelas envolvidas no relacionamento
  BaseTableView *tables[2];

  /* Representação gráfica dos pontos adicionados ao relacionamento pelo usuário.
     Estes objetos são usados para facilitar a movimentação dos pontos pela tela */
  vector<QGraphicsPolygonItem *> graph_points;

  //Linhas que definem o relacionamento
  vector<QGraphicsLineItem *> lines;

  //Armazena a representação gráfica dos atributos do relacionamento
  vector<QGraphicsItemGroup *> attributes;

  //Objeto descritor do tipo do relacionamento
  QGraphicsPolygonItem *descriptor;

  /* Armazena a referência ao objeto filho (ponto ou rótulo) atualmente sob o cursor do mouse.
     Esta referência é usada no método mouseMoveEvent() para movimentar o objeto filho */
  QGraphicsItem *sel_object;

  //Armazena a posição inicial (padrão) dos rótulos do relacionamento
  QPointF labels_ini_pos[3];

  //Armazena o índice do objeto filho (ponto ou rótulo) selecionado
  int sel_object_idx;

  //Configura o posicionamento dos rótulos do relacionamento
  void configureLabels(void);

  //Configura o posicionamento do descritor de relacionamento
  void configureDescriptor(void);

  //Configura o posicionamento dos atributos do relacionamento
  void configureAttributes(void);

  /* Sobrecarga do método ObjetoGrafico::configurarInfoPosicao.
     Esta implementação configura a posição do objeto de informação
     da posição em relação ao descritor do relacionamento */
  void configurePositionInfo(void);

 protected:
  //Sobrecarga do método ObjetoGrafico::itemChange() que faz operações adicionais quando objeto sobre modificações
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  //Métodos que tratam movimentos e cliques de mouse sobre o objeto e/ou seus filhos
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *){}

 public slots:
  //Configura a linha do relacionamento
  void configureLine(void);

  //Obtém um rótulo através do índice
  TextboxView *getLabel(unsigned lab_idx);

 private slots:
  //Configura o objeto relacionamento completo
  void configureObject(void);

 public:
  RelationshipView(BaseRelationship *rel);
  ~RelationshipView(void);

  //Calcula o boundingRect do relacionamento considerando todos os objetos filhos
  QRectF __boundingRect(void);

  //Retorna o objeto de origem convertido em relacionamento
  BaseRelationship *getSourceObject(void);

  /** issue#2 **/
  /* Desconecta do relacionamento os sinais emitidos pelas tabelas.
     Esse método só deve ser chamado quando o relacionamento será removido
     da cena e destruído, se chamado antes disso, o relacionamento não será
     mais atualizando quando uma das tabelas se movimentarem */
  void disconnectTables(void);

 signals:
  //Este sinal é emitido sempre que um ponto é adicionado ou removido do relacionamento
  void s_relationshipModified(BaseGraphicObject *rel);
};

#endif