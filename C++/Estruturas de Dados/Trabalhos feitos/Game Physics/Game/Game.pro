QT += core
QT -= gui

CONFIG += c++11

TARGET = Game
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Jogadas.cpp \
    AVLTree.cpp \
    NodeAVL.cpp \
    ObjetosDoJogo.cpp \
    PosicaoDoObjeto.cpp \
    Jogo.cpp \
    ListaCircular.cpp \
    NodeLC.cpp

HEADERS += \
    Jogadas.h \
    AVLTree.h \
    NodeAVL.h \
    ObjetosDoJogo.h \
    PosicaoDoObjeto.h \
    Jogo.h \
    ListaCircular.h \
    NodeLC.h
